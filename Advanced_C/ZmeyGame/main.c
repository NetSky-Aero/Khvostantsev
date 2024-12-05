#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include <inttypes.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define MIN_Y  2
#define CONTROLS 3
#define FOOD_COUNT 5
enum {LEFT=1, UP, RIGHT, DOWN, STOP_GAME='q'};
enum {MAX_TAIL_SIZE=100, START_TAIL_SIZE=3, MAX_FOOD_SIZE=20, FOOD_EXPIRE_SECONDS=10};

// ��������� ���������� ��� ��������� ����� �����
struct control_buttons
{
    int down;
    int up;
    int left;
    int right;
};

// ������ ��� ���������� ��������� � ��������� WSAD
struct control_buttons default_controls[CONTROLS] =
{
    {KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT},          // ���������� ���������
    {'s', 'w', 'a', 'd'},                             // ���������� WSAD (������ �������)
    {'S', 'W', 'A', 'D'}                              // ���������� WSAD (������� �������)
};

// ��������� ��� ������ ������
typedef struct tail_t
{
    int x;                                                                                  // ���������� X ������
    int y;                                                                                  // ���������� Y ������
} tail_t;

// ��������� ��� ������
typedef struct snake_t
{
    int x;                                                                                  // ���������� X ������ ������
    int y;                                                                                  // ���������� Y ������ ������
    int direction;                                                                          // ������� ����������� �������� ������
    size_t tsize;                                                                           // ������� ������ ������
    struct tail_t *tail;                                                                    // ������, ���������� �������� ������
} snake_t;

// ��������� ��� ���
typedef struct food_t
{
    int x;                                                                                  // ���������� X ���
    int y;                                                                                  // ���������� Y ���
    int active;                                                                             // ���� ���������� (1 - ��������, 0 - �������)
    time_t spawn_time;                                                                      // ����� ��������� ���
} food_t;

// ������������� ������ ������
void initTail(struct tail_t t[], size_t size)
{
    struct tail_t init_t = {0, 0};
    for (size_t i = 0; i < size; i++)
    {
        t[i] = init_t;                                                                      // ������������ ��������� ���������� ������ � (0, 0)
    }
}

// ������������� ������ ������
void initHead(struct snake_t *head, int x, int y)
{
    head->x = x;                                                                            // ������������� ��������� ���������� X
    head->y = y;                                                                            // ������������� ��������� ���������� Y
    head->direction = RIGHT;                                                                // ��������� ����������� - ������
}

// ������������� ���� ������
void initSnake(snake_t *head, size_t size, int x, int y)
{
    tail_t* tail = (tail_t*) malloc(MAX_TAIL_SIZE * sizeof(tail_t));                        // ������� ������ ��� �����
    initTail(tail, MAX_TAIL_SIZE);                                                          // ������������� �����
    initHead(head, x, y);                                                                   // ������������� ������
    head->tail = tail;                                                                      // ���������� ����� � ������
    head->tsize = size + 1;                                                                 // ������������ ������ ������
}

// �������� ������ ������
void go(struct snake_t *head)
{
    char ch = '@';                                                                          // ������ ������ ������
    int max_x = 0, max_y = 0;
    getmaxyx(stdscr, max_y, max_x);                                                         // ������� ������� ���� ���������

    mvprintw(head->y, head->x, " ");                                                        // ������ ������ ������� ������
    switch (head->direction)                                                                // ������ ������ � ����������� �� �����������
    {
        case LEFT:
            head->x = (head->x <= 0) ? max_x : head->x - 1;                                 // ����������� �������� �� �����������
            break;
        case RIGHT:
            head->x = (head->x >= max_x) ? 0 : head->x + 1;
            break;
        case UP:
            head->y = (head->y <= 0) ? max_y : head->y - 1;                                 // ����������� �������� �� ���������
            break;
        case DOWN:
            head->y = (head->y >= max_y) ? 0 : head->y + 1;
            break;
    }
    mvprintw(head->y, head->x, "%c", ch);                                                   // ��������� ������ � ����� �������
    refresh();                                                                              // �������� �����
}

// ��������� ����������� ������
void changeDirection(struct snake_t* snake, const int32_t key)
{
    int lower_key = tolower(key);  // ���������� � ������� ��������

    for (int i = 0; i < CONTROLS; i++)
    {
        if (lower_key == default_controls[i].down && snake->direction != UP)
            snake->direction = DOWN;
        else if (lower_key == default_controls[i].up && snake->direction != DOWN)
            snake->direction = UP;
        else if (lower_key == default_controls[i].right && snake->direction != LEFT)
            snake->direction = RIGHT;
        else if (lower_key == default_controls[i].left && snake->direction != RIGHT)
            snake->direction = LEFT;
    }
}

// �������� ������ ������
void goTail(struct snake_t *head)
{
    char ch = '*';                                                                          // ������ ������
    mvprintw(head->tail[head->tsize - 1].y, head->tail[head->tsize - 1].x, " ");            // ������ ������ �����
    for (size_t i = head->tsize - 1; i > 0; i--)                                            // ��������� ����� �����
    {
        head->tail[i] = head->tail[i - 1];
        mvprintw(head->tail[i].y, head->tail[i].x, "%c", ch);                               // ��������� �����
    }
    head->tail[0].x = head->x;                                                              // ������ ����� ������ ������� �� �������
    head->tail[0].y = head->y;
}

// ���������� ������ ������
void addTail(snake_t* snake)
{
    if (snake->tsize < MAX_TAIL_SIZE)                                                       // ��������, �� ��������� �� ������������ ������ ������
    {
        snake->tsize++;                                                                     // ���������� �����
    }
}

// ���������� ��� � ��������� ������
void putFood(food_t* food, int count)
{
    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);                                                         // ������� ������� ������
    for (int i = 0; i < count; i++)
    {
        if (!food[i].active)                                                                // ���� ��� �� �������
        {
            food[i].x = rand() % max_x;                                                     // ��������� ��������� ����������
            food[i].y = rand() % max_y;
            food[i].active = 1;                                                             // ��������� ���
            food[i].spawn_time = time(NULL);                                                // �������� ����� ���������
            mvprintw(food[i].y, food[i].x, "$");                                            // ��������� ���
        }
    }
}

// �������� � ���������� ���
void refreshFood(food_t* food, int count)
{
    time_t now = time(NULL);
    for (int i = 0; i < count; i++)
    {
        if (!food[i].active || difftime(now, food[i].spawn_time) > FOOD_EXPIRE_SECONDS)     // ��� �������� ��� �������
        {
            food[i].active = 0;                                                             // ����������� ���
            putFood(&food[i], 1);                                                           // ��������� ����� ���
        }
    }
}

// ��������, ����� �� ������ ���
int haveEat(snake_t* snake, food_t* food, int count)
{
    for (int i = 0; i < count; i++)
    {
        if (food[i].active && snake->x == food[i].x && snake->y == food[i].y)               // ���������� ���������
        {
            food[i].active = 0;                                                             // ����������� ��������� ���
            addTail(snake);                                                                 // ���������� �����
            return 1;
        }
    }
    return 0;
}

int main()
{
    initscr();                                                                              // ������������� ncurses
    timeout(0);                                                                             // �� �������� ������� getch()
    noecho();                                                                               // �� ��������� �������� �������
    curs_set(0);                                                                            // ������� ������
    keypad(stdscr, TRUE);                                                                   // ������� ��������� �������������� ������

    srand(time(NULL));                                                                      // ������������� ��������� ��������� �����
    snake_t *snake = (snake_t*)malloc(sizeof(snake_t));                                     // ������� ������ ��� ������
    food_t food[FOOD_COUNT] = {0};                                                          // ������������� ������ ���

    initSnake(snake, START_TAIL_SIZE, 10, 10);                                              // ������������� ������
    putFood(food, FOOD_COUNT);                                                              // �������� ���

    clock_t start_time = clock();                                                           // ������� ������ �������
    clock_t current_time = start_time;

    while (1)
    {
        current_time = clock();                                                             // ������� �����
        double elapsed = (double)(current_time - start_time) / CLOCKS_PER_SEC;              // ����� � ��������
        if (elapsed >= 0.1)                                                                 // ������� 100 �����������
        {
            start_time = current_time;                                                      // �������� ����� ������
            int ch = getch();                                                               // ����� ������
            if (ch == STOP_GAME) break;                                                     // ���� ������� "q", �� �������� ����

            changeDirection(snake, ch);                                                     // ������� �����������
            go(snake);                                                                      // ������ ������
            goTail(snake);                                                                  // ������ �����
            if (haveEat(snake, food, FOOD_COUNT)) {}                                        // �������� ��������� ���

            refreshFood(food, FOOD_COUNT);                                                  // �������� ���
            refresh();                                                                      // �������� �����
        }
    }

    endwin();                                                                               // �������� ������ � ncurses
    free(snake->tail);                                                                      // ���������� ������
    free(snake);                                                                            // ���������� ������
    return 0;
}

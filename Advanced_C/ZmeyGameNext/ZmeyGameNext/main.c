#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include <inttypes.h>
#include <string.h>
#include <unistd.h>

#define MIN_Y 2
#define CONTROLS 2
#define FOOD_COUNT 5
enum { LEFT = 1, UP, RIGHT, DOWN, STOP_GAME = 'q' };
enum { MAX_TAIL_SIZE = 100, START_TAIL_SIZE = 3, MAX_FOOD_SIZE = 20, FOOD_EXPIRE_SECONDS = 10 };

// ��������� ���������� ��� ��������� ����� �����
struct control_buttons {
    int down;
    int up;
    int left;
    int right;
};

// ������ ��� ���������� ��������� � ��������� WSAD
struct control_buttons default_controls[CONTROLS] = {
    { KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT }, // ���������� ��������� (��� ������ ������)
    { 's', 'w', 'a', 'd' }                     // ���������� WSAD (��� ������ ������)
};

// ��������� ��� ������ ������
typedef struct tail_t {
    int x; // ���������� X ������
    int y; // ���������� Y ������
} tail_t;

// ��������� ��� ������
typedef struct snake_t {
    int x; // ���������� X ������ ������
    int y; // ���������� Y ������ ������
    int direction; // ������� ����������� �������� ������
    size_t tsize; // ������� ������ ������
    struct tail_t* tail; // ������, ���������� �������� ������
    int player; // ����� ������ (1 ��� 2)
    int food_eaten; // ���������� ��������� ���
} snake_t;

// ��������� ��� ���
typedef struct food_t {
    int x; // ���������� X ���
    int y; // ���������� Y ���
    int active; // ���� ���������� (1 - ��������, 0 - �������)
    time_t spawn_time; // ����� ��������� ���
} food_t;

// ��������� �������
void refreshFood(food_t food[], int count, snake_t* snake1, snake_t* snake2);
int isCollideWithSnake(snake_t* snake, int x, int y);
int isCrush(snake_t* snake, snake_t* otherSnake);
void drawStartMenu();
void drawSnakeScores(snake_t* snake1, snake_t* snake2);

// ������� ��� ����������� ������ � ������ ������
void setColor(int snakeNumber) {
    if (snakeNumber == 1) {
        attron(COLOR_PAIR(1)); // ������ 1 (�������)
    } else if (snakeNumber == 2) {
        attron(COLOR_PAIR(2)); // ������� ��� ������ ������
    }
}

// ������������� ������ ������
void initTail(struct tail_t t[], size_t size) {
    struct tail_t init_t = { 0, 0 };
    for (size_t i = 0; i < size; i++) {
        t[i] = init_t; // ������������ ��������� ���������� ������ � (0, 0)
    }
}

// ������������� ������ ������
void initHead(struct snake_t* head, int x, int y, int player) {
    head->x = x; // ������������� ��������� ���������� X
    head->y = y; // ������������� ��������� ���������� Y
    head->direction = RIGHT; // ��������� ����������� - ������
    head->player = player; // ����� ������
    head->food_eaten = 0; // �������������� ������� ��������� ���
}

// ������������� ���� ������
void initSnake(snake_t* head, size_t size, int x, int y, int player) {
    tail_t* tail = (tail_t*)malloc(MAX_TAIL_SIZE * sizeof(tail_t)); // ������� ������ ��� �����
    if (tail == NULL) {
        perror("Unable to allocate memory for snake tail");
        exit(1); // ��������� ��������� � �������
    }
    initTail(tail, MAX_TAIL_SIZE); // ������������� �����
    initHead(head, x, y, player); // ������������� ������
    head->tail = tail; // ���������� ����� � ������
    head->tsize = size + 1; // ������������ ������ ������
}

// �������� ������ ������
void go(snake_t* head) {
    char ch = '@'; // ������ ������ ������
    int max_x = 0, max_y = 0;
    getmaxyx(stdscr, max_y, max_x); // ������� ������� ���� ���������

    // �������� �� ����� �� ������� ������
    head->x = (head->x < 0) ? 0 : (head->x >= max_x) ? max_x - 1 : head->x;
    head->y = (head->y < 0) ? 0 : (head->y >= max_y) ? max_y - 1 : head->y;

    mvprintw(head->y, head->x, " "); // ������ ������ ������� ������
    switch (head->direction) // ������ ������ � ����������� �� �����������
    {
    case LEFT:
        head->x = (head->x <= 0) ? max_x - 1 : head->x - 1; // ����������� �������� �� �����������
        break;
    case RIGHT:
        head->x = (head->x >= max_x - 1) ? 0 : head->x + 1;
        break;
    case UP:
        head->y = (head->y <= 0) ? max_y - 1 : head->y - 1; // ����������� �������� �� ���������
        break;
    case DOWN:
        head->y = (head->y >= max_y - 1) ? 0 : head->y + 1;
        break;
    }
    setColor(head->player); // ������������� ���� ������ � ����������� �� ������
    mvprintw(head->y, head->x, "%c", ch); // ��������� ������ � ����� �������
    refresh(); // ��������� �����
}

// �������� ������ ������
void goTail(snake_t* snake) {
    mvprintw(snake->tail[snake->tsize - 1].y, snake->tail[snake->tsize - 1].x, " "); // ������� ��������� �������
    for (size_t i = snake->tsize - 1; i > 0; i--) {
        snake->tail[i] = snake->tail[i - 1];
        mvprintw(snake->tail[i].y, snake->tail[i].x, "o"); // ���������� �����
    }
    snake->tail[0].x = snake->x;
    snake->tail[0].y = snake->y;
}

// �������� ������������ ������ � ������� ��� ������ �������
int isCrush(snake_t* snake, snake_t* otherSnake) {
    // �������� ������������ � ����������� �������
    for (size_t i = 1; i < snake->tsize; i++) {
        if (snake->x == snake->tail[i].x && snake->y == snake->tail[i].y) {
            return 1; // ������������ � �������
        }
    }

    // �������� ������������ � ������ �������
    if (snake->x == otherSnake->x && snake->y == otherSnake->y) {
        return 1; // ������������ � ������ �������
    }

    return 0; // ���� ������������ ���
}

// �������� �������� � �������
int isCollideWithSnake(snake_t* snake, int x, int y) {
    if (snake->x == x && snake->y == y) return 1;
    for (size_t i = 0; i < snake->tsize; i++) {
        if (snake->tail[i].x == x && snake->tail[i].y == y) return 1;
    }
    return 0;
}


// ��������� ����������� �������� ������
void changeDirection(snake_t* snake, int ch) {
    if (ch == default_controls[snake->player - 1].up && snake->direction != DOWN) snake->direction = UP;
    else if (ch == default_controls[snake->player - 1].down && snake->direction != UP) snake->direction = DOWN;
    else if (ch == default_controls[snake->player - 1].left && snake->direction != RIGHT) snake->direction = LEFT;
    else if (ch == default_controls[snake->player - 1].right && snake->direction != LEFT) snake->direction = RIGHT;
}

// ������� ���������� ���
void putFood(food_t food[], int count, snake_t* snake1, snake_t* snake2) {
    for (int i = 0; i < count; i++) {
        // �������� ���������� ��� � ��������� ������
        do {
            food[i].x = rand() % COLS;
            food[i].y = rand() % LINES;
        } while (isCollideWithSnake(snake1, food[i].x, food[i].y) || isCollideWithSnake(snake2, food[i].x, food[i].y));

        food[i].active = 1; // �������� ��� ��� ��������
        food[i].spawn_time = time(NULL); // ����� ��������� ���

        // ������������� ���� ��� � ���������� �
        attron(COLOR_PAIR(3)); // ���� ���
        mvprintw(food[i].y, food[i].x, "$");
        attroff(COLOR_PAIR(3)); // ���������� ����
        refresh(); // ��������� �����
    }
}


// �������� �� �������� ���
int haveEat(snake_t* snake, food_t food[], int count) {
    for (int i = 0; i < count; i++) {
        // ���������, ��������� �� ���������� ��� � ����
        if (food[i].active && snake->x == food[i].x && snake->y == food[i].y) {
            // ���� ��� �������, �������� � ��� ����������
            food[i].active = 0;
            // ����������� ������ ������ � ������� ��������� ���
            snake->tsize++;
            snake->food_eaten++;  // ����������� ������� ��������� ���
            return 1; // ���������� 1, ���� ��� �������
        }
    }
    return 0; // ���� ��� �� �������, ���������� 0
}



// ���������� ���
void refreshFood(food_t food[], int count, snake_t* snake1, snake_t* snake2) {
    time_t current_time = time(NULL); // ������� �����
    for (int i = 0; i < count; i++) {
        // ���� ��� �������� ��� ���� �������, ���������� �����
        if (!food[i].active || (current_time - food[i].spawn_time > FOOD_EXPIRE_SECONDS)) {
            do {
                food[i].x = rand() % COLS;
                food[i].y = rand() % LINES;
            } while (isCollideWithSnake(snake1, food[i].x, food[i].y) || isCollideWithSnake(snake2, food[i].x, food[i].y));

            food[i].active = 1; // �������� ��� ��� ��������
            food[i].spawn_time = current_time; // ��������� ����� ��������� ���

            // ������������� ���� ��� � ���������� �
            attron(COLOR_PAIR(3)); // ���� ���
            mvprintw(food[i].y, food[i].x, "$");
            attroff(COLOR_PAIR(3)); // ���������� ����
            refresh(); // ��������� �����
        }
    }
}



// ��������� ����
void drawStartMenu() {
    clear();
    box(stdscr, 0, 0); // ������ �����
    mvprintw(5, 10, "Welcome to Snake Game!");
    mvprintw(7, 10, "Press Enter to start the game.");
    refresh();
    timeout(-1); // ��������� getch(), ���� �� ����� ����� ������
    while (getch() != '\n') { // ������� ������� Enter
        // ��� ������������� ����� ������, ���� ������� ����������
    }
    timeout(100); // ���������� timeout ����� ����, ����� ������ ������� ���� � ��������� ���������
    clear(); // ������� ����� ����� ������ ����
}

void drawSnakeScores(snake_t* snake1, snake_t* snake2) {
    mvprintw(0, 0, "Player 1 Score: %d", snake1->food_eaten);
    mvprintw(0, COLS - 20, "Player 2 Score: %d", snake2->food_eaten);
}

int main() {
    initscr(); // �������������� ncurses
    timeout(100); // ������ ����� �������� � 100 ��
    noecho(); // ��������� ��� �����
    cbreak(); // ��������� �����������
    keypad(stdscr, TRUE); // �������� ��������� ����������� ������, ������� �������

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK); // ������� ��� ������ ������
    init_pair(2, COLOR_GREEN, COLOR_BLACK); // ������� ��� ������ ������
    init_pair(3, COLOR_YELLOW, COLOR_BLACK); // ������ ��� ���

    srand(time(NULL));

    // ������������� ����
    snake_t snake1, snake2;
    initSnake(&snake1, START_TAIL_SIZE, 20, 10, 1);
    initSnake(&snake2, START_TAIL_SIZE, 40, 10, 2);

    // ������������� ���
    food_t food[FOOD_COUNT];
    putFood(food, FOOD_COUNT, &snake1, &snake2);

    // ���������� ��������� ���� � ���� ������� �������
    drawStartMenu();  // ��������� ����
    // ����� ����� ��� ����� ����� ������ ���� ��� ��������������� �������� �����

    // ������� ������� ����
    while (1) {
        drawSnakeScores(&snake1, &snake2); // ���������� ����
        go(&snake1); // ������� ������ ������
        goTail(&snake1); // ������� ����� ������ ������
        go(&snake2); // ������� ������ ������
        goTail(&snake2); // ������� ����� ������ ������

        if (haveEat(&snake1, food, FOOD_COUNT)) { // ���������, �� ����� �� ������ ������ ���
            putFood(food, FOOD_COUNT, &snake1, &snake2); // ��������� ����� ���
        }
        if (haveEat(&snake2, food, FOOD_COUNT)) { // ���������, �� ����� �� ������ ������ ���
            putFood(food, FOOD_COUNT, &snake1, &snake2); // ��������� ����� ���
        }

        refreshFood(food, FOOD_COUNT, &snake1, &snake2); // ��������� ���

        // ���� ����������� ������
        int ch = getch();
        if (ch == STOP_GAME) break; // ��������� ����, ���� ������ 'q'
        changeDirection(&snake1, ch); // �������� ����������� ������ ������
        changeDirection(&snake2, ch); // �������� ����������� ������ ������

        if (isCrush(&snake1, &snake2)) break; // ��������� ����, ���� ������ �����������
    }

    endwin(); // ��������� ������ � ncurses
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include <inttypes.h>
#include <string.h>
#include <unistd.h>

#define MIN_Y 2
#define FRAME_DELAY 100000

enum {LEFT=1, UP, RIGHT, DOWN, STOP_GAME='q'};
enum {MAX_TAIL_SIZE=100, START_TAIL_SIZE=7};

typedef struct tail_t
{
    int x;
    int y;
} tail_t;

typedef struct snake_t
{
    int x;
    int y;
    int direction;
    size_t tsize;
    tail_t *tail;
    struct control_buttons
    {
        int down;
        int up;
        int left;
        int right;
    } controls;
} snake_t;

void initTail(tail_t t[], size_t size)
{
    for(size_t i = 0; i < size; i++)
    {
        t[i].x = -1;
        t[i].y = -1;
    }
}

void initHead(snake_t *head, int x, int y)
{
    head->x = x;
    head->y = y;
    head->direction = RIGHT;
}

void initSnake(snake_t *head, size_t size, int x, int y)
{
    tail_t* tail = (tail_t*) malloc(MAX_TAIL_SIZE * sizeof(tail_t));
    initTail(tail, MAX_TAIL_SIZE);
    initHead(head, x, y);
    head->tail = tail;
    head->tsize = size + 1;
    head->controls = (struct control_buttons) {KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT};
}

void go(snake_t *head)
{
    int max_x = 0, max_y = 0;
    getmaxyx(stdscr, max_y, max_x);
    mvprintw(head->y, head->x, " ");

    switch (head->direction) {
        case LEFT:  head->x--; break;
        case RIGHT: head->x++; break;
        case UP:    head->y--; break;
        case DOWN:  head->y++; break;
    }
    if (head->x < 0 || head->x >= max_x || head->y < MIN_Y || head->y >= max_y) // Проверяю выход за границы экрана
    {
        mvprintw(max_y / 2, max_x / 2 - 5, "GAME OVER");
        refresh();
        usleep(2000000);
        endwin();
        exit(0);
    }

    mvprintw(head->y, head->x, "@");
    refresh();
}

void goTail(snake_t *head)
{
    mvprintw(head->tail[head->tsize - 1].y, head->tail[head->tsize - 1].x, " ");
    for (size_t i = head->tsize - 1; i > 0; i--)
    {
        head->tail[i] = head->tail[i - 1];
    }
    head->tail[0].x = head->x;
    head->tail[0].y = head->y;

    for (size_t i = 1; i < head->tsize; i++)
    {
        mvprintw(head->tail[i].y, head->tail[i].x, "*");

        if (head->x == head->tail[i].x && head->y == head->tail[i].y) // Проверяю столкновение с хвостом
        {
            mvprintw(LINES / 2, COLS / 2 - 5, "GAME OVER");
            refresh();
            usleep(2000000);
            endwin();
            exit(0);
        }
    }
}

void changeDirection(snake_t* snake, const int key)
{
    if (key == snake->controls.down && snake->direction != UP) snake->direction = DOWN;
    else if (key == snake->controls.up && snake->direction != DOWN) snake->direction = UP;
    else if (key == snake->controls.right && snake->direction != LEFT) snake->direction = RIGHT;
    else if (key == snake->controls.left && snake->direction != RIGHT) snake->direction = LEFT;
}

int main(void)
{
    snake_t* snake = (snake_t*)malloc(sizeof(snake_t));
    initSnake(snake, START_TAIL_SIZE, 10, 10);

    initscr();
    keypad(stdscr, TRUE);
    raw();
    noecho();
    curs_set(FALSE);
    mvprintw(0, 0, "Control the arrows. Press 'q' for EXIT");

    int key_pressed = 0;
    clock_t last_time = clock();
    int frame_count = 0;
    double fps = 0.0;
    clock_t start_time = clock();

    while (key_pressed != STOP_GAME)
    {
        key_pressed = getch();
        clock_t current_time = clock();
        frame_count++;

        if ((current_time - last_time) >= (FRAME_DELAY / 1000.0 * CLOCKS_PER_SEC / 1000))
        {
            last_time = current_time;
            go(snake);
            goTail(snake);
            changeDirection(snake, key_pressed);
        }

        if ((current_time - start_time) >= CLOCKS_PER_SEC) // Вычисляю FPS
        {
            fps = frame_count / ((double)(current_time - start_time) / CLOCKS_PER_SEC);
            start_time = current_time;
            frame_count = 0;

            mvprintw(1, 0, "FPS: %.2f", fps); // Показываю FPS
            refresh();
        }
    }

    free(snake->tail);
    free(snake);
    endwin();
    return 0;
}

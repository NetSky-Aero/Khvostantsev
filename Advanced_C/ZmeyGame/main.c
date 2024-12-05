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

// Структура управления для различных типов ввода
struct control_buttons
{
    int down;
    int up;
    int left;
    int right;
};

// Массив для управления стрелками и клавишами WSAD
struct control_buttons default_controls[CONTROLS] =
{
    {KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT},          // Управление стрелками
    {'s', 'w', 'a', 'd'},                             // Управление WSAD (нижний регистр)
    {'S', 'W', 'A', 'D'}                              // Управление WSAD (верхний регистр)
};

// Структура для хвоста змейки
typedef struct tail_t
{
    int x;                                                                                  // Координата X хвоста
    int y;                                                                                  // Координата Y хвоста
} tail_t;

// Структура для змейки
typedef struct snake_t
{
    int x;                                                                                  // Координата X головы змейки
    int y;                                                                                  // Координата Y головы змейки
    int direction;                                                                          // Текущее направление движения змейки
    size_t tsize;                                                                           // Текущий размер хвоста
    struct tail_t *tail;                                                                    // Массив, содержащий сегменты хвоста
} snake_t;

// Структура для еды
typedef struct food_t
{
    int x;                                                                                  // Координата X еды
    int y;                                                                                  // Координата Y еды
    int active;                                                                             // Флаг активности (1 - активное, 0 - съедено)
    time_t spawn_time;                                                                      // Время появления еды
} food_t;

// Инициализация хвоста змейки
void initTail(struct tail_t t[], size_t size)
{
    struct tail_t init_t = {0, 0};
    for (size_t i = 0; i < size; i++)
    {
        t[i] = init_t;                                                                      // Устанавливаю начальные координаты хвоста в (0, 0)
    }
}

// Инициализация головы змейки
void initHead(struct snake_t *head, int x, int y)
{
    head->x = x;                                                                            // Устанавливаем начальную координату X
    head->y = y;                                                                            // Устанавливаем начальную координату Y
    head->direction = RIGHT;                                                                // Начальное направление - вправо
}

// Инициализация всей змейки
void initSnake(snake_t *head, size_t size, int x, int y)
{
    tail_t* tail = (tail_t*) malloc(MAX_TAIL_SIZE * sizeof(tail_t));                        // Выделяю память под хвост
    initTail(tail, MAX_TAIL_SIZE);                                                          // Инициализирую хвост
    initHead(head, x, y);                                                                   // Инициализирую голову
    head->tail = tail;                                                                      // Привязываю хвост к змейке
    head->tsize = size + 1;                                                                 // Устанавливаю размер хвоста
}

// Движение головы змейки
void go(struct snake_t *head)
{
    char ch = '@';                                                                          // Символ головы змейки
    int max_x = 0, max_y = 0;
    getmaxyx(stdscr, max_y, max_x);                                                         // Получаю размеры окна терминала

    mvprintw(head->y, head->x, " ");                                                        // Убираю старую позицию головы
    switch (head->direction)                                                                // Двигаю голову в зависимости от направления
    {
        case LEFT:
            head->x = (head->x <= 0) ? max_x : head->x - 1;                                 // Циклическое движение по горизонтали
            break;
        case RIGHT:
            head->x = (head->x >= max_x) ? 0 : head->x + 1;
            break;
        case UP:
            head->y = (head->y <= 0) ? max_y : head->y - 1;                                 // Циклическое движение по вертикали
            break;
        case DOWN:
            head->y = (head->y >= max_y) ? 0 : head->y + 1;
            break;
    }
    mvprintw(head->y, head->x, "%c", ch);                                                   // Отображаю голову в новой позиции
    refresh();                                                                              // Обновляю экран
}

// Изменение направления змейки
void changeDirection(struct snake_t* snake, const int32_t key)
{
    int lower_key = tolower(key);  // Приведение к нижнему регистру

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

// Движение хвоста змейки
void goTail(struct snake_t *head)
{
    char ch = '*';                                                                          // Символ хвоста
    mvprintw(head->tail[head->tsize - 1].y, head->tail[head->tsize - 1].x, " ");            // Удаляю старый хвост
    for (size_t i = head->tsize - 1; i > 0; i--)                                            // Перемещаю хвост вперёд
    {
        head->tail[i] = head->tail[i - 1];
        mvprintw(head->tail[i].y, head->tail[i].x, "%c", ch);                               // Отображаю хвост
    }
    head->tail[0].x = head->x;                                                              // Первая часть хвоста следует за головой
    head->tail[0].y = head->y;
}

// Увеличение хвоста змейки
void addTail(snake_t* snake)
{
    if (snake->tsize < MAX_TAIL_SIZE)                                                       // Проверяю, не достигнут ли максимальный размер хвоста
    {
        snake->tsize++;                                                                     // Увеличиваю хвост
    }
}

// Размещение еды в случайных местах
void putFood(food_t* food, int count)
{
    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);                                                         // Получаю размеры экрана
    for (int i = 0; i < count; i++)
    {
        if (!food[i].active)                                                                // Если еда не активна
        {
            food[i].x = rand() % max_x;                                                     // Генерирую случайные координаты
            food[i].y = rand() % max_y;
            food[i].active = 1;                                                             // Активирую еду
            food[i].spawn_time = time(NULL);                                                // Фиксирую время появления
            mvprintw(food[i].y, food[i].x, "$");                                            // Отображаю еду
        }
    }
}

// Проверка и обновление еды
void refreshFood(food_t* food, int count)
{
    time_t now = time(NULL);
    for (int i = 0; i < count; i++)
    {
        if (!food[i].active || difftime(now, food[i].spawn_time) > FOOD_EXPIRE_SECONDS)     // Еда устарела или съедена
        {
            food[i].active = 0;                                                             // Деактивирую еду
            putFood(&food[i], 1);                                                           // Генерирую новую еду
        }
    }
}

// Проверка, съела ли змейка еду
int haveEat(snake_t* snake, food_t* food, int count)
{
    for (int i = 0; i < count; i++)
    {
        if (food[i].active && snake->x == food[i].x && snake->y == food[i].y)               // Координаты совпадают
        {
            food[i].active = 0;                                                             // Деактивирую съеденную еду
            addTail(snake);                                                                 // Увеличиваю хвост
            return 1;
        }
    }
    return 0;
}

int main()
{
    initscr();                                                                              // Инициализирую ncurses
    timeout(0);                                                                             // Не блокирую функцию getch()
    noecho();                                                                               // Не отображаю вводимые символы
    curs_set(0);                                                                            // Скрываю курсор
    keypad(stdscr, TRUE);                                                                   // Включаю поддержку функциональных клавиш

    srand(time(NULL));                                                                      // Инициализирую генератор случайных чисел
    snake_t *snake = (snake_t*)malloc(sizeof(snake_t));                                     // Выделяю память для змейки
    food_t food[FOOD_COUNT] = {0};                                                          // Инициализирую массив еды

    initSnake(snake, START_TAIL_SIZE, 10, 10);                                              // Инициализирую змейку
    putFood(food, FOOD_COUNT);                                                              // Размещаю еду

    clock_t start_time = clock();                                                           // Начинаю отсчет времени
    clock_t current_time = start_time;

    while (1)
    {
        current_time = clock();                                                             // Текущее время
        double elapsed = (double)(current_time - start_time) / CLOCKS_PER_SEC;              // Время в секундах
        if (elapsed >= 0.1)                                                                 // Таймаут 100 миллисекунд
        {
            start_time = current_time;                                                      // Обновляю время начала
            int ch = getch();                                                               // Читаю символ
            if (ch == STOP_GAME) break;                                                     // Если нажимаю "q", то завершаю игру

            changeDirection(snake, ch);                                                     // Изменяю направление
            go(snake);                                                                      // Двигаю голову
            goTail(snake);                                                                  // Двигаю хвост
            if (haveEat(snake, food, FOOD_COUNT)) {}                                        // Проверяю съеденную еду

            refreshFood(food, FOOD_COUNT);                                                  // Обновляю еду
            refresh();                                                                      // Обновляю экран
        }
    }

    endwin();                                                                               // Завершаю работу с ncurses
    free(snake->tail);                                                                      // Освобождаю память
    free(snake);                                                                            // Освобождаю память
    return 0;
}

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

// Структура управления для различных типов ввода
struct control_buttons {
    int down;
    int up;
    int left;
    int right;
};

// Массив для управления стрелками и клавишами WSAD
struct control_buttons default_controls[CONTROLS] = {
    { KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT }, // Управление стрелками (для второй змейки)
    { 's', 'w', 'a', 'd' }                     // Управление WSAD (для первой змейки)
};

// Структура для хвоста змейки
typedef struct tail_t {
    int x; // Координата X хвоста
    int y; // Координата Y хвоста
} tail_t;

// Структура для змейки
typedef struct snake_t {
    int x; // Координата X головы змейки
    int y; // Координата Y головы змейки
    int direction; // Текущее направление движения змейки
    size_t tsize; // Текущий размер хвоста
    struct tail_t* tail; // Массив, содержащий сегменты хвоста
    int player; // Номер игрока (1 или 2)
    int food_eaten; // Количество съеденной еды
} snake_t;

// Структура для еды
typedef struct food_t {
    int x; // Координата X еды
    int y; // Координата Y еды
    int active; // Флаг активности (1 - активное, 0 - съедено)
    time_t spawn_time; // Время появления еды
} food_t;

// Прототипы функций
void refreshFood(food_t food[], int count, snake_t* snake1, snake_t* snake2);
int isCollideWithSnake(snake_t* snake, int x, int y);
int isCrush(snake_t* snake, snake_t* otherSnake);
void drawStartMenu();
void drawSnakeScores(snake_t* snake1, snake_t* snake2);

// Функция для отображения змейки с нужным цветом
void setColor(int snakeNumber) {
    if (snakeNumber == 1) {
        attron(COLOR_PAIR(1)); // Змейка 1 (красная)
    } else if (snakeNumber == 2) {
        attron(COLOR_PAIR(2)); // Зеленый для второй змейки
    }
}

// Инициализация хвоста змейки
void initTail(struct tail_t t[], size_t size) {
    struct tail_t init_t = { 0, 0 };
    for (size_t i = 0; i < size; i++) {
        t[i] = init_t; // Устанавливаю начальные координаты хвоста в (0, 0)
    }
}

// Инициализация головы змейки
void initHead(struct snake_t* head, int x, int y, int player) {
    head->x = x; // Устанавливаем начальную координату X
    head->y = y; // Устанавливаем начальную координату Y
    head->direction = RIGHT; // Начальное направление - вправо
    head->player = player; // Номер игрока
    head->food_eaten = 0; // Инициализируем счетчик съеденной еды
}

// Инициализация всей змейки
void initSnake(snake_t* head, size_t size, int x, int y, int player) {
    tail_t* tail = (tail_t*)malloc(MAX_TAIL_SIZE * sizeof(tail_t)); // Выделяю память под хвост
    if (tail == NULL) {
        perror("Unable to allocate memory for snake tail");
        exit(1); // Завершаем программу с ошибкой
    }
    initTail(tail, MAX_TAIL_SIZE); // Инициализирую хвост
    initHead(head, x, y, player); // Инициализирую голову
    head->tail = tail; // Привязываю хвост к змейке
    head->tsize = size + 1; // Устанавливаю размер хвоста
}

// Движение головы змейки
void go(snake_t* head) {
    char ch = '@'; // Символ головы змейки
    int max_x = 0, max_y = 0;
    getmaxyx(stdscr, max_y, max_x); // Получаю размеры окна терминала

    // Проверка на выход за пределы экрана
    head->x = (head->x < 0) ? 0 : (head->x >= max_x) ? max_x - 1 : head->x;
    head->y = (head->y < 0) ? 0 : (head->y >= max_y) ? max_y - 1 : head->y;

    mvprintw(head->y, head->x, " "); // Убираю старую позицию головы
    switch (head->direction) // Двигаю голову в зависимости от направления
    {
    case LEFT:
        head->x = (head->x <= 0) ? max_x - 1 : head->x - 1; // Циклическое движение по горизонтали
        break;
    case RIGHT:
        head->x = (head->x >= max_x - 1) ? 0 : head->x + 1;
        break;
    case UP:
        head->y = (head->y <= 0) ? max_y - 1 : head->y - 1; // Циклическое движение по вертикали
        break;
    case DOWN:
        head->y = (head->y >= max_y - 1) ? 0 : head->y + 1;
        break;
    }
    setColor(head->player); // Устанавливаем цвет змейки в зависимости от игрока
    mvprintw(head->y, head->x, "%c", ch); // Отображаю голову в новой позиции
    refresh(); // Обновляем экран
}

// Движение хвоста змейки
void goTail(snake_t* snake) {
    mvprintw(snake->tail[snake->tsize - 1].y, snake->tail[snake->tsize - 1].x, " "); // Убираем последний сегмент
    for (size_t i = snake->tsize - 1; i > 0; i--) {
        snake->tail[i] = snake->tail[i - 1];
        mvprintw(snake->tail[i].y, snake->tail[i].x, "o"); // Отображаем хвост
    }
    snake->tail[0].x = snake->x;
    snake->tail[0].y = snake->y;
}

// Проверка столкновения змейки с хвостом или другой змейкой
int isCrush(snake_t* snake, snake_t* otherSnake) {
    // Проверка столкновения с собственным хвостом
    for (size_t i = 1; i < snake->tsize; i++) {
        if (snake->x == snake->tail[i].x && snake->y == snake->tail[i].y) {
            return 1; // Столкновение с хвостом
        }
    }

    // Проверка столкновения с другой змейкой
    if (snake->x == otherSnake->x && snake->y == otherSnake->y) {
        return 1; // Столкновение с другой змейкой
    }

    return 0; // Если столкновения нет
}

// Проверка коллизии с змейкой
int isCollideWithSnake(snake_t* snake, int x, int y) {
    if (snake->x == x && snake->y == y) return 1;
    for (size_t i = 0; i < snake->tsize; i++) {
        if (snake->tail[i].x == x && snake->tail[i].y == y) return 1;
    }
    return 0;
}


// Изменение направления движения змейки
void changeDirection(snake_t* snake, int ch) {
    if (ch == default_controls[snake->player - 1].up && snake->direction != DOWN) snake->direction = UP;
    else if (ch == default_controls[snake->player - 1].down && snake->direction != UP) snake->direction = DOWN;
    else if (ch == default_controls[snake->player - 1].left && snake->direction != RIGHT) snake->direction = LEFT;
    else if (ch == default_controls[snake->player - 1].right && snake->direction != LEFT) snake->direction = RIGHT;
}

// Функция размещения еды
void putFood(food_t food[], int count, snake_t* snake1, snake_t* snake2) {
    for (int i = 0; i < count; i++) {
        // Пытаемся разместить еду в случайных местах
        do {
            food[i].x = rand() % COLS;
            food[i].y = rand() % LINES;
        } while (isCollideWithSnake(snake1, food[i].x, food[i].y) || isCollideWithSnake(snake2, food[i].x, food[i].y));

        food[i].active = 1; // Помечаем еду как активную
        food[i].spawn_time = time(NULL); // Время появления еды

        // Устанавливаем цвет еды и отображаем её
        attron(COLOR_PAIR(3)); // Цвет еды
        mvprintw(food[i].y, food[i].x, "$");
        attroff(COLOR_PAIR(3)); // Сбрасываем цвет
        refresh(); // Обновляем экран
    }
}


// Проверка на поедание еды
int haveEat(snake_t* snake, food_t food[], int count) {
    for (int i = 0; i < count; i++) {
        // Проверяем, совпадают ли координаты еды и змеи
        if (food[i].active && snake->x == food[i].x && snake->y == food[i].y) {
            // Если еда съедена, помечаем её как неактивную
            food[i].active = 0;
            // Увеличиваем размер змейки и счетчик съеденной еды
            snake->tsize++;
            snake->food_eaten++;  // Увеличиваем счетчик съеденной еды
            return 1; // Возвращаем 1, если еда съедена
        }
    }
    return 0; // Если еда не съедена, возвращаем 0
}



// Обновление еды
void refreshFood(food_t food[], int count, snake_t* snake1, snake_t* snake2) {
    time_t current_time = time(NULL); // Текущее время
    for (int i = 0; i < count; i++) {
        // Если еда устарела или была съедена, генерируем новую
        if (!food[i].active || (current_time - food[i].spawn_time > FOOD_EXPIRE_SECONDS)) {
            do {
                food[i].x = rand() % COLS;
                food[i].y = rand() % LINES;
            } while (isCollideWithSnake(snake1, food[i].x, food[i].y) || isCollideWithSnake(snake2, food[i].x, food[i].y));

            food[i].active = 1; // Помечаем еду как активную
            food[i].spawn_time = current_time; // Обновляем время появления еды

            // Устанавливаем цвет еды и отображаем её
            attron(COLOR_PAIR(3)); // Цвет еды
            mvprintw(food[i].y, food[i].x, "$");
            attroff(COLOR_PAIR(3)); // Сбрасываем цвет
            refresh(); // Обновляем экран
        }
    }
}



// Стартовое меню
void drawStartMenu() {
    clear();
    box(stdscr, 0, 0); // Рисуем рамку
    mvprintw(5, 10, "Welcome to Snake Game!");
    mvprintw(7, 10, "Press Enter to start the game.");
    refresh();
    timeout(-1); // Блокируем getch(), пока не будет нажат символ
    while (getch() != '\n') { // Ожидаем нажатие Enter
        // Нет необходимости ждать дважды, одна попытка достаточна
    }
    timeout(100); // Возвращаем timeout после меню, чтобы дальше ожидать ввод с небольшой задержкой
    clear(); // Очищаем экран после старта игры
}

void drawSnakeScores(snake_t* snake1, snake_t* snake2) {
    mvprintw(0, 0, "Player 1 Score: %d", snake1->food_eaten);
    mvprintw(0, COLS - 20, "Player 2 Score: %d", snake2->food_eaten);
}

int main() {
    initscr(); // Инициализируем ncurses
    timeout(100); // Задаем время задержки в 100 мс
    noecho(); // Отключаем эхо ввода
    cbreak(); // Отключаем буферизацию
    keypad(stdscr, TRUE); // Включаем поддержку специальных клавиш, включая стрелки

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK); // Красный для первой змейки
    init_pair(2, COLOR_GREEN, COLOR_BLACK); // Зеленый для второй змейки
    init_pair(3, COLOR_YELLOW, COLOR_BLACK); // Желтый для еды

    srand(time(NULL));

    // Инициализация змей
    snake_t snake1, snake2;
    initSnake(&snake1, START_TAIL_SIZE, 20, 10, 1);
    initSnake(&snake2, START_TAIL_SIZE, 40, 10, 2);

    // Инициализация еды
    food_t food[FOOD_COUNT];
    putFood(food, FOOD_COUNT, &snake1, &snake2);

    // Отображаем стартовое меню и ждем нажатия клавиши
    drawStartMenu();  // Стартовое меню
    // После этого уже можно сразу начать игру без дополнительного ожидания ввода

    // Главный игровой цикл
    while (1) {
        drawSnakeScores(&snake1, &snake2); // Отображаем счёт
        go(&snake1); // Двигаем первую змейку
        goTail(&snake1); // Двигаем хвост первой змейки
        go(&snake2); // Двигаем вторую змейку
        goTail(&snake2); // Двигаем хвост второй змейки

        if (haveEat(&snake1, food, FOOD_COUNT)) { // Проверяем, не съела ли первая змейка еду
            putFood(food, FOOD_COUNT, &snake1, &snake2); // Размещаем новую еду
        }
        if (haveEat(&snake2, food, FOOD_COUNT)) { // Проверяем, не съела ли вторая змейка еду
            putFood(food, FOOD_COUNT, &snake1, &snake2); // Размещаем новую еду
        }

        refreshFood(food, FOOD_COUNT, &snake1, &snake2); // Обновляем еду

        // Ввод управляющих клавиш
        int ch = getch();
        if (ch == STOP_GAME) break; // Завершаем игру, если нажата 'q'
        changeDirection(&snake1, ch); // Изменяем направление первой змейки
        changeDirection(&snake2, ch); // Изменяем направление второй змейки

        if (isCrush(&snake1, &snake2)) break; // Завершаем игру, если змейки столкнулись
    }

    endwin(); // Завершаем работу с ncurses
    return 0;
}

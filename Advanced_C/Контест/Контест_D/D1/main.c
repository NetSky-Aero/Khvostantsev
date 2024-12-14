#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

typedef int datatype;                                                   // Определяю структуру дерева
typedef struct tree
{
    datatype key;
    struct tree *left, *right;
} tree;

typedef struct queueNode                                                // Узел очереди для уровня и горизонтального расстояния
{
    tree *node;
    int hd;                                                             // горизонтальное расстояние
    struct queueNode *next;
} queueNode;

typedef struct queue                                                    // Структура очереди
{
    queueNode *front, *rear;
} queue;

queue *createQueue()                                                    // Инициализирую очередь
{
    queue *q = (queue *)malloc(sizeof(queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(queue *q, tree *node, int hd)                              // Добавляю в очередь
{
    queueNode *newNode = (queueNode *)malloc(sizeof(queueNode));
    newNode->node = node;
    newNode->hd = hd;
    newNode->next = NULL;
    if (q->rear == NULL)
    {
        q->front = q->rear = newNode;
        return;
    }
    q->rear->next = newNode;
    q->rear = newNode;
}

queueNode *dequeue(queue *q)                                            // Удаляю из очереди
{
    if (q->front == NULL)
    {
        return NULL;
    }
    queueNode *temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL)
    {
        q->rear = NULL;
    }
    return temp;
}

bool isQueueEmpty(queue *q)                                             // Проверяю, пуста ли очередь
{
    return q->front == NULL;
}

typedef struct mapNode                                                  // Узел для карты видимости сверху
{
    int hd;
    datatype key;
    struct mapNode *next;
} mapNode;

void addToMap(mapNode **map, int hd, datatype key)                      // Добавляю в карту видимости сверху
{
    mapNode *newNode = (mapNode *)malloc(sizeof(mapNode));
    newNode->hd = hd;
    newNode->key = key;
    newNode->next = *map;
    *map = newNode;
}

bool existsInMap(mapNode *map, int hd)                                  // Проверяю, существует ли горизонтальное расстояние в карте
{
    while (map != NULL)
    {
        if (map->hd == hd)
        {
            return true;
        }
        map = map->next;
    }
    return false;
}

void printMap(mapNode *map)                                             // Вывожу значения карты в порядке возрастания HD
{
    int minHD = INT_MAX, maxHD = INT_MIN;
    mapNode *temp = map;

    while (temp != NULL)                                                // Ищу минимальное и максимальное значения HD
    {
        if (temp->hd < minHD) minHD = temp->hd;
        if (temp->hd > maxHD) maxHD = temp->hd;
        temp = temp->next;
    }

    for (int i = minHD; i <= maxHD; ++i)                                // Вывожу значения в порядке HD
    {
        temp = map;
        while (temp != NULL)
        {
            if (temp->hd == i)
            {
                printf("%d ", temp->key);
                break;
            }
            temp = temp->next;
        }
    }
}

void btUpView(tree *root)                                               // Функция для печати вида сверху void btUpView(tree *root)
{
    if (root == NULL)
    {
        return;
    }

    queue *q = createQueue();
    mapNode *map = NULL;

    enqueue(q, root, 0);

    while (!isQueueEmpty(q))
    {
        queueNode *temp = dequeue(q);

        tree *currentNode = temp->node;
        int hd = temp->hd;
        free(temp);

        if (!existsInMap(map, hd))                                      // Если горизонтальное расстояние не добавлено в карту, добавить его
        {
            addToMap(&map, hd, currentNode->key);
        }

        if (currentNode->left)                                          // Добавляю левое и правое поддерево в очередь
        {
            enqueue(q, currentNode->left, hd - 1);
        }
        if (currentNode->right)
        {
            enqueue(q, currentNode->right, hd + 1);
        }
    }

    printMap(map);                                                      // Печатаю карту
}

tree *createNode(datatype key)                                          // Вспомогательная функция для создания узла дерева
{
    tree *newNode = (tree *)malloc(sizeof(tree));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void insert(tree **root, datatype key)                                  // Функция для добавления узла в дерево
{
    if (*root == NULL)
    {
        *root = createNode(key);
        return;
    }
    if (key < (*root)->key)
    {
        insert(&(*root)->left, key);
    } else {
        insert(&(*root)->right, key);
    }
}

int main(void)
{
    tree *root = NULL;
    char input[256];

    fgets(input, sizeof(input), stdin);

    char *token = strtok(input, " ");
    while (token)
    {
        int value = atoi(token);
        insert(&root, value);
        token = strtok(NULL, " ");
    }

    btUpView(root);

    return 0;
}

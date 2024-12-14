#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

typedef int datatype;                                                   // ��������� ��������� ������
typedef struct tree
{
    datatype key;
    struct tree *left, *right;
} tree;

typedef struct queueNode                                                // ���� ������� ��� ������ � ��������������� ����������
{
    tree *node;
    int hd;                                                             // �������������� ����������
    struct queueNode *next;
} queueNode;

typedef struct queue                                                    // ��������� �������
{
    queueNode *front, *rear;
} queue;

queue *createQueue()                                                    // ������������� �������
{
    queue *q = (queue *)malloc(sizeof(queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(queue *q, tree *node, int hd)                              // �������� � �������
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

queueNode *dequeue(queue *q)                                            // ������ �� �������
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

bool isQueueEmpty(queue *q)                                             // ��������, ����� �� �������
{
    return q->front == NULL;
}

typedef struct mapNode                                                  // ���� ��� ����� ��������� ������
{
    int hd;
    datatype key;
    struct mapNode *next;
} mapNode;

void addToMap(mapNode **map, int hd, datatype key)                      // �������� � ����� ��������� ������
{
    mapNode *newNode = (mapNode *)malloc(sizeof(mapNode));
    newNode->hd = hd;
    newNode->key = key;
    newNode->next = *map;
    *map = newNode;
}

bool existsInMap(mapNode *map, int hd)                                  // ��������, ���������� �� �������������� ���������� � �����
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

void printMap(mapNode *map)                                             // ������ �������� ����� � ������� ����������� HD
{
    int minHD = INT_MAX, maxHD = INT_MIN;
    mapNode *temp = map;

    while (temp != NULL)                                                // ��� ����������� � ������������ �������� HD
    {
        if (temp->hd < minHD) minHD = temp->hd;
        if (temp->hd > maxHD) maxHD = temp->hd;
        temp = temp->next;
    }

    for (int i = minHD; i <= maxHD; ++i)                                // ������ �������� � ������� HD
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

void btUpView(tree *root)                                               // ������� ��� ������ ���� ������ void btUpView(tree *root)
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

        if (!existsInMap(map, hd))                                      // ���� �������������� ���������� �� ��������� � �����, �������� ���
        {
            addToMap(&map, hd, currentNode->key);
        }

        if (currentNode->left)                                          // �������� ����� � ������ ��������� � �������
        {
            enqueue(q, currentNode->left, hd - 1);
        }
        if (currentNode->right)
        {
            enqueue(q, currentNode->right, hd + 1);
        }
    }

    printMap(map);                                                      // ������� �����
}

tree *createNode(datatype key)                                          // ��������������� ������� ��� �������� ���� ������
{
    tree *newNode = (tree *)malloc(sizeof(tree));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void insert(tree **root, datatype key)                                  // ������� ��� ���������� ���� � ������
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

#include <stdio.h>
#include <stdlib.h>

typedef struct tree {
    int key;
    struct tree *left, *right;
    struct tree *parent;
} tree;

// Функция для создания нового узла
tree *createNode(int key) {
    tree *node = (tree *)malloc(sizeof(tree));
    node->key = key;
    node->left = node->right = node->parent = NULL;
    return node;
}

// Функция для вставки нового ключа в дерево
tree *insert(tree *root, int key) {
    if (root == NULL) {
        return createNode(key);
    }

    if (key < root->key) {
        tree *leftChild = insert(root->left, key);
        root->left = leftChild;
        leftChild->parent = root;
    } else if (key > root->key) {
        tree *rightChild = insert(root->right, key);
        root->right = rightChild;
        rightChild->parent = root;
    }

    return root;
}

// Функция для поиска узла по ключу
tree *findNode(tree *root, int key) {
    tree *current = root;
    while (current != NULL && current->key != key) {
        if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return current;
}

// Функция для поиска брата
tree *findBrother(tree *root, int key) {
    // Найти узел с ключом key
    tree *current = findNode(root, key);

    // Если узел не найден, вернуть NULL
    if (current == NULL) {
        return NULL;
    }

    // Проверить родителя
    tree *parent = current->parent;
    if (parent == NULL) {
        return NULL; // У корня нет брата
    }

    // Определить брата в зависимости от того, левый ли это ребёнок
    if (parent->left == current) {
        return parent->right; // Брат справа
    } else {
        return parent->left; // Брат слева
    }
}

// Вспомогательная функция для вывода результата
void printBrother(tree *brother) {
    if (brother == NULL) {
        printf("0\n");
    } else {
        printf("%d\n", brother->key);
    }
}

int main() {
    tree *root = NULL;

    // Заданные входные данные
    int keys[] = {10, 5, 15, 3, 7, 13, 18, 1, 6, 14, 0, 3};
    int n = sizeof(keys) / sizeof(keys[0]);

    // Строим дерево
    for (int i = 0; i < n; i++) {
        root = insert(root, keys[i]);
    }

    // Поиск брата для узла с ключом 15
    tree *brother = findBrother(root, 15);

    // Вывод результата
    printBrother(brother);

    return 0;
}

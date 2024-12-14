#include <stdio.h>
#include <stdlib.h>

typedef struct tree {
    int key;
    struct tree *left, *right;
    struct tree *parent;
} tree;

// ������� ��� �������� ������ ����
tree *createNode(int key) {
    tree *node = (tree *)malloc(sizeof(tree));
    node->key = key;
    node->left = node->right = node->parent = NULL;
    return node;
}

// ������� ��� ������� ������ ����� � ������
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

// ������� ��� ������ ���� �� �����
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

// ������� ��� ������ �����
tree *findBrother(tree *root, int key) {
    // ����� ���� � ������ key
    tree *current = findNode(root, key);

    // ���� ���� �� ������, ������� NULL
    if (current == NULL) {
        return NULL;
    }

    // ��������� ��������
    tree *parent = current->parent;
    if (parent == NULL) {
        return NULL; // � ����� ��� �����
    }

    // ���������� ����� � ����������� �� ����, ����� �� ��� ������
    if (parent->left == current) {
        return parent->right; // ���� ������
    } else {
        return parent->left; // ���� �����
    }
}

// ��������������� ������� ��� ������ ����������
void printBrother(tree *brother) {
    if (brother == NULL) {
        printf("0\n");
    } else {
        printf("%d\n", brother->key);
    }
}

int main() {
    tree *root = NULL;

    // �������� ������� ������
    int keys[] = {10, 5, 15, 3, 7, 13, 18, 1, 6, 14, 0, 3};
    int n = sizeof(keys) / sizeof(keys[0]);

    // ������ ������
    for (int i = 0; i < n; i++) {
        root = insert(root, keys[i]);
    }

    // ����� ����� ��� ���� � ������ 15
    tree *brother = findBrother(root, 15);

    // ����� ����������
    printBrother(brother);

    return 0;
}

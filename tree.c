#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "time.h"
#include <math.h>

Tree* createTree() {
    Tree *tree = (Tree *)malloc(sizeof(Tree));
    tree->root = NULL;
    tree->head = NULL;
    tree->tail = NULL;
    return tree;
}

Node* createNode(const char *key, const char *value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->key = strdup(key);
    newNode->value = strdup(value);
    newNode->left = newNode->right = newNode->parent = newNode->next = newNode->prev = NULL;
    return newNode;
}

void freeNode(Node *node) {
    if (node) {
        free(node->key);
        free(node->value);
        free(node);
    }
}

Node* addNode(Tree *tree, const char *key, const char *value) {
    Node *newNode = createNode(key, value);
    if (!tree->root) {
        tree->root = newNode;
        tree->head = tree->tail = newNode;
        return newNode;
    }

    Node *current = tree->root;
    Node *parent = NULL;
    while (current) {
        parent = current;
        if (strcmp(key, current->key) < 0) {
            current = current->left;
        } else if (strcmp(key, current->key) > 0) {
            current = current->right;
        } else {
            char *oldValue = current->value;
            current->value = strdup(value);
            free(oldValue);
            return current;
        }
    }

    newNode->parent = parent;
    if (strcmp(key, parent->key) < 0) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    if (strcmp(newNode->key, tree->head->key) < 0) {
        newNode->next = tree->head;
        tree->head->prev = newNode;
        tree->head = newNode;
    } else if (strcmp(newNode->key, tree->tail->key) > 0) {
        newNode->prev = tree->tail;
        tree->tail->next = newNode;
        tree->tail = newNode;
    } else {
        Node *succ = tree->head;
        while (succ && strcmp(succ->key, key) < 0) {
            succ = succ->next;
        }
        newNode->next = succ;
        newNode->prev = succ->prev;
        succ->prev->next = newNode;
        succ->prev = newNode;
    }

    return newNode;
}

Node* findNode(Node *root, const char *key) {
    while (root) {
        int cmp = strcmp(key, root->key);
        if (cmp < 0) {
            root = root->left;
        } else if (cmp > 0) {
            root = root->right;
        } else {
            return root;
        }
    }
    return NULL;
}

Node* deleteNode(Tree *tree, const char *key) {
    Node *target = findNode(tree->root, key);
    if (!target) {
        return NULL;
    }

    Node *y = NULL;
    if (!target->left || !target->right) {
        y = target;
    } else {
        y = target->next;
    }

    Node *x = y->left ? y->left : y->right;
    if (x) {
        x->parent = y->parent;
    }

    if (!y->parent) {
        tree->root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }

    if (y != target) {
        free(target->key);
        target->key = strdup(y->key);
        free(target->value);
        target->value = strdup(y->value);
    }
    if (y->prev) {
        y->prev->next = y->next;
    }
    if (y->next) {
        y->next->prev = y->prev;
    }

    if (y == tree->head) {
        tree->head = y->next;
    }
    if (y == tree->tail) {
        tree->tail = y->prev;
    }

    freeNode(y);
    return target;
}

void inorderTraversal(Node *root) {
    if (root) {
        inorderTraversal(root->left);
        printf("%s: %s\n", root->key, root->value);
        inorderTraversal(root->right);
    }
}

void reverseOrderTraversal(Node *root) {
    if (root) {
        reverseOrderTraversal(root->right);
        printf("%s: %s\n", root->key, root->value);
        reverseOrderTraversal(root->left);
    }
}

void freeTree(Tree *tree) {
    Node *current = tree->head;
    while (current) {
        Node *next = current->next;
        freeNode(current);
        current = next;
    }
    free(tree);
}

int calculateDifference(const char *str1, const char *str2) {
    int diff = 0;
    while (*str1 && *str2) {
        diff += abs(*str1 - *str2);
        str1++;
        str2++;
    }
    while (*str1) {
        diff += abs(*str1);
        str1++;
    }
    while (*str2) {
        diff += abs(*str2);
        str2++;
    }
    return diff;
}

void spSearchNode(Node *root, const char *value, Node **result, int *maxDiff) {
    if (!root) return;
    spSearchNode(root->left, value, result, maxDiff);

    int currentDiff = calculateDifference(root->value, value);
    if (currentDiff > *maxDiff || (currentDiff == *maxDiff && strcmp(root->key, (*result)->key) < 0)) {
        *maxDiff = currentDiff;
        *result = root;
    }

    spSearchNode(root->right, value, result, maxDiff);
}

void spSearchNodeTree(Tree *tree, const char *value) {
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    Node *result = NULL;
    int maxDiff = -1;
    spSearchNode(tree->root, value, &result, &maxDiff);
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    if (result) {
        printf("Найдено: %s: %s\n", result->key, result->value);
    } else {
        printf("Не найдено\n");
    }
    printf("Время выполнения: %f секунд\n", cpu_time_used);
}

#ifndef TREE_H
#define TREE_H

typedef struct Node {
    char *key;
    char *value;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct Tree {
    Node *root;
    Node *head;
    Node *tail;
} Tree;

Tree* createTree();
Node* createNode(const char *key, const char *value);
void freeNode(Node *node);

Node* addNode(Tree *tree, const char *key, const char *value);
Node* findNode(Node *root, const char *key);
Node* deleteNode(Tree *tree, const char *key);

void inorderTraversal(Node *root);
void reverseOrderTraversal(Node *root);
void freeTree(Tree *tree);

int calculateDifference(const char *str1, const char *str2);
void spSearchNode(Node *root, const char *value, Node **result, int *maxDiff);
void spSearchNodeTree(Tree *tree, const char *value);

#endif

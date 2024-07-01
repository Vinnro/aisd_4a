#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

void send_command_menu() {
    printf("\033[0;33m____________________________________\n");
    printf("__________Вот ваше меню_____________\n");
    printf("____Выберите один из вариантов ниже___\n");
    printf("[1] Добавить\n");
    printf("[2] Удалить\n");
    printf("[3] Обход дерева\n");
    printf("[4] Поиск\n");
    printf("[5] Специальный поиск\n");
    printf("[0] Выход\n");
    printf("____________________________________\033[0m\n");
}

void add_node_tree(Tree *tree) {
    char key[256], value[256];
    printf("Введите ключ: ");
    scanf("%s", key);
    printf("Введите значение: ");
    scanf("%s", value);
    addNode(tree, key, value);
}

void remove_node_tree(Tree *tree) {
    char key[256];
    printf("Введите ключ для удаления: ");
    scanf("%s", key);
    deleteNode(tree, key);
}

void traversal_limit_tree(Tree *tree) {
    reverseOrderTraversal(tree->root);
}

void search_node_tree(Tree *tree) {
    char key[256];
    printf("Введите ключ для поиска: ");
    scanf("%s", key);
    Node *found = findNode(tree->root, key);
    if (found) {
        printf("Найдено: %s: %s\n", found->key, found->value);
    } else {
        printf("Не найдено\n");
    }
}

void sp_search_node_tree(Tree *tree) {
    char value[256];
    printf("Введите значение для поиска: ");
    scanf("%s", value);
    spSearchNodeTree(tree, value);
}

void menu(Tree *tree) {
    void (*func[5])(Tree *) = {add_node_tree, remove_node_tree, traversal_limit_tree, search_node_tree, sp_search_node_tree};
    printf("\033[H\033[J");
    send_command_menu();

    while (1) {
        printf("\033[1;90mВведите команду (номер [0-5]):\033[0;0m\n");
        int command = 0;
        int x = scanf("%d", &command);
        if (x == EOF) {
            scanf("%*[^\n]*c");
            reverseOrderTraversal(tree->root);
            freeTree(tree);
            return;
        }
        if (command == 0) {
            freeTree(tree);
            return;
        } else if (command > 0 && command < 6) {
            func[command - 1](tree);
        } else {
            printf("Неверная команда. Попробуйте снова.\n");
        }
    }
}

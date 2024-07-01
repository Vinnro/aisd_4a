#include "tree.h"
#include "menu.h"

int main() {
    Tree *tree = createTree();
    menu(tree);
    return 0;
}

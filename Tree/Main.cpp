#include <stdlib.h>
#include <stdio.h>
#include "Tree.h"
#include "Tree_dump.h"

int main () {
    TREE tree = {};

    tree_init(&tree);

    op_new(&tree.root, "Roma");
    op_new(&tree.root->left, "Dima");
    op_new(&tree.root->left->left, "Anya");
    op_new(&tree.root->left->right, "Alina");
    op_new(&tree.root->right, "Andrei");

    int counter = 0;

    make_png_dump("tree.dot", tree.root, &counter);

    return 0;
}
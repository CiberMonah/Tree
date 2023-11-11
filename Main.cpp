#include <stdlib.h>
#include <stdio.h>
#include "Tree.h"

int main () {
    TREE tree = {};
    tree_init(&tree, 0);

    op_new(&tree.root->left, 1);
    op_new(&tree.root->left->left, 3);
    op_new(&tree.root->left->right, 4);
    op_new(&tree.root->right, 2);

    printf("\n");
    pre_order(tree.root);
    printf("\n");
    post_order(tree.root);
    printf("\n");
    in_order(tree.root);

    return 0;
}
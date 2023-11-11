#include <stdlib.h>
#include <stdio.h>
#include "Tree.h"

int main () {
    TREE tree = {};
    FILE* out;

    if ((out = fopen("tree.txt", "w")) == NULL) {
        printf("File creating error");
        return 1;
    }

    tree_init(&tree, 10);
    op_new(&tree.root->left, 5);
    op_new(&tree.root->left->left, 1);
    op_new(&tree.root->left->right, 7);
    op_new(&tree.root->right, 15);

    // different types to print tree
    // print_pre_order(out, tree.root);
    // print_post_order(out, tree.root);
    // print_in_order(out, tree.root);

    branch_delete(tree.root, "right");
    print_in_order(out, tree.root);

    fclose(out);

    return 0;
}
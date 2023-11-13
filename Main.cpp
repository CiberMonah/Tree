#include <stdlib.h>
#include <stdio.h>
#include "Tree.h"
#include "Akinator.h"
#include "Tree_dump.h"

int main () {
    TREE tree = {};

    FILE* out  = nullptr;

    if((out= fopen("tree.txt", "w")) == nullptr) {
        return FILE_OPEN_ERR;
    }

    tree_init(&tree);

    op_new(&tree.root, "Roma");
    op_new(&tree.root->left, "Dima");
    op_new(&tree.root->left->left, "Anya");
    op_new(&tree.root->left->right, "Alina");
    op_new(&tree.root->right, "Andrei");

    //make_dot_dump()



    // different types to print tree

    // print_pre_order(stdin, tree.root);
    // print_post_order(stdin, tree.root);
    // print_in_order(stdin, tree.root);

    print_pre_order(stdout, tree.root);
    print_pre_order(out, tree.root);

    fclose(out);

    return 0;
}
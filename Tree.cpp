#include "Tree.h"
#include <stdlib.h>
#include <stdio.h>

err_type tree_init(TREE* tree, Elem_t root_value) {
    tree->tree_size = 0;
    return op_new(&tree->root, root_value);
}

err_type op_new(NODE** node, Elem_t value) {
    *node = (NODE*)calloc(1, sizeof(NODE));

    if(node == nullptr)
        return MEM_ALL_ERR;
    (*node)->data = value;
    (*node)->right = nullptr;
    (*node)->left = nullptr;

    return NO_ERR;
}

void pre_order(NODE* node) {
    if(!node) {
        printf("nil ");
        return;
    }
    printf("( ");
    printf("%d ", node->data);
    pre_order(node->left);
    pre_order(node->right);
    printf(") ");
}

void in_order(NODE* node) {
    if(!node) {
        printf("nil ");
        return;
    }
    printf("( ");
    pre_order(node->left);
    printf("%d ", node->data);
    pre_order(node->right);
    printf(") ");
}

void post_order(NODE* node) {
    if(!node) {
        printf("nil ");
        return;
    }
    printf("( ");
    pre_order(node->left);
    pre_order(node->right);
    printf("%d ", node->data);
    printf(") ");
}

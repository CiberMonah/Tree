#include "Tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

err_type tree_init(TREE* tree) {
    tree->tree_size = 0;
    tree->root = NULL;
    return NO_ERR;
}

static err_type free_nodes(NODE* node) {
    if(!node) {
        return NO_ERR;
    }

    free_nodes(node->left);
    free_nodes(node->right);
    free(node);

    return NO_ERR;
}

err_type free_tree(TREE* tree) {
    tree->tree_size = -1;

    free_nodes(tree->root);

    return NO_ERR;
}

static err_type tree_delete(NODE* root) {
    if(!root) {
        return NO_ERR;
    }
    tree_delete(root->left);
    tree_delete(root->right);
    root->left = nullptr;
    root->right = nullptr;
    free(root);

    return NO_ERR;
}

err_type branch_delete(NODE* root, const char* str) {

    if(strcmp(str, "left" ) == 0) {
        tree_delete(root->left);
        root->left = nullptr;
    } else if(strcmp(str, "right" ) == 0) {
        tree_delete(root->right);
        root->right = nullptr;
    } else if(strcmp(str, "both") == 0) {
        tree_delete(root->left);
        root->left = nullptr;
        tree_delete(root->right);
        root->right = nullptr;
    } else {
        printf("Wrong code in branch delete func\n");
        return ERROR;
    }
    return NO_ERR;
}

err_type op_new(NODE** node, Elem_t value) {
    *node = (NODE*)calloc(1, sizeof(NODE));

    if(node == nullptr)
        return MEM_ALL_ERR;
    (*node)->data = strdup(value);
    (*node)->right = nullptr;
    (*node)->left = nullptr;

    return NO_ERR;
}

void print_pre_order(FILE* out, NODE* node) {
    if(!node) {
        fprintf(out, "nil ");
        return;
    }
    fprintf(out, "( ");
    fprintf(out, format, node->data);
    print_pre_order(out, node->left);
    print_pre_order(out, node->right);
    fprintf(out, ") ");
}

void print_in_order(FILE* out, NODE* node) {
    if(!node) {
        fprintf(out, "nil ");
        return;
    }
    fprintf(out, "( ");
    print_in_order(out, node->left);
    fprintf(out, format, node->data);
    print_in_order(out, node->right);
    fprintf(out, ") ");
}

void print_post_order(FILE* out, NODE* node) {
    if(!node) {
        fprintf(out, "nil ");
        return;
    }
    fprintf(out, "( ");
    print_post_order(out, node->left);
    print_post_order(out, node->right);
    fprintf(out, format, node->data);
    fprintf(out, ") ");
}

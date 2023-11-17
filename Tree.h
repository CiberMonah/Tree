#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>

typedef char* Elem_t;
#define format "%s "            //To print or scanf any types

struct NODE {
    Elem_t data;

    NODE* left;
    NODE* right;
};

struct TREE {
    NODE* root;
    unsigned int tree_size;
};

enum tree_err_type {
    TREE_NO_ERR          = 0,
    TREE_ERROR           = -1,

    TREE_MEM_ALL_ERR     = 1 << 0,
    TREE_FILE_OPEN_ERR   = 1 << 1,
};

tree_err_type op_new(NODE** node, Elem_t value);
tree_err_type tree_init(TREE* tree);
tree_err_type free_tree(TREE* tree);
tree_err_type branch_delete(NODE* root, const char* str);

void print_pre_order(FILE* out, NODE* node);
void print_in_order(FILE* out, NODE* node);
void print_post_order(FILE* out, NODE* node); 

#endif
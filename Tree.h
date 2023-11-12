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

enum err_type {
    NO_ERR          = 0,
    ERROR           = -1,

    MEM_ALL_ERR     = 1 << 0,
    FILE_OPEN_ERR   = 1 << 1,

};

err_type op_new(NODE** node, Elem_t value);
err_type tree_init(TREE* tree);
err_type free_tree(TREE* tree);
err_type branch_delete(NODE* root, const char* str);

void print_pre_order(FILE* out, NODE* node);
void print_in_order(FILE* out, NODE* node);
void print_post_order(FILE* out, NODE* node); 

#endif
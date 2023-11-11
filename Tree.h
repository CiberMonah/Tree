#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

typedef int Elem_t;

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
    NO_ERR      = 0,

    MEM_ALL_ERR = 1 << 0,

};

err_type op_new(NODE** node, Elem_t value);
err_type tree_init(TREE* tree, Elem_t root_value);

void pre_order(NODE* node);
void in_order(NODE* node);
void post_order(NODE* node); 

#endif
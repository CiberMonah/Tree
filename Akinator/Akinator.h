#ifndef AKINATOR_H_INCLUDED
#define AKINATOR_H_INCLUDED
#include "Src_Tree\Tree.h"

tree_err_type menu(const char* data_file_name, const char* dump_file_name);
tree_err_type save_data(NODE* root, FILE* fp);
tree_err_type load_data(NODE** root, FILE* fp, FILE* dump_file);
tree_err_type guess_session (NODE* root);
int give_definition(NODE* root, char* key);
void compare_difinitions(NODE* root, char* key1, char* key2);

#endif

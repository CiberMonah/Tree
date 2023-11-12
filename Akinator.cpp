#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Tree.h"
#include "Akinator.h"

static err_type save_data(NODE* root, FILE* fp) {
    fp = fopen("akinator.txt", "w");
    print_pre_order(fp, root);
    fclose(fp);
    return NO_ERR;
}

static err_type parse_data(FILE* fp, NODE** root) {
    if(root == nullptr) 
        return NO_ERR;
    char word[10] = "";
    
    fscanf(fp, format, word);

    printf("%s\n", word);

    if(strcmp(word, "(") == 0) {
        fscanf(fp, format, word);
        printf("read root: %s\n", word);

        op_new(root, word);

        printf("parsing left tree...\n");
        parse_data(fp, &((*root)->left));
        printf("parsing right tree...\n");
        parse_data(fp, &((*root)->right));
        printf("finished parsing %s\n", word);
        fscanf(fp, "%s ", word);
    } else if (strcmp(word, "nil") == 0) {
        *root = nullptr;
        return NO_ERR;
    } else {
        return NO_ERR;
    }
    return NO_ERR;
}

static err_type load_data(NODE** root, FILE* fp) {
    
    parse_data(fp, root);
    rewind(fp);

    return NO_ERR;
}

err_type menu(const char* data_file_name) {
    int com;
    TREE tree = {};

    FILE* in  = nullptr;

    if((in = fopen(data_file_name, "r")) == nullptr) {
        return FILE_OPEN_ERR;
    }

    tree_init(&tree);

    printf("commands:\n1 - load data\n2 - save - data\n3 - print_data\n");

    while((scanf("%d", &com))) {
        switch(com) {
        case 1:
            load_data(&tree.root, in);
            break;
        case 2:
            fclose(in);
            save_data(tree.root, in);
            return NO_ERR;
            break;
        case 3:
            print_pre_order(stdout, tree.root);
            break;
        default:
            return NO_ERR;
        }
    }

    free(in);

    return NO_ERR;
}
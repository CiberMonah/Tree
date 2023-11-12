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

static err_type parse_data(FILE* fp, FILE* dump_file, NODE** root) {
    if(root == nullptr) 
        return NO_ERR;
    char word[10] = "";
    
    fscanf(fp, format, word);

    fprintf(dump_file, "%s\n", word);

    if(strcmp(word, "(") == 0) {
        fscanf(fp, format, word);
        fprintf(dump_file, "read root: %s\n", word);

        op_new(root, word);

        fprintf(dump_file, "parsing left tree...\n");
        parse_data(fp, dump_file, &((*root)->left));
        fprintf(dump_file, "parsing right tree...\n");
        parse_data(fp, dump_file, &((*root)->right));
        fprintf(dump_file, "finished parsing %s\n", word);
        fscanf(fp, "%s ", word);
    } else if (strcmp(word, "nil") == 0) {
        *root = nullptr;
        return NO_ERR;
    } else {
        return NO_ERR;
    }
    return NO_ERR;
}

static err_type load_data(NODE** root, FILE* fp, FILE* dump_file) {
    
    parse_data(fp, dump_file, root);
    printf("Loaded succesful\n");
    rewind(fp);

    return NO_ERR;
}

static err_type session (NODE* root) {
    if(!root) 
        return NO_ERR;

    char ch = 0;
    char answer[20] = "nothing", question[20] = "nothing";

    printf("%s?\n", root->data);
    printf("Y/N?: ");

    getchar();
    ch = getchar();
    
    // printf("Char - %c\n", ch);
    switch(ch) {
    case 'Y':
        if(root->right == nullptr) {
            printf("HAHAHAHA I GUEST RIGHT!!!!  :D\n");
            return NO_ERR;
        } else {
            session(root->right);
        }
        break;
    case 'N':
        if(root->left == nullptr) {
            printf("WHO IS IT?????\n");
            scanf("%s", answer);
            printf("HOW IT DIFFER?????      \\_(:/))_/\n");
            scanf("%s", question);
            op_new(&root->right, answer);
            op_new(&root->left, root->data);
            root->data = strdup(question);
            printf("OK....I WILL REMEMBER IT....  :^>\n");
            return NO_ERR;
        } else {
            session(root->left);
        }
        break;
    default:
    printf("WRONG KEYYY, ITS ONLY Y OR N STUPID HUMAN!!!!!  :-t\n");
        break;
    }

    return NO_ERR;
}

err_type menu(const char* data_file_name, FILE* dump_file) {
    int com;
    TREE tree = {};
    FILE* in  = nullptr;
    FILE* out  = nullptr;
    

    tree_init(&tree);

    printf("commands:\n1 - load data\n2 - save - data\n3 - print_data\n4 - start session\n");

    while((scanf("%d", &com))) {
        switch(com) {
        case 1:
            if((in = fopen(data_file_name, "r")) == nullptr) {
                return FILE_OPEN_ERR;
            }

            load_data(&tree.root, in, dump_file);

            fclose(in);

            break;

        case 2:
            if((out = fopen(data_file_name, "w")) == nullptr) {
                return FILE_OPEN_ERR;
            }

            save_data(tree.root, out);

            fclose(out);
            break;

        case 3:
            print_pre_order(stdout, tree.root);
            fprintf(stdout, "\n");

            break;

        case 4:
            session(tree.root);

            break;
        default:
            return NO_ERR;
        }
    }

    return NO_ERR;
}
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Tree.h"
#include "Akinator.h"
#include "Stack\Simple_stack.h"

static tree_err_type save_data(NODE* root, FILE* fp) {
    fp = fopen("akinator.txt", "w");
    print_pre_order(fp, root);
    fclose(fp);
    return TREE_NO_ERR;
}

static void read_word(char *word, size_t size, FILE *input)
{
	int symb = getc(input);
	size_t ind = 0;
	while (ind < size && symb != EOF && !isspace(symb)) {
		word[ind++] = (char)getc(input);
	}
}

static tree_err_type parse_data(FILE* fp, FILE* dump_file, NODE** root) {
    if(root == nullptr) 
        return TREE_NO_ERR;
    char word[10] = "";
    
    fscanf(fp, format, word);

    if(strcmp(word, "(") != 0)
        fprintf(dump_file, "%s\n", word);

    if(strcmp(word, "(") == 0) {
        fscanf(fp, format, word);
        fprintf(dump_file, "read root: %s\n", word);

        op_new(root, word);

        fprintf(dump_file, "parsing left tree...%s\n", word);
        parse_data(fp, dump_file, &((*root)->left));
        fprintf(dump_file, "parsing right tree...%s\n", word);
        parse_data(fp, dump_file, &((*root)->right));
        fprintf(dump_file, "finished parsing %s\n", word);
        fscanf(fp, "%s ", word);
    } else if (strcmp(word, "nil") == 0) {
        *root = nullptr;
        return TREE_NO_ERR;
    } else {
        return TREE_NO_ERR;
    }
    return TREE_NO_ERR;
}

static tree_err_type load_data(NODE** root, FILE* fp, FILE* dump_file) {
    
    parse_data(fp, stdout, root);
    printf("Loaded succesful\n");
    rewind(fp);
    fprintf(dump_file, "\nLOADED SUCCESFUL\n");
    return TREE_NO_ERR;
}

static tree_err_type session (NODE* root) {
    if(!root) 
        return TREE_NO_ERR;

    char ch = 0;
    char answer[50] = "", question[50] = "";

    printf("%s?\n", root->data);
    printf("Y/N?: ");

    getchar();
    ch = (char)getchar();
    
    // printf("Char - %c\n", ch);
    switch(ch) {
    case 'Y':
        if(root->right == nullptr) {
            printf("HAHAHAHA I GUEST RIGHT!!!!  :D\n");
            return TREE_NO_ERR;
        } else {
            session(root->right);
        }
        break;
    case 'N':
        if(root->left == nullptr) {
            printf("WHO IS IT?????\n");
            if(scanf("%s", answer) != 1) {
                printf("Only one word in question and answer\n");  
                return TREE_ERROR;
            }
            printf("HOW IT DIFFER?????      \\_(:/))_/\n");
            if(scanf("%s", question) != 1) {
                printf("Only one word in question and answer\n");  
                return TREE_ERROR;
            }
            op_new(&root->right, answer);
            op_new(&root->left, root->data);
            root->data = strdup(question);
            printf("OK....I WILL REMEMBER IT....  :^>\n");
            return TREE_NO_ERR;
        } else {
            session(root->left);
        }
        break;
    default:
    printf("WRONG KEYYY, ITS ONLY Y OR N STUPID HUMAN!!!!!  :-t\n");
        break;
    }

    return TREE_NO_ERR;
}

static int give_definition(NODE* root, char* key) {
    if(!root) {
        return 0;
    }

    if(strcmp(root->data, key) == 0) {
        printf("%s ", key);
        return 1;
    }
    
    if(give_definition(root->left, key)) {
        printf("not %s ", root->data);
        return 1;
    } else if(give_definition(root->right, key)) {
        printf("%s ", root->data);
        return 1;
    }

    return 0;
}

static int make_stack_of_definitions(NODE* root, char* key, Stack* stk) {
    if(!root) {
        return 0;
    }

    if(strcmp(root->data, key) == 0) {
        push(stk, key);
        return 1;
    }
    
    if(give_definition(root->left, key)) {
        push(stk, strcat("not ", key));
        return 1;
    } else if(give_definition(root->right, key)) {
        push(stk, key);
        return 1;
    }

    return 0;
}

static void compare_difinitions(NODE* root, char* key1, char* key2) {
    Stack stk1 = {};
    stack_init(&stk1);
    Stack stk2 = {};
    stack_init(&stk2);

    make_stack_of_definitions(root, key1, &stk1);
    make_stack_of_definitions(root, key2, &stk2);

    int i = 0;

    printf("The same:\n");

    while(stk1.data[i] == stk2.data[i]) {
        printf("%s ", stk1.data[i]);
        i++;
    } printf("\n");
}

tree_err_type menu(const char* data_file_name, const char* dump_file_name) {
    int com;
    TREE tree = {};
    FILE* data_file  = nullptr;
    FILE* dump_file = nullptr;
    char subject[50] = "";
    char subject1[50] = "";
    tree_init(&tree);

    printf("commands:\n1 - load data\n2 - save_data\n3 - print_data\n4 - start session\n5 - give definition\n6 - Compare\n");

    while((scanf("%d", &com))) {
        switch(com) {
        case 1:
            if((data_file = fopen(data_file_name, "r")) == nullptr) {
                return TREE_FILE_OPEN_ERR;
            }

            if((dump_file = fopen(dump_file_name, "w")) == nullptr) {
                return TREE_FILE_OPEN_ERR;
            }

            load_data(&tree.root, data_file, dump_file);
            
            fclose(dump_file);
            fclose(data_file);
           
            break;

        case 2:
            if((data_file = fopen(data_file_name, "w")) == nullptr) {
                return TREE_FILE_OPEN_ERR;
            
            }
            save_data(tree.root, data_file);

            fclose(data_file);

            printf("Saved!\n");
            break;

        case 3:
            print_pre_order(stdout, tree.root);
            fprintf(stdout, "\n");

            break;

        case 4:
            session(tree.root);

            break;

        case 5:
            printf("I CAN GIVE DEFINITION FOR ANYTHING!\nType your subject:\n");
            scanf("%s", subject);
            if(!give_definition(tree.root, subject))
                printf("OOOOPS I CANT GIVE DEFINITION FOR IT...:(");
            printf("\n");
            break;
        case 6:
            printf("I cant compare everithing!!!!\n");
            printf("Print two objects\n");
            scanf("%s %s", subject1, subject);
            compare_difinitions(tree.root, subject1, subject);
            break;
        default:
            return TREE_NO_ERR;
        }
    }

    return TREE_NO_ERR;
}
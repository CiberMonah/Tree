#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Akinator.h"
#include "Src_Tree\Tree.h"
#include "stack.h"
#include "Src_Tree\Tree_dump.h"


tree_err_type save_data(NODE* root, FILE* fp) {
    print_pre_order(fp, root);
    return TREE_NO_ERR;
}

static void read_word(char *word, size_t size, FILE *input) {
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

tree_err_type load_data(NODE** root, FILE* fp, FILE* dump_file) {
    
    parse_data(fp, stdout, root);
    printf("Loaded succesful\n");
    rewind(fp);
    fprintf(dump_file, "\nLOADED SUCCESFUL\n");
    return TREE_NO_ERR;
}

tree_err_type guess_session (NODE* root) {
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
            guess_session(root->right);
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
            guess_session(root->left);
        }
        break;
    default:
    printf("WRONG KEYYY, ITS ONLY Y OR N STUPID HUMAN!!!!!  :-t\n");
        break;
    }

    return TREE_NO_ERR;
}

int give_definition(NODE* root, char* key) {
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
    char answer[128] = "not ";

    if(!root) {
        return 0;
    }

    if(strcmp(root->data, key) == 0) {
        stack_push(stk, key);
        return 1;
    }
    
    if(make_stack_of_definitions(root->left, key, stk)) {
        stack_push(stk, strdup(strcat(answer, root->data)));
        return 1;
    } else if(make_stack_of_definitions(root->right, strdup(root->data), stk)) {
        stack_push(stk, key);
        return 1;
    }

    return 0;
}

void compare_difinitions(NODE* root, char* key1, char* key2) {
    Stack stk1 = {};
    STK_CTOR(&stk1);
    Stack stk2 = {};
    STK_CTOR(&stk2);

    make_stack_of_definitions(root, key1, &stk1);
    make_stack_of_definitions(root, key2, &stk2);

    int i = 0;

    printf("The same:\n");
    printf("First stack:\n");
    print_stack(&stk1);
    printf("Second stack:\n");
    print_stack(&stk2);

    while(strcmp(stk1.data[i], stk2.data[i]) == 0) {
        printf("%s ", stk1.data[i]);
        i++;
    } printf("\n");

    stack_dtor(&stk1);
    stack_dtor(&stk2);
}

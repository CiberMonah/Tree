#include <stdlib.h>
#include <stdio.h>
#include "Tree.h"
#include "Akinator.h"
#include "Tree_dump.h"

int main () {
    FILE* data_file = nullptr;
    FILE* dump_file = nullptr;
    FILE* dot_file = nullptr;;

    const char* data_file_name = "akinator.txt";
    const char* dump_file_name = "dump_akinator.txt";

    int comand = 0;
    int counter = 0;

    char str1[50] = "";
    char str2[50] = "";

    TREE tree = {};
    
    tree_init(&tree);

    printf("commands:\n"
        "1 - load data\n2 - save_data"
        "\n3 - print_data"
        "\n4 - start session"
        "\n5 - give definition"
        "\n6 - Compare"
        "\n7 - make png"
        "\n9 - exit\n");

    while((scanf("%d", &comand))) {
        switch(comand) {
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
                return -1;
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
            guess_session(tree.root);

            break;
        case 5:
            printf("I CAN GIVE DEFINITION FOR ANYTHING!\nType your subject:\n");
            scanf("%s", str1);
            if(!give_definition(tree.root, str1))
                printf("OOOOPS I CANT GIVE DEFINITION FOR IT...:(");
            printf("\n");

            break;
        case 6:
            printf("I cant compare everithing!!!!\n");
            printf("Print two objects\n");
            scanf("%s %s", str2, str1);
            compare_difinitions(tree.root, str2, str1);

            break;
        case 7:
            
            make_png_dump("akinator.dot", tree.root, &counter);

            break;
        case 9:
            return 0;
            break;
        default:
            break;
        }
    }

    return 0;
}
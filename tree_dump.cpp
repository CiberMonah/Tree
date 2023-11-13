#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Tree.h"

int iteration = 0;              //Uses to make o lot of png in raw

static void print_edges(FILE* dot_file, NODE* node, const char* color) {
    if(!node) {
        return;
    }
    
    print_edges(dot_file, node->left, color);
    fprintf(dot_file, "node%p -> node%p [color = \"%s\"];\n", node, node->left, color);
    print_pre_order(dot_file, node->right);
    fprintf(dot_file, "node%p -> node%p [color = \"%s\"];\n", node, node->right, color);
}

static void print_node(FILE* dot_file, NODE* node) {
    fprintf(dot_file, "node%p[shape = Mrecord, style = filled, fillcolor=\"#DDFFDD\", label = \"NODE_%p| {<data> %s| <left> left - %p | <right> right - %p}\"];\n", node, node, node->data, node->left, node->right);
}

static void print_nodes(FILE* dot_file, NODE* node) {
    if(!node)
        return;
    print_all_nodes(dot_file, node->left);
    print_all_nodes(dot_file, node->right);
    print_node(dot_file, node);
}

static void print_all_nodes (FILE* dot_file, NODE* node) {
    fprintf(dot_file, "{rank = same;");
    
    print_nodes(dot_file, node);

    fprintf(dot_file, "}\n");
}

void make_dot_dump(FILE* dot_file, TREE* tree) {
    assert(dot_file != nullptr);

    fprintf(dot_file, "digraph G{"                          //set base settings and style
                            "rankdir = VR;\n"
                            "graph [dpi = 150];\n"
                            "ranksep = 0.5;\n"
                            "splines = ortho;\n"
                            "edge[minlen = 3, penwidth = 3];\n"
                            "graph [bgcolor=\"#31353b\"]"
	                        "node[color=\"black\",fontsize=14];\n"
	                        "edge[color=\"darkgreen\",fontcolor=\"blue\",fontsize=12];\n"
                            "node[shape = record, style = rounded, fixedsize = true, height = 1, width = 3, fontsize = 20];\n");

    fprintf(dot_file,       "{rank = min;\n"                  //set sizes of cells head tail free
		                        "head[label = \"head\", shape = Mrecord, style = filled, fillcolor=\"#007700\",width = 1];\n"
	                        "}\n"
                            "{rank = min;\n"
                                "tail[label = \"tail\", shape = Mrecord, style = filled, fillcolor=\"#FF00FF\", width = 1];\n"
                            "}\n"
                            "{rank = min;\n"
                                "free[label = \"free\", shape = Mrecord, style = filled, fillcolor=\"#FFDDFF\", width = 1];\n"
                            "}\n");
    
    print_all_nodes(dot_file, tree->root);

    print_edges(dot_file, tree->root, "#00C5CD");                 //make free edges

    fprintf(dot_file, "}");
}



void make_html_dump(FILE* dot_file, TREE* tree) {

    FILE* file_dot = nullptr;

    char dot_name[] = "my_dot*.dot";

    dot_name[6] = (char) iteration + 65;

    if ((file_dot = fopen(dot_name, "w")) == NULL) {
        printf("File creating error");
        return;
    }
    

    make_dot_dump(file_dot, tree);

    

    fclose(file_dot);                                   //dot file created

                   //0123456789012345678901234567890123456
    char comand[] = "dot my_dot*.dot -T png -o my_dot*.png";

    comand[10] = (char) iteration + 65;
    comand[32] = (char) iteration + 65;

    system(comand);      //png created

    ////////////////////////////////////////////////////////////////////////////////////////
    

    FILE* dump_txt = nullptr;

    char txt_name[] = "dump*.txt";

    txt_name[4] = (char)(iteration + 65);

    if ((dump_txt = fopen(txt_name, "w")) == NULL) {
        printf("File creating error");
        return;
    }

    // dump_list(dump_txt, list, head, tail, free_head, list_size, file, func, line);

    // ////////////////////////////////////////////////////////////////////////////////////////
    FILE* dump_html = nullptr;

    if ((dump_html = fopen("dump.html", "w")) == NULL) {
        printf("File creating error");
        return;
    }

    fprintf(dump_html, "<!DOCTYPE html>\n"
                           "<html>\n<body>\n");
    for(int i = 0; i <= iteration; i++) { 
        fprintf(dump_html, "<div> iteration : %d </div>\n", i);
        //fprintf(dump_html, "<iframe src=\"dump%c.txt\" width=\"100%%\" height=\"300\">\n</iframe>\n", (char)(i + 65));
        fprintf(dump_html, "<img src=\"my_dot%c.png\" height=\"200\">\n", (char)(i + 65));
    }

    fprintf(dump_html, "</body>\n</html>\n");

    //fclose(dump_txt);

    iteration++;
    
}

// void dump_list(FILE* dump_file, NODE* list, int head, int tail, int free_head, unsigned int list_size, const char* file, const char* func, const int line) {
//     const int NUMBER_OF_SPACES = 5;
//     fprintf(dump_file, "\nDUMP called in file: %s\n"
//             "In function: %s\n"
//             "On line: %d\n", file, func, line);

//     fprintf(dump_file,"\nSize of list: %d\n", list_size);
//     fprintf(dump_file,"\nList head: %d\n", head);
//     fprintf(dump_file,"List tail: %d\n", tail);
//     fprintf(dump_file,"free list head: %d\n", free_head);

//     fprintf(dump_file,"\nid:  ");

//     for(unsigned int i = 0; i < list_size; i ++) {
//         fprintf(dump_file, "%*d", NUMBER_OF_SPACES, i);
//     } fprintf(dump_file, "\n\n");

//     fprintf(dump_file, "data:");

//     for(unsigned int i = 0; i < list_size; i ++) {
//         if(list[i].data == FREE_DATA) 
//             fprintf(dump_file, "%*s", NUMBER_OF_SPACES, "FREE");
//         else if(list[i].data == POISON) 
//             fprintf(dump_file, "%*s", NUMBER_OF_SPACES, "POIS");
//         else 
//             fprintf(dump_file, "%*d", NUMBER_OF_SPACES, list[i].data);
//     }

//     fprintf(dump_file, "\n\n");

//     fprintf(dump_file, "next:");
    
//     for(unsigned int i = 0; i < list_size; i ++) {
//         fprintf(dump_file, "%*d", NUMBER_OF_SPACES, list[i].next_id);
//     } fprintf(dump_file, "\n\n");

//     fprintf(dump_file, "prev:");

//     for(unsigned int i = 0; i < list_size; i ++) {
//         fprintf(dump_file, "%*d", NUMBER_OF_SPACES, list[i].prev_id);
//     } fprintf(dump_file, "\n\n");
// }
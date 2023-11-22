#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Tree_dump.h"
#include "Tree.h"

static void dot_dump(FILE* file, NODE* node, int* counter) {
	setvbuf(file, NULL, _IONBF, 0);

	int counter_now = *counter;

	if (node != 0) {
		fprintf(file, "\tNode_%d [label = \"%s\", shape = \"ellipse\", style = \"filled\", fillcolor = \"#1f77b4\"]\n", (*counter), node->data);
		if (node->left != 0) {
			fprintf(file, "\tNode_%d -> Node_%d\n", counter_now, (*counter) + 1);
			(*counter)++;
			dot_dump(file, node->left, counter);
		}
		if (node->right != 0) {
			fprintf(file, "\tNode_%d -> Node_%d\n", counter_now, (*counter) + 1);
			(*counter)++;
			dot_dump(file, node->right, counter);
		}
	}
}

void make_png_dump(const char* file_name , NODE* node, int* counter) {
	FILE* dot_file = nullptr;

	if(!(dot_file = fopen(file_name, "w")))
		return;

    fprintf(dot_file, "digraph G{\n");

    dot_dump(dot_file, node, counter);

    fprintf(dot_file, "}");

	fclose(dot_file);

	system("dot tree.dot -T png -o tree.png");
}
#include <stdio.h>
#include <stdlib.h>
#include "Simple_stack.h"

int main(void) {
    Stack stk = {};
    stack_init(&stk);
    push(&stk, "cow");
    push(&stk, "rabbit");
    push(&stk, "parrot");

    pop(&stk);
    print_stack(&stk);

    //All functions work

    stack_dtor(&stk);
}
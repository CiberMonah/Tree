#include "Simple_stack.h"
#include <stdlib.h>
#include <stdio.h>

void stack_init(Stack* stk) {
    if(!stk)
        return;
    stk->size = 0;
    stk->top = 0;
    stk->data = (Stk_elem_t*)calloc(MIN_STACK_SIZE, sizeof(Stk_elem_t));
}

void stack_dtor(Stack* stk) {
    if(!stk)
        return;
    stk->size = -1;
    stk->top = -1;
    free(stk->data);
}

static int stack_resize_capacity(Stack* stk) {
    if(!stk)
        return -1;

    Stk_elem_t* temp = NULL;
    

    if ((stk->size == stk->size / SIZE_MULTIPLIER - SIZE_GISTERESIS - 1) && (stk->size / SIZE_MULTIPLIER>= MIN_STACK_SIZE)) {
        temp = (Stk_elem_t*)realloc(stk->data, stk -> size  / SIZE_MULTIPLIER * sizeof(Stk_elem_t) - SIZE_GISTERESIS);
        if(temp == NULL)
            return -1;
        stk->data = temp;
        stk->size = stk->size / SIZE_MULTIPLIER;
        return 0;
    } else if(stk->size == stk->size - 1) {
        temp = (Stk_elem_t*)realloc(stk->data, stk->size * SIZE_MULTIPLIER * sizeof(Stk_elem_t));
        if(temp == NULL)
            return -1;
        stk->data = temp;
        for(int i = 0; i < stk->size + 2; i++)
            stk->data[stk->size  + i] = 0;
        stk->size *= SIZE_MULTIPLIER;
        return 0;
    }
    return 0;
}

void push(Stack* stk, Stk_elem_t elem) {
    stk->data[stk->top] = elem;
    stk->top++;
    stack_resize_capacity(stk);
}

Stk_elem_t pop(Stack *stk) {
    Stk_elem_t value = stk->data[stk->top];
    stk->data[stk->top] = 0;
    stk->top = 0;
    stack_resize_capacity(stk);
    return value;
}



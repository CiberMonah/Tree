#ifndef SIMPLE_STACK_H_INCLUDED
#define SIMPLE_STACK_H_INCLUDED

typedef char* Stk_elem_t;

const int MIN_STACK_SIZE    = 5;
const int SIZE_MULTIPLIER   = 2;
const int SIZE_GISTERESIS   = 0;

struct Stack {
    int top;
    Stk_elem_t* data;
    int size = 0;
};

void stack_init(Stack* stk);
void stack_dtor(Stack* stk);
void push(Stack* stk, Stk_elem_t elem);
Stk_elem_t pop(Stack *stk);

#endif
#ifndef STACK_H
#define STACK_H

#include <stdio.h>

struct stack_t {
        int *data = nullptr;
        size_t size = 0;
        size_t capacity = 0;
};

// Creates stack.
void stack_ctor(stack_t *stack, size_t capacity);
// Pushes element to the stack.
void stack_push(stack_t *stack, int elem);
// Pops the elemnt out of the stack.
int stack_pop(stack_t *stack);
// Deconstructs stack.
void stack_dtor(stack_t *stack);

#endif // STACK_H

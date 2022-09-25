#ifndef STACK_H
#define STACK_H

#include <stdio.h>

typedef int elem_t;

const size_t STACK_CAPACITY = 10;

struct stack_t {
        elem_t *data = nullptr;
        size_t size = 0;
        size_t capacity = STACK_CAPACITY;
};

// Creates stack.
void stack_ctor(stack_t *stack, size_t capacity);
// Pushes element to the stack.
void stack_push(stack_t *stack, elem_t elem);
// Pops the elemnt out of the stack.
int stack_pop(stack_t *stack);
// Deconstructs stack.
void stack_dtor(stack_t *stack);

#endif // STACK_H

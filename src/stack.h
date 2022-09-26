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
int stack_ctor(stack_t *stack);
// Pushes element to the stack.
int stack_push(stack_t *stack, elem_t elem);
// Pops the elemnt out of the stack.
elem_t stack_pop(stack_t *stack);
// Deconstructs stack.
int stack_dtor(stack_t *stack);

#endif // STACK_H


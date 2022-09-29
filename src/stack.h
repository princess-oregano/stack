#ifndef STACK_H
#define STACK_H

#include <stdio.h>

#define VAR_INFO(var) ((var_info_t) {__FILE__, __LINE__, __PRETTY_FUNCTION__, #var})

typedef int elem_t;

const size_t DEF_STACK_CAPACITY = 10;

enum resize_mode_t {
        REDUCE   = -1,
        INCREASE = 1,
};

struct var_info_t {
        const char *file_name     = nullptr;
        int line                  = 0;
        const char *func_name     = nullptr;
        const char* init_var_name = nullptr;
};

struct stack_t {
        var_info_t var_info {};
        elem_t *data = nullptr;
        size_t size = 0;
        size_t capacity = 0;
};

// Creates stack.
int stack_ctor(stack_t *stack, unsigned int capacity, var_info_t var_info);
// Pushes element to the stack.
int stack_push(stack_t *stack, elem_t elem);
// Pops the elemnt out of the stack.
elem_t stack_pop(stack_t *stack);
// Deconstructs stack.
int stack_dtor(stack_t *stack);
// Prints all available information about stack.
void stack_dump(stack_t stack, var_info_t cur_var_info);

#endif // STACK_H


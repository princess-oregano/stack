#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void stack_ctor(stack_t *stack, size_t capacity)
{
        stack->data = (elem_t *) calloc(capacity, sizeof(elem_t));
}

void stack_push(stack_t *stack, elem_t elem)
{
        stack->data[stack->size] = elem;
        stack->size++;
}

elem_t stack_pop(stack_t *stack)
{
        stack->size--;
        return stack->data[stack->size];
}

void stack_dtor(stack_t *stack)
{
        free(stack->data);
}

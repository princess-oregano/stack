#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"

void stack_ctor(stack_t *stack, size_t capacity)
{
        assert(stack);

        stack->data = (elem_t *) calloc(capacity, sizeof(elem_t));
}

void stack_push(stack_t *stack, elem_t elem)
{
        assert(stack);

        if (size < capacity) {
                stack->data[stack->size] = elem;
                stack->size++;
        }
}

elem_t stack_pop(stack_t *stack)
{
        assert(stack);

        stack->size--;
        return stack->data[stack->size];
}

void stack_dtor(stack_t *stack)
{
        assert(stack);

        free(stack->data);
}

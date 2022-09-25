#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
#include "stack.h"

static void 
data_resize(elem_t **data, size_t *capacity)
{
        elem_t *stk_data_ptr = nullptr;
        *capacity *= 2;

        stk_data_ptr = (elem_t *) realloc(*data, *capacity * sizeof(stack_t));
        *data = stk_data_ptr;
}

void 
stack_ctor(stack_t *stack, size_t capacity)
{
        assert(stack);

        stack->data = (elem_t *) calloc(capacity, sizeof(elem_t));
}

void 
stack_push(stack_t *stack, elem_t elem)
{
        assert(stack);

        if (stack->size >= stack->capacity) {
                fprintf(stderr, "Resize\n");
                data_resize(&stack->data, &stack->capacity);
        }

        stack->data[stack->size++] = elem;
}

elem_t 
stack_pop(stack_t *stack)
{
        assert(stack);

        stack->size--;
        return stack->data[stack->size];
}

void 
stack_dtor(stack_t *stack)
{
        assert(stack);

        free(stack->data);
}

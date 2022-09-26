#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "error.h"
#include "stack.h"

static int
data_resize(elem_t **data, size_t *capacity)
{
        elem_t *stk_data_ptr = nullptr;
        *capacity *= 2;

        if ((stk_data_ptr = (elem_t *) realloc(*data,
                            *capacity * sizeof(stack_t))) == nullptr)
                return ERR_ALLOC;
        else
                *data = stk_data_ptr;

        return ERR_NO_ERR;
}

int
stack_ctor(stack_t *stack)
{
        assert(stack);

        if ((stack->data = (elem_t *) calloc(stack->capacity, sizeof(elem_t))) == nullptr)
                return ERR_ALLOC;

        return ERR_NO_ERR;
}

int
stack_push(stack_t *stack, elem_t elem)
{
        assert(stack);
        int err_local = ERR_NO_ERR;

        if (stack->size >= stack->capacity) {
                if ((err_local = data_resize(&stack->data, &stack->capacity)) != ERR_NO_ERR)
                        return err_local;
                fprintf(stderr, "Resize\n");
        }

        stack->data[stack->size++] = elem;

        return ERR_NO_ERR;
}

elem_t
stack_pop(stack_t *stack)
{
        assert(stack);

        stack->size--;
        return stack->data[stack->size];
}

int
stack_dtor(stack_t *stack)
{
        assert(stack);

        free(stack->data);

        return ERR_NO_ERR;
}


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "error.h"
#include "stack.h"

static int
data_resize(elem_t **data, size_t *capacity, int mode)
{
        elem_t *stk_data_ptr = nullptr;
        switch(mode) {
                case REDUCE:
                        if (*capacity > DEF_STACK_CAPACITY)
                                *capacity /= 2;
                        break;
                case INCREASE:
                        *capacity *= 2;
                        break;
                default:
                        assert(0 && "Invalid resize mode.\n");
                        break;
        }

        if ((stk_data_ptr = (elem_t *) realloc(*data,
                            *capacity * sizeof(stack_t))) == nullptr)
                return ERR_ALLOC;
        else
                *data = stk_data_ptr;

        return ERR_NO_ERR;
}

int
stack_ctor(stack_t *stack, unsigned int capacity)
{
        assert(stack);

        stack->capacity = capacity;
        if ((stack->data = (elem_t *) calloc(stack->capacity, sizeof(elem_t))) == nullptr)
                return ERR_ALLOC;

        return ERR_NO_ERR;
}

int
stack_push(stack_t *stack, elem_t elem)
{
        assert(stack);
        int err = ERR_NO_ERR;

        if (stack->size >= stack->capacity) {
                if ((err = data_resize(&stack->data, &stack->capacity, INCREASE)) != ERR_NO_ERR)
                        return err;
                fprintf(stderr, "size = %zu, capacity = %zu\n",
                                stack->size, stack->capacity);
        }

        stack->data[stack->size++] = elem;

        return ERR_NO_ERR;
}

elem_t
stack_pop(stack_t *stack)
{
        assert(stack);
        int err = ERR_NO_ERR;

        stack->size--;
        elem_t ret_val = stack->data[stack->size];

        if (2 * stack->size < stack->capacity) {
                fprintf(stderr, "size = %zu, capacity = %zu\n",
                                stack->size, stack->capacity);
                err = data_resize(&stack->data, &stack->capacity, REDUCE);
        }

        return ret_val;
}

int
stack_dtor(stack_t *stack)
{
        assert(stack);

        free(stack->data);

        return ERR_NO_ERR;
}


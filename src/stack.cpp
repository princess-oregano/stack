#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "error.h"
#include "stack.h"

static long long
data_resize(elem_t **data, size_t *capacity, int mode)
{
        err_u err {};

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
                            *capacity * sizeof(stack_t))) == nullptr) {
                err.type.ERR_ALLOC = true;
                return err.val;
        }
        else
                *data = stk_data_ptr;

        return err.val;
}

static void data_dump(stack_t stack)
{
        size_t i = 0;

        for (i = 0; i < stack.capacity; i++)
                printf("        [%zu]%d\n", i, stack.data[i]);
}

long long
stack_ctor(stack_t *stack, unsigned int capacity, var_info_t var_info)
{
        assert(stack);

        err_u err {};

        stack->var_info = var_info;

        stack->capacity = capacity;
        if ((stack->data = (elem_t *) calloc(stack->capacity, sizeof(elem_t))) == nullptr) {
                err.type.ERR_ALLOC = 1;
                return err.val;
        }

        return err.val;
}

long long
stack_push(stack_t *stack, elem_t elem)
{
        assert(stack);

        err_u err {};

        if (stack->size >= stack->capacity) {
                if ((err.val |= data_resize(&stack->data, &stack->capacity, INCREASE)) != 0)
                        return err.val;
                fprintf(stderr, "size = %zu, capacity = %zu\n",
                                stack->size, stack->capacity);
        }

        stack->data[stack->size++] = elem;

        return err.val;
}

long long
stack_pop(stack_t *stack, elem_t *ret_val)
{
        assert(stack);

        err_u err {};

        stack->size--;
        *ret_val = stack->data[stack->size];

        if (2 * stack->size < stack->capacity) {
                fprintf(stderr, "size = %zu, capacity = %zu\n",
                                stack->size, stack->capacity);
                err.val |= data_resize(&stack->data, &stack->capacity, REDUCE);
        }

        return err.val;
}

long long
stack_dtor(stack_t *stack)
{
        assert(stack);
        err_u err {};

        for (size_t i = 0; i < stack->capacity; i++)
                stack->data[i] = 0;
        stack->size = (unsigned int) -1;
        stack->capacity = (unsigned int) -1;

        if (stack->data != nullptr)   //not nullptr, bit still invalid??
                free(stack->data);

        stack->data = (elem_t *) 0xDEAD0000;

        return err.val;
}

void
stack_dump(stack_t stack, var_info_t cur_var_info)
{
        fprintf(stdout,
                "%s at %s(%d):\n"
                "%s[%p] \"%s\" at %s at %s(%d)\n"
                "       size = %zu\n"
                "       capacity = %zu\n"
                "       data[%p]:\n",
                cur_var_info.func_name, cur_var_info.file_name,
                cur_var_info.line, cur_var_info.init_var_name,
                &stack, stack.var_info.init_var_name,
                stack.var_info.func_name, stack.var_info.file_name,
                stack.var_info.line, stack.size, stack.capacity, &stack.data);

        data_dump(stack);
}


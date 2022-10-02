#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "error.h"
#include "stack.h"

static unsigned int
crc8(unsigned int crc, void *data, size_t len)
{
        unsigned char const *data_ptr = (unsigned char const *)data;

        if (data == NULL)
                return 0;

        crc &= 0xff;

        unsigned char const *end = data_ptr + len;
        while (data_ptr < end)
                crc = crc8_table[crc ^ *data_ptr++];

        return crc;
}

static long long
data_resize(stack_t *stack, size_t capacity)
{
        err_u err {};

        char *data_ptr = (char *)stack->data - sizeof(unsigned long long);

        char *stk_data_ptr_tmp = (char *) realloc(data_ptr, capacity * sizeof(elem_t) +
                                2 * sizeof(unsigned long long));

        if (stk_data_ptr_tmp == nullptr) {
                err.type.ERR_ALLOC = true;
                return err.val;
        }

        stack->capacity = capacity;

        stack->data = (elem_t *) (stk_data_ptr_tmp + sizeof(unsigned long long));

        *((unsigned long long *) stack->data - 1) = CANARY_VAL;
        *(unsigned long long *) (stack->data + stack->capacity) = CANARY_VAL;

        stack->crc_hash = 0;
        stack->crc_hash = crc8(stack->crc_hash, stack, sizeof(stack_t));

        return err.val;
}

long long
stack_ctor(stack_t *stack, unsigned int capacity, var_info_t var_info)
{
        assert(stack);

        err_u err {};
        char *tmp_data_ptr = nullptr;

        stack->var_info = var_info;
        stack->capacity = capacity;


        tmp_data_ptr = (char *) calloc(stack->capacity * sizeof(elem_t)
                         + 2 * sizeof(unsigned long long), 1);

        if (tmp_data_ptr == nullptr) {
                err.type.ERR_ALLOC = 1;
                return err.val;
        }

        stack->data = (elem_t *)(tmp_data_ptr + sizeof(unsigned long long));

        fprintf(stderr, "(unsigned long long *) stack->data = %p\n",
                         (unsigned long long *) stack->data);
        fprintf(stderr, "(unsigned long long *) stack->data - 1 = %p\n",
                         (unsigned long long *) stack->data - 1);
        *((unsigned long long *) stack->data - 1) = CANARY_VAL;
        *((unsigned long long *) (stack->data + stack->capacity)) = CANARY_VAL;

        fprintf(stderr, "stack address = %p\n", stack);
        fprintf(stderr, "sizeof(stack) = %zx\n", sizeof(stack_t));
        stack->crc_hash = crc8(0, stack, sizeof(stack_t));

        return err.val;
}

long long
stack_push(stack_t *stack, elem_t elem)
{
        assert(stack);

        err_u err {};

        if (stack->size >= stack->capacity) {
                if ((err.val |= data_resize(stack, stack->capacity*2)) != 0)
                        return err.val;
        }

        stack->data[stack->size++] = elem;

        stack->crc_hash = 0;
        stack->crc_hash = crc8(stack->crc_hash, stack, sizeof(stack_t));

        return err.val;
}

long long
stack_pop(stack_t *stack, elem_t *ret_val)
{
        assert(stack);

        err_u err {};

        stack->size--;
        *ret_val = stack->data[stack->size];
        stack->data[stack->size] = DATA_POISON;

        if (2 * stack->size < stack->capacity) {
                err.val |= data_resize(stack, stack->capacity/2);
        }

        stack->crc_hash = 0;
        stack->crc_hash = crc8(stack->crc_hash, stack, sizeof(stack_t));

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

        stack->data = (elem_t *) 0xDEAD;

        return err.val;
}

static void
data_dump(stack_t stack)
{
        size_t i = 0;

        for (i = 0; i < stack.capacity; i++)
                printf("        [%zu]0x%016llx %d\n", i, (unsigned long long) stack.data[i], stack.data[i]);
}

void
stack_dump(stack_t stack, var_info_t cur_var_info)
{
        fprintf(stdout,
                "%s at %s(%d):\n"
                "%s[%p] \"%s\" at %s at %s(%d)\n"
                "       hash = %u\n"
                "       size = %zu\n"
                "       capacity = %zu\n"
                "       data[%p]:\n",
                cur_var_info.func_name, cur_var_info.file_name,
                cur_var_info.line, cur_var_info.init_var_name,
                &stack, stack.var_info.init_var_name,
                stack.var_info.func_name, stack.var_info.file_name,
                stack.var_info.line, stack.crc_hash, stack.size,
                stack.capacity, &stack.data);

        data_dump(stack);
}


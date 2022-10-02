#include <stdio.h>
#include "stack.h"
#include "error.h"

int
main()
{
        stack_t stack {};
        err_u error {};

        stack_ctor(&stack, DEF_STACK_CAPACITY, VAR_INFO(stack));
        if (error.val != 0) {
                decypher_error(error);
                return error.val;
        }

        printf("Enter values:\n");

        elem_t value = 0;
        while (scanf("%d", &value) == 1) {
                stack_push(&stack, value);
                if (error.val) {
                        decypher_error(error);
                        return error.val;
                }
        }

        stack_dump(stack, VAR_INFO(stack));

        while (stack.size > 0) {
                elem_t ret = stack_pop(&stack);
                printf("ret = %d\n", ret);
        }

        stack_dtor(&stack);
        if (error.val != 0) {
                decypher_error(error);
                return error.val;
        }

        return 0;
}


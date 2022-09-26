#include <stdio.h>
#include "stack.h"
#include "error.h"

int main()
{
        stack_t stack {};
        unsigned int error = 0;

        if ((error |= stack_ctor(&stack)) != ERR_NO_ERR) {
                decypher_error(error);
                return error;
        }

        printf("Enter values:\n");

        elem_t value = 0;
        while (scanf("%d", &value) == 1) {
                if ((error |= stack_push(&stack, value)) != ERR_NO_ERR) {
                        decypher_error(error);
                        return error;
                }
        }

        while (stack.size > 0) {
                elem_t ret = stack_pop(&stack);
                printf("ret = %d\n", ret);
        }

        if ((error |= stack_dtor(&stack)) != ERR_NO_ERR) {
                decypher_error(error);
                return error;
        }

        return 0;
}


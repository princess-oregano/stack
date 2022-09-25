#include <stdio.h>
#include "stack.h"

int main()
{
        stack_t stack {};
        elem_t value = 0;

        printf("Enter capacity:\n");
        scanf("%zu", &stack.capacity);

        stack_ctor(&stack, stack.capacity);

        printf("Enter values:\n");
        while (scanf("%d", &value) == 1) {
                stack_push(&stack, value);
        }

        while (stack.size > 0) {
                elem_t ret = stack_pop(&stack);
                printf("ret = %d\n", ret);
        }

        stack_dtor(&stack);
}


#include <stdio.h>
#include "error.h"

void
decypher_error(unsigned int err)
{
        if (err  == ERR_NO_ERR)
                return;

        if ((err & ERR_ALLOC) == ERR_ALLOC) {
                fprintf(stderr, "Couldn't allocate memory.\n");
        }
}


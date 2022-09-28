#include <stdio.h>

enum error_t: unsigned long {
        ERR_NO_ERR = 0,
        ERR_ALLOC  = 1,
};

void decypher_error(unsigned int err);


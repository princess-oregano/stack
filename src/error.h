#include <stdio.h>

union err_t {
        long long err;
};

enum error_t: unsigned long {
        ERR_NO_ERR = 0,
        ERR_ALLOC  = 1,
};

// Prints all encountered errors stored in err variable.
void decypher_error(unsigned int err);


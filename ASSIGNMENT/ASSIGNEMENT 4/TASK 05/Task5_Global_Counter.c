#include "global_counter.h"

/* Definition exists in exactly one source file. */
int shared_token = 1000;

int next_shared_token(void)
{
    return ++shared_token;
}

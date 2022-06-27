#include <time.h>

#include "value.h"

#define UNUSED __attribute__((unused))

Value n_clock(int argc, UNUSED Value *argv)
{
    if (argc != 0)
    {
        return ERROR_ARGC;
    }
    return NUMBER_VAL((double)clock() / CLOCKS_PER_SEC);
}

Value n_triple(int argc, Value *argv)
{
    if (argc != 1)
    {
        return ERROR_ARGC;
    }
    else if (!IS_NUMBER(argv[0]))
    {
        return ERROR_ARGV;
    }

    return NUMBER_VAL(AS_NUMBER(argv[0]) * 3);
}
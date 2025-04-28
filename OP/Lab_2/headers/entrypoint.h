#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include <stddef.h>
#include "demodata.h"

typedef enum {
    OP_INIT     = 1,
    OP_LOAD     = 2,
    OP_STATS    = 3,
    OP_METRICS  = 4,
    OP_CLEANUP  = 5,
    OP_COUNT    = 6,
    OP_AT       = 7
} Operation;

int doOperations(Operation op);

#endif // ENTRYPOINT_H

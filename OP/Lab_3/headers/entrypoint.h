#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "operations.h"

typedef enum {
    OP_INIT,
    OP_LOAD,
    OP_STATS,
    OP_METRICS,
    OP_CLEANUP,
    OP_COUNT,
    OP_AT
} Operation;

int doOperations(Operation op);

#endif // ENTRYPOINT_H

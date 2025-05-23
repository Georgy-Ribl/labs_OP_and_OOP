#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "operations.h"

typedef enum {
    OP_INIT = 1,
    OP_SET_FILE,
    OP_LOAD,
    OP_STATS,
    OP_SET_REGION,
    OP_SET_COLUMN,
    OP_METRICS,
    OP_COUNT,
    OP_CLEANUP
} Operation;

int doOperations(OperationsContext* ctx,
                 Operation           op,
                 const char*         strParam = nullptr,
                 int                 numParam = 0);

#endif // ENTRYPOINT_H

#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include <stddef.h>
#include "demodata.h"

typedef enum {
    OP_INIT,
    OP_LOAD,
    OP_STATS,
    OP_METRICS,
    OP_CLEANUP,
    OP_COUNT,
    OP_AT
} Operation;

int doOperations(Operation op,
                 void* p1, void* p2,
                 void* p3, void* p4,
                 void* p5);

#endif

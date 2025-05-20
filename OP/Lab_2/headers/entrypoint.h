#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include <stddef.h>
#include "operations.h"

typedef enum {
    OP_INIT     = 1,
    OP_LOAD     = 2,
    OP_STATS    = 3,
    OP_METRICS  = 4,
    OP_CLEANUP  = 5,
    OP_COUNT    = 6,
    OP_AT       = 7
} Operation;

int doOperations(OperationsContext* ctx, Operation op);

size_t opCount(const OperationsContext* ctx);
const DemographicRecord* opAt(const OperationsContext* ctx, size_t idx);
void getOpStats(const OperationsContext* ctx, size_t* total, size_t* bad);
void getOpMetrics(const OperationsContext* ctx, double* mn, double* mx, double* md);
void setOpFileName(OperationsContext* ctx, const char* fn);
void setOpFilterRegion(OperationsContext* ctx, const char* region);
void setOpColumn(OperationsContext* ctx, int idx);

#endif

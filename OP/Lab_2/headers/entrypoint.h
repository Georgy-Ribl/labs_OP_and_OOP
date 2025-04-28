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
int opInit();
int opLoad();
void opStats();
int opMetrics();
void opCleanup();
size_t opCount();
const DemographicRecord* opAt(size_t idx);
void setOpFileName(const char* fn);
void setOpFilterRegion(const char* region);
void setOpColumn(int idx);
void getOpStats(size_t* total, size_t* bad);
void getOpMetrics(double* mn, double* mx, double* md);

#endif

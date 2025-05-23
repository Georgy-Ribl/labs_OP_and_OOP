#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

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

int doOperations(Operation op);
void setFileName(const char* fn);
void setFilterRegion(const char* region);
void setColumn(int column);
size_t getCount(void);
const DemographicRecord* getAt(size_t idx);
double getField(const DemographicRecord* record, int column);
void getMetrics(double* outMin, double* outMax, double* outMedian);

#endif

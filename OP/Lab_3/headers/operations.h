#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "demodata.h"
#include "metrics.h"
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LEN 256
#define MAX_FILTER_LEN   256

typedef struct {
    DemographicArray data;
    size_t           totalLines;
    size_t           errorLines;
    char             fileName[MAX_FILENAME_LEN];
    char             filter[MAX_FILTER_LEN];
    int              columnIndex;
    double           minValue;
    double           maxValue;
    double           medianValue;
} OperationsContext;

int  initOperationsContext(OperationsContext* ctx);
int  loadData            (OperationsContext* ctx);
void getLoadStats        (OperationsContext* ctx, size_t* total, size_t* bad);
void setFileName         (OperationsContext* ctx, const char* fn);
void setFilterRegion     (OperationsContext* ctx, const char* region);
void setColumnIndex      (OperationsContext* ctx, int idx);
int  computeMetrics      (OperationsContext* ctx);
size_t countRecords      (OperationsContext* ctx);
void cleanupOperationsContext(OperationsContext* ctx);
const DemographicRecord* opAt(const OperationsContext* ctx, size_t index);


#endif // OPERATIONS_H

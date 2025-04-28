#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <stddef.h>
#include "demodata.h"

#define MAX_FILENAME_LEN 256

typedef struct {
    DemographicArray data;
    char             fileName[MAX_FILENAME_LEN];
    char             regionFilter[FIELD_SIZE];
    int              columnIndex;
    size_t           totalLines;
    size_t           errorLines;
    double           minValue;
    double           maxValue;
    double           medianValue;
} OperationsContext;

int  initOperationsContext(OperationsContext* ctx);
int  loadData(OperationsContext* ctx);
int  computeMetrics(OperationsContext* ctx);
void cleanupOperationsContext(OperationsContext* ctx);
size_t countRecords(const OperationsContext* ctx);
const DemographicRecord* getRecordAt(const OperationsContext* ctx, size_t index);
void setFileName(OperationsContext* ctx, const char* fileName);
void setFilterRegion(OperationsContext* ctx, const char* region);
void setColumnIndex(OperationsContext* ctx, int columnIndex);
void getLoadStats(const OperationsContext* ctx, size_t* total, size_t* bad);
void getMetrics(const OperationsContext* ctx, double* mn, double* mx, double* md);

#endif

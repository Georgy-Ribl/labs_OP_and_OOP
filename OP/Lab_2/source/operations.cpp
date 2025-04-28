#include "operations.h"
#include <string.h>
#include "demodata.h"

int initOperationsContext(OperationsContext* ctx)
{
    ctx->fileName[0]    = '\0';
    ctx->regionFilter[0]= '\0';
    ctx->columnIndex    = COL_NPG;
    ctx->totalLines     = 0;
    ctx->errorLines     = 0;
    ctx->minValue       = ctx->maxValue = ctx->medianValue = 0.0;
    return initDemographicArray(&ctx->data);
}

int loadData(OperationsContext* ctx)
{
    freeDemographicArray(&ctx->data);
    int st = initDemographicArray(&ctx->data);
    if (st != OK) {
        return st;
    }
    return parseCSVFile(
        ctx->fileName,
        &ctx->data,
        &ctx->totalLines,
        &ctx->errorLines
        );
}

int computeMetrics(OperationsContext* ctx)
{
    return calculateMinMaxMedian(
        &ctx->data,
        ctx->regionFilter,
        ctx->columnIndex,
        &ctx->minValue,
        &ctx->maxValue,
        &ctx->medianValue
        );
}

void cleanupOperationsContext(OperationsContext* ctx)
{
    freeDemographicArray(&ctx->data);
}

size_t countRecords(const OperationsContext* ctx)
{
    return ctx->data.size;
}

const DemographicRecord* getRecordAt(const OperationsContext* ctx, size_t i)
{
    return (i < ctx->data.size)
    ? &ctx->data.records[i]
    : NULL;
}

void setFileName(OperationsContext* ctx, const char* fn)
{
    strncpy(ctx->fileName, fn, MAX_FILENAME_LEN - 1);
    ctx->fileName[MAX_FILENAME_LEN - 1] = '\0';
}

void setFilterRegion(OperationsContext* ctx, const char* r)
{
    strncpy(ctx->regionFilter, r, FIELD_SIZE - 1);
    ctx->regionFilter[FIELD_SIZE - 1] = '\0';
}

void setColumnIndex(OperationsContext* ctx, int c)
{
    ctx->columnIndex = c;
}

void getLoadStats(const OperationsContext* ctx, size_t* total, size_t* bad)
{
    if (total) *total = ctx->totalLines;
    if (bad)   *bad   = ctx->errorLines;
}

void getMetrics(const OperationsContext* ctx, double* mn, double* mx, double* md)
{
    if (mn) *mn = ctx->minValue;
    if (mx) *mx = ctx->maxValue;
    if (md) *md = ctx->medianValue;
}

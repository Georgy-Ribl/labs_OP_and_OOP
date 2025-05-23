#include "operations.h"

int initOperationsContext(OperationsContext* ctx) {
    ctx->totalLines = ctx->errorLines = 0;
    ctx->fileName[0] = ctx->filter[0] = '\0';
    ctx->columnIndex = COL_NPG;
    ctx->minValue = ctx->maxValue = ctx->medianValue = 0.0;
    return initDemographicArray(&ctx->data);
}

int loadData(OperationsContext* ctx) {
    freeDemographicArray(&ctx->data);
    initDemographicArray(&ctx->data);
    return parseCSVFile(ctx->fileName,
                        &ctx->data,
                        &ctx->totalLines,
                        &ctx->errorLines);
}

void getLoadStats(OperationsContext* ctx, size_t* total, size_t* bad) {
    if (total) *total = ctx->totalLines;
    if (bad)   *bad   = ctx->errorLines;
}

void setFileName(OperationsContext* ctx, const char* fn) {
    strncpy(ctx->fileName, fn, MAX_FILENAME_LEN-1);
    ctx->fileName[MAX_FILENAME_LEN-1] = '\0';
}

void setFilterRegion(OperationsContext* ctx, const char* region) {
    strncpy(ctx->filter, region, MAX_FILTER_LEN-1);
    ctx->filter[MAX_FILTER_LEN-1] = '\0';
}

void setColumnIndex(OperationsContext* ctx, int idx) {
    ctx->columnIndex = idx;
}

int computeMetrics(OperationsContext* ctx) {
    return calculate_min_max_median(
        &ctx->data,
        ctx->filter,
        ctx->columnIndex,
        &ctx->minValue,
        &ctx->maxValue,
        &ctx->medianValue
        );
}

size_t countRecords(OperationsContext* ctx) {
    return ctx->data.size;
}

void cleanupOperationsContext(OperationsContext* ctx) {
    freeDemographicArray(&ctx->data);
}

const DemographicRecord* opAt(const OperationsContext* ctx, size_t index) {
    if (!ctx || index >= ctx->data.size) return NULL;
    return &ctx->data.records[index];
}

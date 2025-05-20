#include "entrypoint.h"
#include "operations.h"

int doOperations(OperationsContext* ctx, Operation op)
{
    if (op == OP_INIT) {
        return initOperationsContext(ctx);
    } else if (op == OP_LOAD) {
        return loadData(ctx);
    } else if (op == OP_STATS) {
        return OK;
    } else if (op == OP_METRICS) {
        return computeMetrics(ctx);
    } else if (op == OP_CLEANUP) {
        cleanupOperationsContext(ctx);
        return OK;
    } else {
        return ERR_USER_INPUT;
    }
}

size_t opCount(const OperationsContext* ctx)
{
    return countRecords(ctx);
}

const DemographicRecord* opAt(const OperationsContext* ctx, size_t idx)
{
    return getRecordAt(ctx, idx);
}

void getOpStats(const OperationsContext* ctx, size_t* total, size_t* bad)
{
    getLoadStats(ctx, total, bad);
}

void getOpMetrics(const OperationsContext* ctx, double* mn, double* mx, double* md)
{
    getMetrics(ctx, mn, mx, md);
}

void setOpFileName(OperationsContext* ctx, const char* fn)
{
    setFileName(ctx, fn);
}

void setOpFilterRegion(OperationsContext* ctx, const char* region)
{
    setFilterRegion(ctx, region);
}

void setOpColumn(OperationsContext* ctx, int idx)
{
    setColumnIndex(ctx, idx);
}

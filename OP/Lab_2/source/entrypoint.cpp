#include "entrypoint.h"
#include "operations.h"

static OperationsContext g_ctx;

int opInit()
{
    return initOperationsContext(&g_ctx);
}

int opLoad()
{
    return loadData(&g_ctx);
}

void opStats()
{
}

int opMetrics()
{
    return computeMetrics(&g_ctx);
}

void opCleanup()
{
    cleanupOperationsContext(&g_ctx);
}

size_t opCount()
{
    return countRecords(&g_ctx);
}

const DemographicRecord* opAt(size_t idx)
{
    return getRecordAt(&g_ctx, idx);
}

void setOpFileName(const char* fn)
{
    setFileName(&g_ctx, fn);
}

void setOpFilterRegion(const char* region)
{
    setFilterRegion(&g_ctx, region);
}

void setOpColumn(int idx)
{
    setColumnIndex(&g_ctx, idx);
}

void getOpStats(size_t* total, size_t* bad)
{
    getLoadStats(&g_ctx, total, bad);
}

void getOpMetrics(double* mn, double* mx, double* md)
{
    getMetrics(&g_ctx, mn, mx, md);
}

int doOperations(Operation op)
{
    int result = ERR_USER_INPUT;
    if (op == OP_INIT) {
        result = opInit();
    } else if (op == OP_LOAD) {
        result = opLoad();
    } else if (op == OP_STATS) {
        opStats();
        result = OK;
    } else if (op == OP_METRICS) {
        result = opMetrics();
    } else if (op == OP_CLEANUP) {
        opCleanup();
        result = OK;
    } else if (op == OP_COUNT) {
        (void)opCount();
        result = OK;
    } else if (op == OP_AT) {
        (void)opAt(0);
        result = OK;
    }
    return result;
}

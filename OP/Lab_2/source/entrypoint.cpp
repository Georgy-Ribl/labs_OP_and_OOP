#include "entrypoint.h"
#include "operations.h"

int doOperations(OperationsContext* ctx,
                 Operation           op,
                 const char*         strParam,
                 int                 numParam)
{
    if (op == OP_INIT) {
        return initOperationsContext(ctx);
    } else if (op == OP_SET_FILE) {
        setFileName(ctx, strParam);
        return OK;
    } else if (op == OP_LOAD) {
        return loadData(ctx);
    } else if (op == OP_STATS) {
        getLoadStats(ctx, &ctx->totalLines, &ctx->errorLines);
        return OK;
    } else if (op == OP_SET_REGION) {
        setFilterRegion(ctx, strParam);
        return OK;
    } else if (op == OP_SET_COLUMN) {
        setColumnIndex(ctx, numParam);
        return OK;
    } else if (op == OP_METRICS) {
        return computeMetrics(ctx);
    } else if (op == OP_COUNT) {
        return (int)countRecords(ctx);
    } else if (op == OP_CLEANUP) {
        cleanupOperationsContext(ctx);
        return OK;
    }
    return ERR_USER_INPUT;
}

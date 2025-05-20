#include "entrypoint.h"
#include "operations.h"

int doOperations(Operation op) {
    int result;
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
        result = (int)opCount();
    } else if (op == OP_AT) {
        result = OK;
    } else {
        result = ERR_USER_INPUT;
    }
    return result;
}

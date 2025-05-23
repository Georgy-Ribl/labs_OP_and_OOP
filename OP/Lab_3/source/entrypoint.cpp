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

void setFileName(const char* fn) { setOpFileName(fn); }
void setFilterRegion(const char* region) { setOpFilterRegion(region); }
void setColumn(int column) { setOpColumn(column); }
size_t getCount(void) { return opCount(); }
const DemographicRecord* getAt(size_t idx) { return opAt(idx); }
double getField(const DemographicRecord* record, int column) { return get_field(record, column); }
void getMetrics(double* outMin, double* outMax, double* outMedian) { getOpMetrics(outMin, outMax, outMedian); }

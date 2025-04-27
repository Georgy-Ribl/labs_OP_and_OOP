#include "operations.h"

static DemographicArray gData;
static size_t           gTotal = 0, gBad = 0;

static int opInit(void* p1, void* p2, void* p3, void* p4, void* p5)
{
    gTotal = gBad = 0;
    return initDemographicArray(&gData);
}

static int opLoad(void* p1, void* p2, void* p3, void* p4, void* p5)
{
    freeDemographicArray(&gData);
    initDemographicArray(&gData);
    const char* filename = reinterpret_cast<const char*>(p1);
    return parseCSVFile(filename, &gData, &gTotal, &gBad);
}

static int opStats(void* p1, void* p2, void* p3, void* p4, void* p5)
{
    if (p1) *reinterpret_cast<size_t*>(p1) = gTotal;
    if (p2) *reinterpret_cast<size_t*>(p2) = gBad;
    return OK;
}

static int opMetrics(void* p1, void* p2, void* p3, void* p4, void* p5)
{
    const char* region = reinterpret_cast<const char*>(p1);
    int column = *reinterpret_cast<int*>(p2);
    double* mn = reinterpret_cast<double*>(p3);
    double* mx = reinterpret_cast<double*>(p4);
    double* md = reinterpret_cast<double*>(p5);
    return calculateMinMaxMedian(&gData, region, column, mn, mx, md);
}

static int opCleanup(void* p1, void* p2, void* p3, void* p4, void* p5)
{
    freeDemographicArray(&gData);
    return OK;
}

static int opCount(void* p1, void* p2, void* p3, void* p4, void* p5)
{
    if (p1) *reinterpret_cast<size_t*>(p1) = gData.size;
    return OK;
}

static int opAt(void* p1, void* p2, void* p3, void* p4, void* p5)
{
    size_t idx = *reinterpret_cast<size_t*>(p1);
    if (idx >= gData.size) return ERR_NOT_FOUND;
    *reinterpret_cast<DemographicRecord*>(p2) = gData.records[idx];
    return OK;
}

typedef int(*Func)(void*,void*,void*,void*,void*);

int dispatchOperation(Operation op,
                      void* p1, void* p2,
                      void* p3, void* p4,
                      void* p5)
{
    static Func table[] = {
        opInit,
        opLoad,
        opStats,
        opMetrics,
        opCleanup,
        opCount,
        opAt
    };
    if (op < 0 || op > OP_AT) return ERR_USER_INPUT;
    return table[op](p1, p2, p3, p4, p5);
}

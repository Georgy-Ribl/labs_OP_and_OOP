#include "operations.h"
#include <stdlib.h>
#include <string.h>

static DemographicArray gData;
static size_t           gTotal = 0, gBad = 0;
static char             gFileName[256];
static char             gFilter[256];
static int              gColumn;
static double           gMin, gMax, gMed;

int opInit()
{
    gTotal = gBad = 0;
    gFileName[0] = gFilter[0] = '\0';
    gColumn = COL_NPG;
    return initDemographicArray(&gData);
}

int opLoad()
{
    freeDemographicArray(&gData);
    initDemographicArray(&gData);
    return parseCSVFile(gFileName, &gData, &gTotal, &gBad);
}

void opStats()
{
}

int opMetrics()
{
    return calculateMinMaxMedian(&gData,
                                 gFilter,
                                 gColumn,
                                 &gMin,
                                 &gMax,
                                 &gMed);
}

void opCleanup()
{
    freeDemographicArray(&gData);
}

size_t opCount()
{
    return gData.size;
}

const DemographicRecord* opAt(size_t idx)
{
    return idx < gData.size ? &gData.records[idx] : nullptr;
}

void setOpFileName(const char* fn)
{
    strncpy(gFileName, fn, sizeof(gFileName) - 1);
    gFileName[sizeof(gFileName) - 1] = '\0';
}

void setOpFilterRegion(const char* r)
{
    strncpy(gFilter, r, sizeof(gFilter) - 1);
    gFilter[sizeof(gFilter) - 1] = '\0';
}

void setOpColumn(int idx)
{
    gColumn = idx;
}

void getOpStats(size_t* total, size_t* bad)
{
    if (total) *total = gTotal;
    if (bad)   *bad   = gBad;
}

void getOpMetrics(double* mn, double* mx, double* md)
{
    if (mn) *mn = gMin;
    if (mx) *mx = gMax;
    if (md) *md = gMed;
}

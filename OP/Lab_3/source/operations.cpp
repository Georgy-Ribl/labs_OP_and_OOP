#include "operations.h"
#include "demodata.h"
#include "metrics.h"
#include <string.h>

static DemographicArray gData;
static size_t gTotal, gBad;
static char gFileName[256];
static char gFilter[256];
static int gColumn;
static double gMin, gMax, gMed;

int opInit(void) {
    gTotal = gBad = 0;
    gFileName[0] = gFilter[0] = '\0';
    gColumn = COL_NPG;
    return initDemographicArray(&gData);
}

int opLoad(void) {
    freeDemographicArray(&gData);
    initDemographicArray(&gData);
    return parseCSVFile(gFileName, &gData, &gTotal, &gBad);
}

void opStats(void) {/* not used currently */}

int opMetrics(void) {
    return calculate_min_max_median(&gData, gFilter, gColumn, &gMin, &gMax, &gMed);
}

void opCleanup(void) {
    freeDemographicArray(&gData);
}

size_t opCount(void) { return gData.size; }
const DemographicRecord* opAt(size_t idx) { return idx<gData.size ? &gData.records[idx] : NULL; }
void setOpFileName(const char* fn)  { strncpy(gFileName, fn, sizeof(gFileName)-1); }
void setOpFilterRegion(const char* r){ strncpy(gFilter, r, sizeof(gFilter)-1); }
void setOpColumn(int c)             { gColumn = c; }
void getOpStats(size_t* t,size_t* b){ if(t)*t=gTotal; if(b)*b=gBad; }
void getOpMetrics(double* mn,double* mx,double* md){ if(mn)*mn=gMin; if(mx)*mx=gMax; if(md)*md=gMed; }

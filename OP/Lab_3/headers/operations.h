#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "demodata.h"
#include <stdlib.h>

void opStats(void);
int  opInit(void);
int  opLoad(void);
int  opMetrics(void);
void opCleanup(void);
size_t opCount(void);
const DemographicRecord* opAt(size_t idx);
void setOpFileName(const char* fn);
void setOpFilterRegion(const char* region);
void setOpColumn(int column);
void getOpStats(size_t* total, size_t* bad);
void getOpMetrics(double* min, double* max, double* median);

#endif // OPERATIONS_H

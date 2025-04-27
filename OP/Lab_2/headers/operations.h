#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "entrypoint.h"
#include "demodata.h"


int opInit();
int opLoad(const char* filename);
void opStats(size_t* total, size_t* bad);
int opMetrics(const char* region,
              int column,
              double* minVal,
              double* maxVal,
              double* medianVal);
void opCleanup();
size_t opCount();
const DemographicRecord* opAt(size_t index);

int dispatchOperation(Operation op,
                      void* p1, void* p2,
                      void* p3, void* p4,
                      void* p5);

#endif

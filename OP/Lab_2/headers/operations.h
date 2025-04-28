#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <stddef.h>
#include "demodata.h"

int     opInit();
int     opLoad();
void    opStats();
int     opMetrics();
void    opCleanup();
size_t  opCount();
const DemographicRecord* opAt(size_t idx);

void    setOpFileName    (const char* fn);
void    setOpFilterRegion(const char* r);
void    setOpColumn      (int idx);
void    getOpStats       (size_t* total, size_t* bad);
void    getOpMetrics     (double* mn, double* mx, double* md);

#endif // OPERATIONS_H

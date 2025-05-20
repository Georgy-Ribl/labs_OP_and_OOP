#ifndef METRICS_H
#define METRICS_H

#include "demodata.h"

int calculate_min_max_median(const DemographicArray* arr,
                             const char* region,
                             int column,
                             double* out_min,
                             double* out_max,
                             double* out_median);

#endif // METRICS_H

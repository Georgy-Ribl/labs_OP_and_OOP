#include "metrics.h"
#include <stdlib.h>
#include <string.h>

static void quicksort(double* v, size_t l, size_t r) {
    if (l >= r) return;
    double pivot = v[(l+r)/2];
    size_t i = l, j = r;
    while (i <= j) {
        while (v[i] < pivot) i++;
        while (v[j] > pivot) j--;
        if (i <= j) {
            double t = v[i]; v[i] = v[j]; v[j] = t;
            i++; if (j) j--;
        }
    }
    if (j > l) quicksort(v, l, j);
    if (i < r) quicksort(v, i, r);
}

int calculate_min_max_median(const DemographicArray* arr,
                             const char* region,
                             int column,
                             double* out_min,
                             double* out_max,
                             double* out_median) {
    if (!arr || arr->size == 0) return ERR_USER_INPUT;
    double* vals = NULL;
    size_t cnt = 0, cap = 0;
    for (size_t i=0; i<arr->size; ++i) {
        const DemographicRecord* r = &arr->records[i];
        if (region[0] && strcmp(r->region, region)!=0) continue;
        if (cnt >= cap) {
            size_t nc = cap ? cap*2 : 16;
            double* p = (double*)realloc(vals, nc*sizeof(double));
            if (!p) { free(vals); return ERR_MEM; }
            vals = p; cap = nc;
        }
        vals[cnt++] = get_field(r, column);
    }
    if (cnt == 0) { free(vals); return ERR_NOT_FOUND; }
    double mn = vals[0], mx = vals[0];
    for (size_t i=1; i<cnt; ++i) {
        if (vals[i]<mn) mn=vals[i];
        if (vals[i]>mx) mx=vals[i];
    }
    quicksort(vals, 0, cnt-1);
    double md = (cnt%2) ? vals[cnt/2] : (vals[cnt/2-1]+vals[cnt/2])*0.5;
    free(vals);
    *out_min = mn; *out_max = mx; *out_median = md;
    return OK;
}

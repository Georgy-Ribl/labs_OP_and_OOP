#include "demodata.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stringutils.h"

int initDemographicArray(DemographicArray* arr)
{
    arr->records  = (DemographicRecord*)malloc(10 * sizeof(DemographicRecord));
    if (!arr->records) return ERR_MEM;
    arr->size     = 0;
    arr->capacity = 10;
    return OK;
}

static int ensureCap(DemographicArray* arr)
{
    if (arr->size < arr->capacity) return OK;
    size_t nc = arr->capacity * 2;
    DemographicRecord* p = (DemographicRecord*)realloc(
        arr->records, nc * sizeof(DemographicRecord));
    if (!p) return ERR_MEM;
    arr->records  = p;
    arr->capacity = nc;
    return OK;
}

int pushDemographicRecord(DemographicArray* arr, const DemographicRecord* rec)
{
    int st = ensureCap(arr);
    if (st != OK) return st;
    arr->records[arr->size++] = *rec;
    return OK;
}

void freeDemographicArray(DemographicArray* arr)
{
    free(arr->records);
    arr->records = NULL;
    arr->size     = 0;
    arr->capacity = 0;
}

static int parseLine(const char* line, DemographicRecord* out)
{
    char buf[CSV_FIELDS_COUNT][FIELD_SIZE];
    char* ptrs[CSV_FIELDS_COUNT];
    for (int i = 0; i < CSV_FIELDS_COUNT; i++) {
        ptrs[i]    = buf[i];
        buf[i][0]  = '\0';
    }
    if (splitLine(line, ',', ptrs, CSV_FIELDS_COUNT, FIELD_SIZE))
        return ERR_PARSE;
    strncpy(out->year,        buf[0], FIELD_SIZE - 1);
    strncpy(out->region,      buf[1], FIELD_SIZE - 1);
    out->npg        = atof(buf[2]);
    out->birthRate  = atof(buf[3]);
    out->deathRate  = atof(buf[4]);
    out->gdw        = atof(buf[5]);
    out->urbanization = atof(buf[6]);
    return OK;
}

int parseCSVFile(const char* filename,
                 DemographicArray* arr,
                 size_t* totalLines,
                 size_t* errorLines)
{
    FILE* f = fopen(filename, "r");
    if (!f) return ERR_FILE;
    char line[1024];
    *totalLines = 0;
    *errorLines = 0;
    fgets(line, sizeof(line), f);
    while (fgets(line, sizeof(line), f)) {
        (*totalLines)++;
        size_t len = strlen(line);
        if (len && line[len - 1] == '\n')
            line[len - 1] = '\0';
        DemographicRecord tmp;
        if (parseLine(line, &tmp) != OK) {
            (*errorLines)++;
        } else {
            int st = pushDemographicRecord(arr, &tmp);
            if (st != OK) {
                fclose(f);
                return st;
            }
        }
    }
    fclose(f);
    return OK;
}

static void quickSort(double* v, size_t l, size_t r)
{
    if (l >= r) return;
    double  pivot = v[(l + r) / 2];
    size_t  i     = l, j = r;
    while (i <= j) {
        while (v[i] < pivot) i++;
        while (v[j] > pivot) j--;
        if (i <= j) {
            double t = v[i]; v[i] = v[j]; v[j] = t;
            i++; if (j) j--;
        }
    }
    if (j > l) quickSort(v, l, j);
    if (i < r) quickSort(v, i, r);
}

static double getVal(const DemographicRecord* r, int c)
{
    switch (c) {
    case COL_NPG: return r->npg;
    case COL_BIRTH_RATE: return r->birthRate;
    case COL_DEATH_RATE: return r->deathRate;
    case COL_GDW: return r->gdw;
    case COL_URBANIZATION: return r->urbanization;
    default: return 0.0;
    }
}

int calculateMinMaxMedian(const DemographicArray* arr,
                          const char* region,
                          int col,
                          double* mn,
                          double* mx,
                          double* md)
{
    if (!arr || arr->size == 0 || col < COL_NPG || col > COL_URBANIZATION)
        return ERR_USER_INPUT;
    double* vals = NULL;
    size_t cnt = 0, cap = 0;
    for (size_t i = 0; i < arr->size; i++) {
        const auto* r = &arr->records[i];
        if (region[0] && strcmp(r->region, region) != 0) continue;
        if (cnt >= cap) {
            size_t nc = cap ? cap * 2 : 16;
            double* p = (double*)realloc(vals, nc * sizeof(double));
            if (!p) { free(vals); return ERR_MEM; }
            vals = p; cap = nc;
        }
        vals[cnt++] = getVal(r, col);
    }
    if (cnt == 0) { free(vals); return ERR_NOT_FOUND; }
    *mn = *mx = vals[0];
    for (size_t i = 1; i < cnt; i++) {
        if (vals[i] < *mn) *mn = vals[i];
        if (vals[i] > *mx) *mx = vals[i];
    }
    quickSort(vals, 0, cnt - 1);
    *md = (cnt % 2)
              ? vals[cnt / 2]
              : (vals[cnt/2 - 1] + vals[cnt/2]) * 0.5;
    free(vals);
    return OK;
}

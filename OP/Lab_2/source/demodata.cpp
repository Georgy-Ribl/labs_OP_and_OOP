#include "demodata.h"
#include "stringutils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 10

int initDemographicArray(DemographicArray* arr)
{
    arr->records  = (DemographicRecord*)malloc(
        INITIAL_CAPACITY * sizeof(DemographicRecord)
        );
    if (!arr->records) {
        return ERR_MEM;
    }
    arr->size     = 0;
    arr->capacity = INITIAL_CAPACITY;
    return OK;
}

static int ensureCapacity(DemographicArray* arr)
{
    if (arr->size < arr->capacity) {
        return OK;
    }
    size_t newCap = arr->capacity * 2;
    DemographicRecord* tmp = (DemographicRecord*)realloc(
        arr->records,
        newCap * sizeof(DemographicRecord)
        );
    if (!tmp) {
        return ERR_MEM;
    }
    arr->records  = tmp;
    arr->capacity = newCap;
    return OK;
}

int pushDemographicRecord(DemographicArray* arr,
                          const DemographicRecord* rec)
{
    int st = ensureCapacity(arr);
    if (st != OK) {
        return st;
    }
    arr->records[arr->size++] = *rec;
    return OK;
}

void freeDemographicArray(DemographicArray* arr)
{
    free(arr->records);
    arr->records  = NULL;
    arr->size     = 0;
    arr->capacity = 0;
}

static int parseLine(const char* line, DemographicRecord* out)
{
    char buf[CSV_FIELDS_COUNT][FIELD_SIZE];
    char* ptrs[CSV_FIELDS_COUNT];
    for (size_t i = 0; i < CSV_FIELDS_COUNT; ++i) {
        ptrs[i]   = buf[i];
        buf[i][0] = '\0';
    }
    if (splitLine(line, ',', ptrs, CSV_FIELDS_COUNT, FIELD_SIZE)) {
        return ERR_PARSE;
    }
    strncpy(out->year,   buf[0], FIELD_SIZE - 1);
    out->year[FIELD_SIZE - 1] = '\0';
    strncpy(out->region, buf[1], FIELD_SIZE - 1);
    out->region[FIELD_SIZE - 1] = '\0';
    out->npg          = atof(buf[2]);
    out->birthRate    = atof(buf[3]);
    out->deathRate    = atof(buf[4]);
    out->gdw          = atof(buf[5]);
    out->urbanization = atof(buf[6]);
    return OK;
}

int parseCSVFile(const char* filename,
                 DemographicArray* arr,
                 size_t* totalLines,
                 size_t* errorLines)
{
    FILE* f = fopen(filename, "r");
    if (!f) {
        return ERR_FILE;
    }
    char line[1024];
    *totalLines = 0;
    *errorLines = 0;
    if (!fgets(line, sizeof(line), f)) {
        fclose(f);
        return ERR_PARSE;
    }
    while (fgets(line, sizeof(line), f)) {
        (*totalLines)++;
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        DemographicRecord rec;
        if (parseLine(line, &rec) != OK) {
            (*errorLines)++;
        } else {
            int st = pushDemographicRecord(arr, &rec);
            if (st != OK) {
                fclose(f);
                return st;
            }
        }
    }
    fclose(f);
    return OK;
}

static void quickSort(double* a, size_t l, size_t r)
{
    if (l >= r) {
        return;
    }
    double pivot = a[(l + r) / 2];
    size_t i = l, j = r;
    while (i <= j) {
        while (a[i] < pivot) i++;
        while (a[j] > pivot) {
            if (j == 0) break;
            j--;
        }
        if (i <= j) {
            double tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
            i++;
            if (j > 0) j--;
        }
    }
    if (j > l) quickSort(a, l, j);
    if (i < r) quickSort(a, i, r);
}

static double getValueByColumn(const DemographicRecord* r, int c)
{
    switch (c) {
    case COL_NPG:          return r->npg;
    case COL_BIRTH_RATE:   return r->birthRate;
    case COL_DEATH_RATE:   return r->deathRate;
    case COL_GDW:          return r->gdw;
    case COL_URBANIZATION: return r->urbanization;
    default:               return 0.0;
    }
}

int calculateMinMaxMedian(const DemographicArray* arr,
                          const char* region,
                          int columnIndex,
                          double* mn,
                          double* mx,
                          double* md)
{
    if (!arr || arr->size == 0 ||
        columnIndex < COL_NPG ||
        columnIndex > COL_URBANIZATION)
    {
        return ERR_USER_INPUT;
    }
    double* vals   = NULL;
    size_t count   = 0;
    size_t capVals = 0;
    for (size_t i = 0; i < arr->size; ++i) {
        const DemographicRecord* rec = &arr->records[i];
        if (region[0] && strcmp(rec->region, region) != 0) {
            continue;
        }
        if (count >= capVals) {
            size_t nc = capVals ? capVals * 2 : 16;
            double* p = (double*)realloc(vals, nc * sizeof(double));
            if (!p) {
                free(vals);
                return ERR_MEM;
            }
            vals   = p;
            capVals = nc;
        }
        vals[count++] = getValueByColumn(rec, columnIndex);
    }
    if (count == 0) {
        free(vals);
        return ERR_NOT_FOUND;
    }
    *mn = *mx = vals[0];
    for (size_t i = 1; i < count; ++i) {
        if (vals[i] < *mn) *mn = vals[i];
        if (vals[i] > *mx) *mx = vals[i];
    }
    quickSort(vals, 0, count - 1);
    if (count % 2) {
        *md = vals[count / 2];
    } else {
        *md = (vals[count/2 - 1] + vals[count/2]) * 0.5;
    }
    free(vals);
    return OK;
}

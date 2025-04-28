#ifndef DEMODATA_H
#define DEMODATA_H

#include <stddef.h>

#define OK               0
#define ERR_FILE         1
#define ERR_MEM          2
#define ERR_PARSE        3
#define ERR_USER_INPUT   4
#define ERR_NOT_FOUND    5

#define FIELD_SIZE        128
#define CSV_FIELDS_COUNT    7
#define MAX_LINE_LENGTH  1024

#define COL_NPG            3
#define COL_BIRTH_RATE     4
#define COL_DEATH_RATE     5
#define COL_GDW            6
#define COL_URBANIZATION   7

typedef struct {
    char   year[FIELD_SIZE];
    char   region[FIELD_SIZE];
    double npg;
    double birthRate;
    double deathRate;
    double gdw;
    double urbanization;
} DemographicRecord;

typedef struct {
    DemographicRecord* records;
    size_t             size;
    size_t             capacity;
} DemographicArray;

int initDemographicArray(DemographicArray* arr);

int pushDemographicRecord(DemographicArray* arr, const DemographicRecord* rec);

void freeDemographicArray(DemographicArray* arr);

int parseCSVFile(const char* filename,
                 DemographicArray* arr,
                 size_t* totalLines,
                 size_t* errorLines);

int calculateMinMaxMedian(const DemographicArray* arr,
                          const char* region,
                          int columnIndex,
                          double* minVal,
                          double* maxVal,
                          double* medianVal);

#endif // DEMODATA_H

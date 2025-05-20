#ifndef DEMODATA_H
#define DEMODATA_H

#include <stdlib.h>

#define FIELD_SIZE 64
#define CSV_FIELDS_COUNT 7

#define COL_YEAR           0
#define COL_REGION         1
#define COL_NPG            2
#define COL_BIRTH_RATE     3
#define COL_DEATH_RATE     4
#define COL_GDW            5
#define COL_URBANIZATION   6

#define OK             0
#define ERR_MEM       -1
#define ERR_PARSE     -2
#define ERR_FILE      -3
#define ERR_USER_INPUT -4
#define ERR_NOT_FOUND -5

typedef struct {
    char year[FIELD_SIZE];
    char region[FIELD_SIZE];
    double npg;
    double birthRate;
    double deathRate;
    double gdw;
    double urbanization;
} DemographicRecord;

typedef struct {
    DemographicRecord* records;
    size_t size;
    size_t capacity;
} DemographicArray;

int initDemographicArray(DemographicArray* arr);
void freeDemographicArray(DemographicArray* arr);
int parseCSVFile(const char* filename,
                 DemographicArray* arr,
                 size_t* totalLines,
                 size_t* errorLines);

double get_field(const DemographicRecord* r, int col);

#endif // DEMODATA_H

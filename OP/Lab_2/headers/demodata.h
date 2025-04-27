#ifndef DEMODATA_H
#define DEMODATA_H

#include <stddef.h>

#define OK              0
#define ERR_FILE        1
#define ERR_MEM         2
#define ERR_USER_INPUT  3
#define ERR_NOT_FOUND   4
#define FIELD_SIZE      128
#define CSV_FIELDS      7

#define COL_NPG          3
#define COL_BIRTH_RATE   4
#define COL_DEATH_RATE   5
#define COL_GDW          6
#define COL_URBANIZATION 7

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

int  initDemographicArray (DemographicArray* a);
int  pushDemographicRecord(DemographicArray* a,const DemographicRecord* r);
void freeDemographicArray (DemographicArray* a);

int  parseCSVFile (const char* file,DemographicArray* a,
                 size_t* total,size_t* bad);
int  calculateMinMaxMedian(const DemographicArray* a,const char* region,
                          int col,double* mn,double* mx,double* med);

#endif

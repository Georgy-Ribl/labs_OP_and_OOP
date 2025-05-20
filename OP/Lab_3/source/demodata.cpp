#include "demodata.h"
#include "stringutils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int initDemographicArray(DemographicArray* arr) {
    arr->records = (DemographicRecord*)malloc(10 * sizeof(DemographicRecord));
    if (!arr->records) return ERR_MEM;
    arr->size = 0;
    arr->capacity = 10;
    return OK;
}

void freeDemographicArray(DemographicArray* arr) {
    free(arr->records);
    arr->records = NULL;
    arr->size = arr->capacity = 0;
}

int parseCSVFile(const char* filename,
                 DemographicArray* arr,
                 size_t* totalLines,
                 size_t* errorLines) {
    FILE* f = fopen(filename, "r");
    if (!f) return ERR_FILE;
    char line[1024];
    *totalLines = *errorLines = 0;
    fgets(line, sizeof(line), f); // skip header
    while (fgets(line, sizeof(line), f)) {
        (*totalLines)++;
        size_t len = strlen(line);
        if (len && line[len-1]=='\n') line[len-1] = '\0';
        DemographicRecord tmp;
        char buf[CSV_FIELDS_COUNT][FIELD_SIZE];
        char* ptrs[CSV_FIELDS_COUNT];
        for (int i=0; i<CSV_FIELDS_COUNT; i++) {
            ptrs[i] = buf[i]; buf[i][0] = '\0';
        }
        if (splitLine(line, ',', ptrs, CSV_FIELDS_COUNT, FIELD_SIZE)) {
            (*errorLines)++;
            continue;
        }
        strncpy(tmp.year,   buf[0], FIELD_SIZE-1);
        strncpy(tmp.region, buf[1], FIELD_SIZE-1);
        tmp.npg          = atof(buf[2]);
        tmp.birthRate    = atof(buf[3]);
        tmp.deathRate    = atof(buf[4]);
        tmp.gdw          = atof(buf[5]);
        tmp.urbanization = atof(buf[6]);

        if (arr->size >= arr->capacity) {
            size_t nc = arr->capacity * 2;
            DemographicRecord* p = (DemographicRecord*)realloc(
                arr->records, nc * sizeof(DemographicRecord));
            if (!p) { fclose(f); return ERR_MEM; }
            arr->records = p;
            arr->capacity = nc;
        }
        arr->records[arr->size++] = tmp;
    }
    fclose(f);
    return OK;
}

double get_field(const DemographicRecord* r, int col) {
    switch(col) {
        case COL_NPG: return r->npg;
        case COL_BIRTH_RATE: return r->birthRate;
        case COL_DEATH_RATE: return r->deathRate;
        case COL_GDW: return r->gdw;
        case COL_URBANIZATION: return r->urbanization;
        default: return 0.0;
    }
}

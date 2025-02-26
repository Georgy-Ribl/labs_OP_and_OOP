#ifndef ENTRY_POINT_H
#define ENTRY_POINT_H

#include "converter.h"

#define SUCCESS 0
#define ERROR -1
#define SIZE 33


typedef struct {
    char inputString[SIZE];
    char errorMessage[SIZE];
    char* outputString;
    int sourceBase;
    int targetBase;
} AppContext;

void initAppContext(AppContext* context);
void setInputData(AppContext* context, const char* input, int sourceBase, int targetBase);
int performConversion(AppContext* context);
void cleanupAppContext(AppContext* context);

#endif // ENTRY_POINT_H

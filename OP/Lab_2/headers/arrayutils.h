#ifndef ARRAYUTILS_H
#define ARRAYUTILS_H

#include <stddef.h>
#define OK      0
#define ERR_MEM 2

typedef struct {
    void*  data;
    size_t elementSize;
    size_t size;
    size_t capacity;
} DynamicArray;

int    daInit     (DynamicArray* arr, size_t initialCap, size_t elemSize);
int    daPushBack (DynamicArray* arr, const void* elem);
void*  daGet      (const DynamicArray* arr, size_t index);
void   daFree     (DynamicArray* arr);

#endif // ARRAYUTILS_H

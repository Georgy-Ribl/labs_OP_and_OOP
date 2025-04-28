#ifndef ARRAYUTILS_H
#define ARRAYUTILS_H

#include <stddef.h>

#define ERR_MEM 2

typedef struct {
    void*  data;
    size_t elementSize;
    size_t size;
    size_t capacity;
} DynamicArray;


int daInit(DynamicArray* arr, size_t initialCapacity, size_t elementSize);

int daPushBack(DynamicArray* arr, const void* element);

void* daGet(const DynamicArray* arr, size_t index);

void daFree(DynamicArray* arr);

#endif // ARRAYUTILS_H

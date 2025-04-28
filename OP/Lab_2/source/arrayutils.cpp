#include "arrayutils.h"
#include <stdlib.h>
#include <string.h>

static int ensureCapacity(DynamicArray* arr)
{
    if (arr->size < arr->capacity) {
        return 0;
    }
    size_t newCap = arr->capacity ? arr->capacity * 2 : 1;
    void* tmp = realloc(arr->data, newCap * arr->elementSize);
    if (!tmp) {
        return ERR_MEM;
    }
    arr->data     = tmp;
    arr->capacity = newCap;
    return 0;
}

int daInit(DynamicArray* arr, size_t initialCapacity, size_t elementSize)
{
    arr->data        = NULL;
    arr->size        = 0;
    arr->capacity    = 0;
    arr->elementSize = elementSize;
    if (initialCapacity) {
        arr->data = malloc(initialCapacity * elementSize);
        if (!arr->data) {
            return ERR_MEM;
        }
        arr->capacity = initialCapacity;
    }
    return 0;
}

int daPushBack(DynamicArray* arr, const void* element)
{
    int st = ensureCapacity(arr);
    if (st) {
        return st;
    }
    memcpy((char*)arr->data + arr->size * arr->elementSize,
           element,
           arr->elementSize);
    arr->size += 1;
    return 0;
}

void* daGet(const DynamicArray* arr, size_t idx)
{
    if (idx >= arr->size) {
        return NULL;
    }
    return (char*)arr->data + idx * arr->elementSize;
}

void daFree(DynamicArray* arr)
{
    free(arr->data);
    arr->data        = NULL;
    arr->size        = 0;
    arr->capacity    = 0;
    arr->elementSize = 0;
}

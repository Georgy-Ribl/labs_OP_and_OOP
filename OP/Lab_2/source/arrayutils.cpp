#include "arrayutils.h"
#include <stdlib.h>
#include <string.h>

static int ensureCap(DynamicArray* a)
{
    if (a->size < a->capacity) return OK;
    size_t nc = a->capacity ? a->capacity * 2 : 1;
    void*  p  = realloc(a->data, nc * a->elementSize);
    if (!p) return ERR_MEM;
    a->data     = p;
    a->capacity = nc;
    return OK;
}

int daInit(DynamicArray* a, size_t c, size_t es)
{
    a->data        = NULL;
    a->size        = 0;
    a->capacity    = 0;
    a->elementSize = es;
    return ensureCap(a);
}

int daPushBack(DynamicArray* a, const void* e)
{
    int st = ensureCap(a);
    if (st != OK) return st;
    memcpy((char*)a->data + a->size * a->elementSize, e, a->elementSize);
    a->size++;
    return OK;
}

void* daGet(const DynamicArray* a, size_t idx)
{
    return idx < a->size ? (char*)a->data + idx * a->elementSize : NULL;
}

void daFree(DynamicArray* a)
{
    free(a->data);
    a->data     = NULL;
    a->size     = 0;
    a->capacity = 0;
    a->elementSize = 0;
}

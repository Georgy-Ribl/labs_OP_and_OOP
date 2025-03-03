#include "memory_utils.h"

int allocateString(char** str, size_t size)
{
    *str = (char*)malloc(size);
    if (*str == NULL) {
        return MEMORY_ERROR;
    }
    return SUCCESS;
}

void freeString(char* str)
{
    if (str) {
        free(str);
    }
}

int copyString(char* dest, const char* src, size_t maxLength)
{
    if (src == NULL || dest == NULL) {
        return MEMORY_ERROR;
    }

    strncpy(dest, src, maxLength);
    dest[maxLength - 1] = '\0';

    return SUCCESS;
}

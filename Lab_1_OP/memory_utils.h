#ifndef MEMORY_UTILS_H
#define MEMORY_UTILS_H

#include <stdlib.h>
#include <string.h>

#define MEMORY_ERROR -1
#define SUCCESS 0


int allocateString(char** str, size_t size);
void freeString(char* str);
int copyString(char* dest, const char* src, size_t maxLength);

#endif // MEMORY_UTILS_H

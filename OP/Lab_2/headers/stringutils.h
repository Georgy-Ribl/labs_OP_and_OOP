#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <stddef.h>

#define MAX_LINE_LENGTH 1024

int splitLine(const char* line,
              char        delimiter,
              char**      tokens,
              size_t      tokenCount,
              size_t      tokenBufSize);

#endif // STRINGUTILS_H

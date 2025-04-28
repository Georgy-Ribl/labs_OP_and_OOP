#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <stddef.h>

int splitLine(const char* line,
              char delimiter,
              char** tokens,
              size_t count,
              size_t tokenBufSize);

#endif // STRINGUTILS_H

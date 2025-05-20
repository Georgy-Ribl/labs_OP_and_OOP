#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <stdlib.h>

int splitLine(const char* line,
              char delimiter,
              char** tokens,
              size_t tokenCount,
              size_t bufSize);

#endif // STRINGUTILS_H

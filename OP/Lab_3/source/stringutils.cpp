#include "stringutils.h"
#include <string.h>

int splitLine(const char* line,
              char delimiter,
              char** tokens,
              size_t tokenCount,
              size_t bufSize) {
    char tmp[1024];
    strncpy(tmp, line, sizeof(tmp)-1);
    tmp[sizeof(tmp)-1] = '\0';
    size_t n = 0;
    char ds[2] = {delimiter, '\0'};
    char* p = strtok(tmp, ds);
    while (p && n < tokenCount) {
        strncpy(tokens[n], p, bufSize-1);
        tokens[n][bufSize-1] = '\0';
        ++n;
        p = strtok(NULL, ds);
    }
    return n == tokenCount ? 0 : 1;
}

#include "stringutils.h"
#include <string.h>

int splitLine(const char* line,
              char        delimiter,
              char**      tokens,
              size_t      tokenCount,
              size_t      tokenBufSize)
{
    char tmp[MAX_LINE_LENGTH];
    strncpy(tmp, line, MAX_LINE_LENGTH - 1);
    tmp[MAX_LINE_LENGTH - 1] = '\0';

    size_t n = 0;
    char*  tok = strtok(tmp, &delimiter);
    while (tok && n < tokenCount) {
        strncpy(tokens[n], tok, tokenBufSize - 1);
        tokens[n][tokenBufSize - 1] = '\0';
        n++;
        tok = strtok(NULL, &delimiter);
    }
    return (n == tokenCount) ? 0 : 1;
}

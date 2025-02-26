#include "converter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory_utils.h"

ErrorCode parseStringToInt32(const char* input, int base, uint32_t* outputValue)
{
    ErrorCode resultFlag = ERROR_NONE;

    if (!input || !outputValue) {
        resultFlag = ERROR_MEMORY_ALLOCATION;
    } else if (base < 2 || base > 36) {
        resultFlag = ERROR_INVALID_DIGIT;
    } else {
        char* endPtr = NULL;
        long result = strtol(input, &endPtr, base);

        if (*endPtr != '\0') {
            resultFlag = ERROR_INVALID_DIGIT;
        } else if (result < INT32_MIN || result > INT32_MAX) {
            resultFlag = ERROR_OUT_OF_RANGE;
        } else {
            *outputValue = (uint32_t)result;
        }
    }

    return resultFlag;
}

ErrorCode convertToTwoComplement(uint32_t value, int base, char** resultString)
{
    ErrorCode resultFlag = ERROR_NONE;

    if (base != 2 && base != 8 && base != 16) {
        resultFlag = ERROR_INVALID_DIGIT;
    } else {
        uint32_t twoComplement = value;

        if (value < 0) {
            twoComplement = (1U << 31) + value;
        }

        resultFlag = convertInt32ToString(twoComplement, base, resultString);
    }

    return resultFlag;
}


ErrorCode convertInt32ToString(uint32_t value, int base, char** resultString)
{
    ErrorCode resultFlag = ERROR_NONE;

    if (!resultString) {
        resultFlag = ERROR_MEMORY_ALLOCATION;
    } else if (base < 2 || base > 36) {
        resultFlag = ERROR_INVALID_DIGIT;
    } else {
        *resultString = NULL;

        size_t bufferSize = 35;
        char* buffer = NULL;

        if (allocateString(&buffer, bufferSize) != SUCCESS) {
            resultFlag = ERROR_MEMORY_ALLOCATION;
        } else {
            if (value == 0) {
                copyString(buffer, "0", bufferSize);
                *resultString = buffer;
            } else {
                int isNegative = (value < 0) ? 1 : 0;
                long long temp = (long long)value;
                if (isNegative) {
                    temp = -temp;
                }

                int pos = 0;
                while (temp > 0 && pos < (int)(bufferSize - 1)) {
                    int digit = (int)(temp % base);
                    temp /= base;

                    if (digit < 10) {
                        buffer[pos++] = (char)('0' + digit);
                    } else {
                        buffer[pos++] = (char)('A' + (digit - 10));
                    }
                }

                if (isNegative && pos < (int)(bufferSize - 1)) {
                    buffer[pos++] = '-';
                }

                buffer[pos] = '\0';

                for (int i = 0; i < pos / 2; i++) {
                    char tmp = buffer[i];
                    buffer[i] = buffer[pos - 1 - i];
                    buffer[pos - 1 - i] = tmp;
                }

                *resultString = buffer;
            }
        }
    }

    return resultFlag;
}

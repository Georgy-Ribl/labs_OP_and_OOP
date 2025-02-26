#ifndef CONVERTER_H
#define CONVERTER_H

#include <stdint.h>

typedef enum {
    ERROR_NONE = 0,
    ERROR_INVALID_DIGIT,
    ERROR_OUT_OF_RANGE,
    ERROR_MEMORY_ALLOCATION
} ErrorCode;

ErrorCode parseStringToInt32(const char* input, int base, uint32_t* outputValue);
ErrorCode convertInt32ToString(uint32_t value, int base, char** resultString);
ErrorCode convertToTwoComplement(uint32_t value, int base, char** resultString);

#endif // CONVERTER_H

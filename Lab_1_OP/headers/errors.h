#ifndef ERRORS_H
#define ERRORS_H

typedef enum {
    ERROR_NONE = 0,
    ERROR_MEMORY_ALLOCATION,
    ERROR_INVALID_DIGIT,
    ERROR_OUT_OF_RANGE,
    ERROR_NULL_POINTER,
    ERROR_UNKNOWN
} ErrorCode;

#endif // ERRORS_H

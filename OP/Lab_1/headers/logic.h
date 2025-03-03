#ifndef LOGIC_H
#define LOGIC_H

#include "errors.h"  // Для ErrorCode

// Прототипы функций
void doInit(int32_t *context);
void doDelinit(int32_t *context);
void doConvert(int32_t *context, const char *number, int baseFrom, int baseTo);
int validateNumber(const char *number, int baseFrom);
void convertFromDecimal(int32_t *context, const char *number, int baseTo);
void convertToDecimal(int32_t *context, const char *number, int baseFrom);

#endif // LOGIC_H

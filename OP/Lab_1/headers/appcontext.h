#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include <stdint.h>

typedef struct {
    char inputString[256];  // Вводимое число
    char errorMessage[256]; // Сообщение об ошибке
    char* outputString;     // Результат конвертации
    int sourceBase;         // Исходная система счисления
    int targetBase;         // Целевая система счисления
} AppContext;

void initAppContext(AppContext* context);
void cleanupAppContext(AppContext* context);
void setInputData(AppContext* context, const char* input, int sourceBase, int targetBase);

#endif // APPCONTEXT_H

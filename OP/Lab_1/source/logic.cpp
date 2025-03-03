#include "logic.h"
#include <stdlib.h>
#include <stdio.h>

void doInit(int32_t *context) {
    *context = 0;  // Инициализация контекста
}

void doDelinit(int32_t *context) {
    // Освобождение ресурсов, если нужно
}

void doConvert(int32_t *context, const char *number, int baseFrom, int baseTo) {
    // Преобразование числа из одной системы счисления в другую
    if (baseFrom == 10) {
        convertFromDecimal(context, number, baseTo);
    } else if (baseTo == 10) {
        convertToDecimal(context, number, baseFrom);
    }
}

int validateNumber(const char *number, int baseFrom) {
    // Валидация числа
    size_t len = strlen(number);
    if (len == 0) return ERROR_INVALID_DIGIT;

    for (size_t i = 0; i < len; ++i) {
        char c = number[i];
        if ((baseFrom == 2 && (c != '0' && c != '1')) ||
            (baseFrom == 8 && (c < '0' || c > '7')) ||
            (baseFrom == 10 && (c < '0' || c > '9')) ||
            (baseFrom == 16 && !((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f')))) {
            return ERROR_INVALID_DIGIT;  // Неправильный символ
        }
    }
    return ERROR_NONE;
}

void convertFromDecimal(int32_t *context, const char *number, int baseTo) {
    int num = atoi(number);  // Преобразуем строку в число
    char result[33];
    if (baseTo == 2) {
        itoa(num, result, 2);  // Преобразование в двоичную систему
    } else if (baseTo == 8) {
        itoa(num, result, 8);  // Преобразование в восьмеричную
    } else if (baseTo == 16) {
        itoa(num, result, 16); // Преобразование в шестнадцатеричную
    }
    *context = atoi(result);
}

void convertToDecimal(int32_t *context, const char *number, int baseFrom) {
    int num = strtol(number, NULL, baseFrom);  // Преобразование в десятичную
    *context = num;
}

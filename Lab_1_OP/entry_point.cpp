#include "entry_point.h"
#include "converter.h"
#include <string.h>
#include <stdlib.h>

#define SUCCESS 0
#define ERROR -1

int performConversion(AppContext* context)
{
    int resultFlag = SUCCESS;

    if (context == NULL) {
        resultFlag = ERROR;
    } else {
        int32_t value = 0;
        ErrorCode parseResult = parseStringToInt32(context->inputString, context->sourceBase, &value);
        if (parseResult != ERROR_NONE) {
            switch (parseResult) {
            case ERROR_INVALID_DIGIT:
                strcpy(context->errorMessage, "Ошибка: недопустимые символы.");
                break;
            case ERROR_OUT_OF_RANGE:
                strcpy(context->errorMessage, "Ошибка: число выходит за пределы.");
                break;
            default:
                strcpy(context->errorMessage, "Неизвестная ошибка парсинга.");
                break;
            }
            resultFlag = ERROR;
        } else {
            char* resultString = NULL;
            ErrorCode convertResult = ERROR_NONE;

            if (context->targetBase == 10) {
                convertResult = convertInt32ToString(value, context->targetBase, &resultString);
            } else {
                convertResult = convertToTwoComplement(value, context->targetBase, &resultString);
            }

            if (convertResult != ERROR_NONE) {
                strcpy(context->errorMessage, "Ошибка при конвертации.");
                resultFlag = ERROR;
            } else {
                context->outputString = resultString;
            }
        }
    }

    return resultFlag;
}


void initAppContext(AppContext* context)
{
    if (context == NULL) return;
    memset(context->inputString, 0, sizeof(context->inputString));
    memset(context->errorMessage, 0, sizeof(context->errorMessage));
    context->outputString = NULL;
    context->sourceBase = 10;
    context->targetBase = 2;
}

void setInputData(AppContext* context, const char* input, int sourceBase, int targetBase)
{
    if (context == NULL) return;
    memset(context->errorMessage, 0, sizeof(context->errorMessage));

    if (input != NULL) {
        strncpy(context->inputString, input, sizeof(context->inputString) - 1);
    } else {
        context->inputString[0] = '\0';
    }

    context->sourceBase = sourceBase;
    context->targetBase = targetBase;
}

void cleanupAppContext(AppContext* context)
{
    if (context == NULL) return;
    if (context->outputString != NULL) {
        free(context->outputString);
        context->outputString = NULL;
    }
}

#ifndef __kOpts_h__
#define __kOpts_h__
#include <stdlib.h>

typedef enum kOpts {
    OPT_D,        // Исключить арабские цифры
    OPT_I,        // Подсчитать количество латинских букв
    OPT_S,        // Подсчитать символы, отличные от латинских букв, цифр и пробелов
    OPT_A,        // Заменить символы, отличные от цифр, на их ASCII код в 16-ричной системе
    OPT_UNKNOWN   // Неизвестный флаг
} kOpts;

void RemoveDigits(const char* input_path, const char* output_path);
void CountLatinLetters(const char* input_path, const char* output_path);
void CountSpecialCharacters(const char* input_path, const char* output_path);
void ReplaceNonDigitsWithAscii(const char* input_path, const char* output_path);
int GetOpts(int argc, char** argv, kOpts* opt);

#endif

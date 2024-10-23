#ifndef ERRORS_H
#define ERRORS_H

typedef enum ErrorCode {
    OK,
    ERR_INVALID_ARG,// Некорректный арг. или флаг
    ERR_NO_STRING,  // мало строк
    ERR_INVALID_NUM, // фу число для seed
    ERR_TOO_MANY_ARGS, // Слишком много аргументов
    ERR_TOO_FEW_ARGS,   // Слишком мало аргументов
    ERR_MEMORY_ALLOCATION
} ErrorCode;

const char* error_messages[] = {
        [ERR_INVALID_ARG] = "Error: invalid flag or argument.\n", // Ошибка: некорректный флаг или аргумент.
        [ERR_NO_STRING] = "Error: no string provided.\n", // Ошибка: отсутствует строка.
        [ERR_INVALID_NUM] = "Error: invalid value for seed.\n", // Ошибка: некорректное значение для seed.
        [ERR_TOO_MANY_ARGS] = "Error: too many arguments for the flag.\n", // Ошибка: слишком много аргументов для флага.
        [ERR_TOO_FEW_ARGS] = "Error: not enough arguments for the flag.\n", // Ошибка: недостаточно аргументов для флага.
        [ERR_MEMORY_ALLOCATION] = "Error: tr.\n"
};

typedef enum kOpts {
    OPT_L,  // -l: подсчет длины строки
    OPT_R,  // -r: реверс строки
    OPT_C,  // -c: конкатенация четных строк в случайном порядке
    OPT_U,  // -u: преобразование нечетных символов в верхний регистр
    OPT_N,  // -n: сортировка строки по цифрам, буквам и символам
    OPT_INVALID
} kOpts;

ErrorCode GetOpts(int argc, char** argv, kOpts *option, unsigned int *seed);
ErrorCode GetStringLength(char* str, int* length);
ErrorCode ReverseString(char* str, char** reversed);
ErrorCode ConcatenateEvenStrings(int argc, char** argv, unsigned int seed, char** result);
ErrorCode UppercaseOddPositions(char* str, char** result);
ErrorCode SortStringByCategories(char* str, char** result);


#endif
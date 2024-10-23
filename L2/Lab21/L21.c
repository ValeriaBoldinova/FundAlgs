#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "L21.h"


// Функция парсинга аргументов
ErrorCode GetOpts(int argc, char** argv, kOpts *option, unsigned int *seed) {
    if (argc < 2 || argv[1][0] != '-' || strlen(argv[1]) != 2 || !isalpha(argv[1][1])) {
        return ERR_INVALID_ARG;
    }

    switch (argv[1][1]) {
        case 'l':
            if (argc != 3) {
                return (argc > 3) ? ERR_TOO_MANY_ARGS : ERR_TOO_FEW_ARGS;
            }
            *option = OPT_L;
            break;
        case 'r':
            if (argc != 3) {
                return (argc > 3) ? ERR_TOO_MANY_ARGS : ERR_TOO_FEW_ARGS;
            }
            *option = OPT_R;
            break;
        case 'c':
            if (argc < 4) {
                return ERR_INVALID_ARG;
            }
            *option = OPT_C;
            *seed = (unsigned int) atoi(argv[2]);  // Парсим seed
            if (*seed == 0 && strcmp(argv[2], "0") != 0) {
                return ERR_INVALID_NUM;
            }
            break;
        case 'u':
            if (argc != 3) {
                return (argc > 3) ? ERR_TOO_MANY_ARGS : ERR_TOO_FEW_ARGS;
            }
            *option = OPT_U;
            break;
        case 'n':
            if (argc != 3) {
                return (argc > 3) ? ERR_TOO_MANY_ARGS : ERR_TOO_FEW_ARGS;
            }
            *option = OPT_N;
            break;
        default:
            return ERR_INVALID_ARG;
    }

    return OK;
}

// Функция подсчета длины строки
ErrorCode GetStringLength(char* str, int* length) {
    if (str == NULL) {
        return ERR_NO_STRING;
    }
    *length = strlen(str);
    return OK;
}

// Функция реверсирования строки
ErrorCode ReverseString(char* str, char** reversed) {
    if (str == NULL) {
        return ERR_NO_STRING;
    }

    int len = strlen(str);
    *reversed = (char*) malloc((len + 1) * sizeof(char));
    if (*reversed == NULL) {
        return ERR_MEMORY_ALLOCATION;
    }

    for (int i = 0; i < len; i++) {
        (*reversed)[i] = str[len - i - 1];
    }
    (*reversed)[len] = '\0';

    return OK;
}

// Функция конкатенации четных строк
ErrorCode ConcatenateEvenStrings(int argc, char** argv, unsigned int seed, char** result) {
    if (argc < 5) {
        return ERR_NO_STRING;
    }
    srand(seed);

    int total_length = 0;
    int count = 0;
    for (int i = 3; i < argc; i += 2) {
        total_length += strlen(argv[i]);
        count++;
    }

    *result = (char*)malloc((total_length + 1) * sizeof(char));
    if (*result == NULL) {
        return ERR_MEMORY_ALLOCATION;
    }

    char** even_strings = (char**) malloc(count * sizeof(char*));
    if (even_strings == NULL) {
        free(*result);
        return ERR_MEMORY_ALLOCATION;
    }

    int index = 0;
    for (int i = 3; i < argc; i += 2) {
        even_strings[index++] = argv[i];
    }

    for (int i = count - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char* temp = even_strings[i];
        even_strings[i] = even_strings[j];
        even_strings[j] = temp;
    }

    (*result)[0] = '\0';
    for (int i = 0; i < count; i++) {
        strcat(*result, even_strings[i]);
    }

    free(even_strings);
    return OK;
}

// Функция преобразования нечетных символов в верхний регистр
ErrorCode UppercaseOddPositions(char* str, char** result) {
    if (str == NULL) {
        return ERR_NO_STRING;
    }

    int len = strlen(str);
    *result = (char*)malloc((len + 1) * sizeof(char));
    if (*result == NULL) {
        return ERR_MEMORY_ALLOCATION;
    }
    strcpy(*result, str);  // Копируем исходную строку

    for (int i = 1; i < len; i += 2) {
        (*result)[i] = toupper((*result)[i]);
    }

    return OK;
}

// Функция сортировки строки по категориям (цифры, буквы, остальные символы)
ErrorCode SortStringByCategories(char* str, char** result) {
    if (str == NULL) {
        return ERR_NO_STRING;
    }
    char* digits = (char*)malloc((strlen(str) + 1) * sizeof(char));
    char* letters= (char*)malloc((strlen(str) + 1) * sizeof(char));
    char* others= (char*)malloc((strlen(str) + 1) * sizeof(char));
    *result = (char*)malloc((strlen(str) + 1) * sizeof(char));
    if (digits == NULL || letters == NULL || others == NULL || *result == NULL) {
        free(digits);
        free(letters);
        free(others);
        free(*result);
        return ERR_MEMORY_ALLOCATION;
    }

    // Разделение строки на цифры, буквы и остальные символы
    for (int i = 0; str[i] != '\0'; i++) {
        if (isdigit(str[i])) {
            strncat(digits, &str[i], 1);
        } else if (isalpha(str[i])) {
            strncat(letters, &str[i], 1);
        } else {
            strncat(others, &str[i], 1);
        }
    }

    // Конкатенация в порядке: цифры, буквы, другие символы
    strcpy(*result, digits);
    strcat(*result, letters);
    strcat(*result, others);

    free(digits);
    free(letters);
    free(others);
    return OK;
}

void PrintError(ErrorCode err) {
    if (err != OK) {
        printf("%s", error_messages[err]);
    }
}

int main(int argc, char** argv) {
    kOpts opt = OPT_INVALID;
    unsigned int seed = 0;
    ErrorCode err;
    char* result = NULL;
    int length = 0;

    err = GetOpts(argc, argv, &opt, &seed);
    if (err != OK) {
        PrintError(err);
        return 1;
    }

    switch (opt) {
        case OPT_L:
            err = GetStringLength(argv[2], &length);
            if (err == OK) {
                printf("String length: %d\n", length);
            }
            break;
        case OPT_R:
            err = ReverseString(argv[2], &result);
            if (err == OK) {
                printf("Reversed string: %s\n", result);
                free(result);
            }
            break;
        case OPT_C:
            err = ConcatenateEvenStrings(argc, argv, seed, &result);
            if (err == OK) {
                printf("Concatenated result: %s\n", result);  // Результат конкатенации
                free(result);
            }
            break;
        case OPT_U:
            err = UppercaseOddPositions(argv[2], &result);
            if (err == OK) {
                printf("Transformed result: %s\n", result);  // Результат преобразования
                free(result);  // Освобождаем выделенную память
            }
            break;
        case OPT_N:
            err = SortStringByCategories(argv[2], &result);
            if (err == OK) {
                printf("Sorted result: %s\n", result);  // Результат сортировки
                free(result);  // Освобождаем выделенную память
            }
            break;
        default:
            printf("Error: unknown option.\n");  // Ошибка: неизвестная опция
            return 1;
    }

    if (err == ERR_NO_STRING) {
        printf("Error: There are not enough rows to perform the operation.\n");  // Ошибка: недостаточно строк для выполнения операции.
    }

    return 0;
}
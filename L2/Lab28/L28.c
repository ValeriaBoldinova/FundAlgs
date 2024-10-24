#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Преобразует символ в числовое значение
int charToValue(char c) {
    if (isdigit(c)) return c - '0';
    return toupper(c) - 'A' + 10;
}

// Преобразует числовое значение в символ
char valueToChar(int val) {
    if (val < 10) return val + '0';
    return val - 10 + 'A';
}

// Сложение в столбик двух чисел в заданной системе счисления
int addInColumn(char* num1, char* num2, int base, char** result) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int maxLen = len1 > len2 ? len1 : len2;
    int carry = 0, i, sum;

    *result = (char*)calloc(maxLen + 4, sizeof(char));
    if (!*result) {
        return 0;
    }
    (*result)[maxLen + 3] = '\0';

    // Сложение чисел в столбик
    for (i = 0; i < maxLen || carry; i++) {
        int digit1 = i < len1 ? charToValue(num1[len1 - 1 - i]) : 0;
        int digit2 = i < len2 ? charToValue(num2[len2 - 1 - i]) : 0;

        if (digit1 >= base || digit2 >= base) {
            free(*result);
            return 0;
        }

        sum = digit1 + digit2 + carry;
        carry = sum / base;
        (*result)[maxLen - i - 1] = valueToChar(sum % base);
    }

    int firstNonZero = 0;
    while ((*result)[firstNonZero] == '0' && (*result)[firstNonZero + 1] != '\0') {
        firstNonZero++;
    }

    if (firstNonZero > 0) {
        memmove(*result, *result + firstNonZero, strlen(*result) - firstNonZero + 1);
    }

    return 1;
}

char* sumNumbers(int base, int count, ...) {
    if (base < 2 || base > 36) {
        return NULL;
    }

    char* result = (char*)calloc(2, sizeof(char));
    if (!result) {
        return NULL;
    }
    strcpy(result, "0");

    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; i++) {
        char* number = va_arg(args, char*);

        char* temp =  (char*)calloc((strlen(result) + 1), sizeof(char));
        if (!temp) {
            free(result);
            va_end(args);
            return NULL;
        }
        strcpy(temp, result);

        char* new_result = NULL;
        if (!addInColumn(temp, number, base, &new_result)) {
            free(temp);
            free(result);
            va_end(args);
            return NULL;
        }

        free(result);
        result = new_result;
        free(temp);
    }

    va_end(args);

    return result;
}

int main() {
    printf("Base 2:\n");
    char* result_base2 = sumNumbers(2, 3, "0000000000", "0000101", "010");
    if (result_base2) {
        printf("Result: %s\n", result_base2);
        free(result_base2);
    } else {
        printf("Error occurred during summation.\n");
    }

    printf("\nBase 3:\n");
    char* result_base3 = sumNumbers(3, 3, "000000000100002222222222222000000000000000000000002222222220000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000002222222222220000000000000000000000000000000000000000000000000000000000000000000000000000000000000", "0000101", "010");
    if (result_base3) {
        printf("Result: %s\n", result_base3);
        free(result_base3);
    } else {
        printf("Error occurred during summation.\n");
    }

    printf("\nBase 16:\n");
    char* result_base16 = sumNumbers(16, 4, "A", "1F", "F", "234");
    if (result_base16) {
        printf("Result: %s\n", result_base16);
        free(result_base16);
    } else {
        printf("Error occurred during summation.\n");
    }

    printf("\nBase 8:\n");
    char* result_base8 = sumNumbers(8, 3, "10", "7", "3");
    if (result_base8) {
        printf("Result: %s\n", result_base8);
        free(result_base8);
    } else {
        printf("Error occurred during summation.\n");
    }

    printf("\nBase 4:\n");
    char* result_base4 = sumNumbers(4, 7, "10", "0", "3", "232", "1233", "13212", "12322112312312");
    if (result_base4) {
        printf("Result: %s\n", result_base4);
        free(result_base4);
    } else {
        printf("Error occurred during summation.\n");
    }

    printf("\nBase 10:\n");
    char* result_base10 = sumNumbers(10, 1, "10");
    if (result_base8) {
        printf("Result: %s\n", result_base10);
        free(result_base10);
    } else {
        printf("Error occurred during summation.\n");
    }

    printf("\nBase 37:\n");
    char* result_base37 = sumNumbers(37, 1, "1230");
    if (result_base37) {
        printf("Result: %s\n", result_base37);
        free(result_base37); // Освобождаем память
    } else {
        printf("Error occurred during summation.\n");
    }

    printf("\nBase 30:\n");
    char* result_base30 = sumNumbers(30, 1, "1230Z");
    if (result_base30) {
        printf("Result: %s\n", result_base30);
        free(result_base30);
    } else {
        printf("Error occurred during summation.\n");
    }
    return 0;
}



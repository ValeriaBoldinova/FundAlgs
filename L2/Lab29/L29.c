#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <stdbool.h>
#include "L29.h"
#define MIN_NUM 0.0000000001


// Функция для вычисления наибольшего общего делителя (НОД)
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

bool isDecimalTooLong(double number, double threshold) {
    // Проверяем, если длина десятичной части числа больше длины порога
    int threshold_digits = 0;
    while (threshold < 1) {
        threshold *= 10;
        threshold_digits++;
    }

    int number_digits = 0;
    while (fmod(number, 1.0) != 0.0) {
        number *= 10;
        number_digits++;
    }

    return number_digits > threshold_digits;
}

// Функция для проверки, имеет ли дробь конечное представление в заданной системе счисления
ErrorCode hasFiniteRepresentationInBase(double number, int base) {
    if (number <= 0.0 || number >= 1.0) {
        return OUT_OF_RANGE;
    }
    if (isDecimalTooLong(number, MIN_NUM)) {
        return BELOW_MIN_THRESHOLD;
    }

    // Преобразуем число в дробь (числитель и знаменатель)
    int den = 1;
    while (fmod(number, 1.0) != 0.0) {
        number *= 10;
        den *= 10;
    }
    int numerator = (int)number;

    // Упрощаем дробь
    int divisor = gcd(numerator, den);
    numerator /= divisor;
    den /= divisor;

    // Проверяем, является ли знаменатель произведением только простых множителей основания
    for (int i = 2; i <= base; i++) {
        if (base % i == 0) {
            while (den % i == 0) {
                den /= i;
            }
        }
    }

    return (den == 1) ? FINITE_REPRESENTATION : INFINITE_REPRESENTATION;
}

// Функция для проверки конечного представления для переменного числа аргументов
void checkFiniteRepresentationInBase(int base, int count, ...) {
    if (base < 2 || base > 36) {
        printf("%s\n", error_messages[BASE_TOO_LOW]);
        return;
    }
    if (count == 0) {
        printf("%s\n", error_messages[NO_NUMBERS_PROVIDED]);
        return;
    }


    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; i++) {
        double num = va_arg(args, double);
        ErrorCode result = hasFiniteRepresentationInBase(num, base);

        // Выводим сообщение на основе кода ошибки
        if (result == INFINITE_REPRESENTATION) {
            printf("%s: %.10f\n", error_messages[result], num); // Вывод: Число не имеет конечного представления в указанной системе счисления.
        } else {
            printf("%s: %.10f\n", error_messages[result], num);
        }
    }

    va_end(args);
}

// Демонстрация работы функции
int main() {
    printf("Checking numbers in base 2:\n"); // Проверка чисел в системе счисления с основанием 2
    checkFiniteRepresentationInBase(2, 5, 0.25, 0.5, 0.75, 0.1, 0.3);
    printf("\n");

    printf("Checking numbers in base 10:\n"); // Проверка чисел в системе счисления с основанием 10
    checkFiniteRepresentationInBase(10, 5, 0.1, 0.2, 0.3, 0.4, 0.5);
    printf("\n");

    printf("Checking numbers in base 8:\n"); // Проверка чисел в системе счисления с основанием 8
    checkFiniteRepresentationInBase(8, 5, 0.1, 0.2, 0.3, 0.4, 0.5);

    printf("Checking numbers in base 8:\n"); // Проверка чисел в системе счисления с основанием 8
    checkFiniteRepresentationInBase(8, 1, 0.00000000055);

    return 0;
}

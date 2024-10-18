#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "L11.h"


// Функция для проверки, является ли строка числом
int IsNumber(const char* str) {
    if (str[0] == '\0') {
        return 0;
    }
    // Если число отрицательное, игнорируем первый символ '-'
    int start = (str[0] == '-') ? 1 : 0; // турнарный оператор

    for (int i = start; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return 0; // Если символ не цифра, это не число
        }
    }
    return 1;
}

// h (вывод кратных чисел до 100)
void HandlerOptH(int number) {
    if (number > 100){
        printf("Нет чисел кратных %d в пределах 100\n", number);
    } else if (number <= 0){
        printf("Число должно быть положительным\n");
    } else{
        printf("Числа кратные %d в пределах 100:\n", number);
        for (int i = number; i <= 100; i += number){
            printf("%d ", i);
        }
    }
    printf("\n");
}


// p (проверка на простоту)
void HandlerOptP(int number){
    if (number == 1) {
        printf("%d не является простым и не является составным числом\n", number);
        return;
    }
    if (number <= 0) {
        printf("Введите положительное число \n");
        return;
    }
    int is_prime = 1;
    for (int i = 2; i <= sqrt(number); i++) {
        if (number % i == 0) {
            is_prime = 0;
            break;
        }
    }

    if (is_prime){
        printf("%d является простым числом\n", number);
    }
    else {
        printf("%d является составным числом\n", number);
    }
}

// s (разделение на цифры в 16-ричной системе)
void HandlerOptS(int number) {
    if (number < 0) {
        printf("Число должно быть положительным\n");
        return;
    }
    printf("Цифры числа %d в 16-ричной системе:\n", number);


    char hex[100];
    int index = 0;
    if (number == 0) {
        printf("0 \n");
        return;
    }

    // Преобразуем число в 16-ричную систему
    while (number > 0) {
        int digit = number % 16;
        hex[index++] = (digit < 10) ? '0' + digit : 'A' + (digit - 10);
        number /= 16;
    }

    // Выводим цифры в обратном порядке
    for (int i = index - 1; i >= 0; i--) {
        printf("%c ", hex[i]);
    }
    printf("\n");
}

// e (таблица степеней от 1 до x)
void HandlerOptE(int number) {
    if (number > 10) {
        printf("Ошибка: Число x должно быть не больше 10 для этого флага\n");
        return;
    }
    if (number <= 0) {
        printf("Число должно быть положительным\n");
        return;
    }


    printf("Таблица степеней для оснований от 1 до 10 (степени от 1 до %d):\n\n", number);

    // Первая строка с заголовками (основ/степ)
    printf(" Основ/Степ |");
    int width = 2;
    for (int exp = 1; exp <= number; exp++) {
        int col_width = (exp == 9) ? 10 : (exp == 10) ? 14 : width;  // Предпоследний столбец на 10 символов, последний на 14
        printf(" %-*d |", col_width, exp);  // Выравнивание по ширине, начиная с 2
        width++;
    }
    printf("\n");

    // Разделительная строка
    printf("------------");
    printf("|");
    width = 2;
    for (int exp = 1; exp <= number; exp++) {
        int col_width = (exp == 9) ? 12 : (exp == 10) ? 16 : width + 2;  // Ширина разделительной строки
        for (int i = 0; i < col_width; i++) printf("-");
        printf("|");
        width++;
    }
    printf("\n");

    // Строки с основаниями и результатами возведения в степени
    for (int base = 1; base <= 10; base++) {
        printf(" %10d |", base);  // Выводим основание с выравниванием
        width = 2;
        for (int exp = 1; exp <= number; exp++) {
            int col_width = (exp == 9) ? 10 : (exp == 10) ? 14 : width;
            long result = (long)pow(base, exp); // Результат возведения в степень
            printf(" %-*ld |", col_width, result);
            width++;
        }
        printf("\n");


        // Разделительная строка между строками таблицы
        printf("------------");
        printf("|");
        width = 2;
        for (int exp = 1; exp <= number; exp++) {
            int col_width = (exp == 9) ? 12 : (exp == 10) ? 16 : width + 2; // Ширина разделительной строки
            for (int i = 0; i < col_width; i++) printf("-");
            printf("|");
            width++;
        }
        printf("\n");
    }
}

// a (сумма чисел от 1 до x)
void HandlerOptA(int number) {
    int sum = 0;
    if (number <= 0) {
        printf("Число должно быть положительным\n");
        return;
    }
    sum = (1 + number) * number / 2;
    printf("Сумма чисел от 1 до %d: %d\n", number, sum);
}

// f (вычисление факториала)
void HandlerOptF(int number) {
    if (number > 22){
        printf("Введите число меньше \n");
        return;
    }
    if (number < 0) {
        printf("Факториал определен только для неотрицательных чисел\n");
        return;
    }
    unsigned long long fact = 1;
    for (int i = 1; i <= number; i++) {
        fact *= i;
    }
    printf("Факториал числа %d: %llu\n", number, fact);
}



// Функция для парсинга аргументов командной строки
int GetOpts(int argc, char** argv, kOpts* opt, int* number){
    if (argc != 3) {
        return 1; // Неправильное количество аргументов
    }
    if (!IsNumber(argv[1])) {
        return 2; // Первый аргумент не является числом
    }
    *number = atoi(argv[1]); // Преобразуем 1 аргумент в число

    // Получаем флаг и определяем соответствующую опцию
    if (argv[2][0] == '/' || argv[2][0] == '-') {
        switch (argv[2][1]) {
            case 'h':
                *opt = OPT_H;
                break;
            case 'p':
                *opt = OPT_P;
                break;
            case 's':
                *opt = OPT_S;
                break;
            case 'e':
                *opt = OPT_E;
                break;
            case 'a':
                *opt = OPT_A;
                break;
            case 'f':
                *opt = OPT_F;
                break;
            default:
                return 3; // Неизвестный флаг
        }
    } else {
        return 4; // Флаг должен начинаться с / или ?
    }
    return 0; // Успешный парсинг
}

// Основная функция
int main(int argc, char** argv) {
    kOpts opt = OPT_UNKNOWN;
    int procceed_number = 0;

    void (*handlers[6])(int) = {
            HandlerOptH,
            HandlerOptP,
            HandlerOptS,
            HandlerOptE,
            HandlerOptA,
            HandlerOptF
    };

    if (GetOpts(argc, argv, &opt, &procceed_number)){
        printf("Некорректный флаг или формат числа. (Первый аргумент должен являться числом)\n");
        return 1;
    }

    if (procceed_number > 999999999){
        printf("Введите число меньше 999999999\n");
        return 2;
    }

    handlers[opt](procceed_number);
    return 0;

}

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

#define SUCCESS 0
#define INPUT_ERROR 1
#define MEMORY_ERROR 2

#define FREE_AND_NULL(ptr) { free(ptr); ptr = NULL; }

double calc_poly(double a, double *coefs, size_t n) {
    double res = 0;
    double pow = 1;
    for (size_t i = 0; i <= n; ++i) {
        res += pow * coefs[i];
        pow *= a;
    }
    return res;
}

void proizv(double **src, int *cnt) {
    if (*cnt == 0) {
        return;
    }

    for (int i = 0; i < (*cnt) - 1; ++i) {
        (*src)[i] = (*src)[i + 1] * (i + 1);
    }
    (*cnt) = (*cnt) - 1;
}

int magic(double **res, double eps, double a, size_t n, ...) {
    if (eps < 0) {  // Проверка, чтобы eps не было отрицательным
        FREE_AND_NULL(*res);
        return INPUT_ERROR;
    }

    // Выделение памяти под результирующий массив коэффициентов
    double *real = (double *)realloc(*res, sizeof(double) * (n + 1));
    if (real == NULL) {
        FREE_AND_NULL(*res);
        return MEMORY_ERROR;
    }
    *res = real;

    // Выделение памяти под входной массив коэффициентов многочлена
    double *input = (double *)malloc(sizeof(double) * (n + 1));
    if (input == NULL) {
        FREE_AND_NULL(*res);
        return MEMORY_ERROR;
    }

    // Считывание коэффициентов многочлена из аргументов
    va_list args;
    va_start(args, n);
    for (size_t i = 0; i <= n; i++) {
        double cur = va_arg(args, double);
        input[i] = cur;
    }
    va_end(args);

    // Если a == 0, просто возвращаем исходные коэффициенты
    if (a == 0) {
        for (size_t i = 0; i <= n; i++) {
            (*res)[i] = input[i];
        }
        FREE_AND_NULL(input);
        return SUCCESS;
    }

    // Основной цикл переразложения многочлена
    double mult = 1;
    int pow = (int)n;

    for (size_t i = 0; i <= n; i++) {
        // Вычисление текущего коэффициента g_i
        (*res)[i] = calc_poly(a, input, pow);

        // Деление на факториал для корректного коэффициента
        if (i > 1) {
            mult *= i;
            (*res)[i] /= mult;
        }

        pow--;
        for (int j = 0; j <= pow; ++j) {
            input[j] = input[j + 1] * (j + 1);
        }
    }

    FREE_AND_NULL(input);
    return SUCCESS;
}

int main() {
    double *result = NULL; // Результирующий массив
    double a = 2.0; // Точка переразложения
    double eps = 0.0001; // Точность
    size_t n = 3; // Степень многочлена

    // Пример: f(x) = 1 + 2x + 3x^2 + 4x^3
    if (magic(&result, eps, a, n, 1.0, 2.0, 3.0, 4.0) == SUCCESS) {
        printf("Resulting coefficients: \n"); // Результирующие коэффициенты:
        for (size_t i = 0; i <= n; i++) {
            printf("g[%zu] = %f\n", i, result[i]);
        }
    } else {
        printf("An error occurred during polynomial re-expansion\n"); // Произошла ошибка при переразложении многочлена
    }

    FREE_AND_NULL(result);
    return 0;
}

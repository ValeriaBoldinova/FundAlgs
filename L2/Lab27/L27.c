#include <stdio.h>
#include <math.h>
#define STEP 0.1  // Шаг для поиска интервалов
#define RANGE_MIN -10.0  // Минимальное значение диапазона
#define RANGE_MAX 10.0   // Максимальное значение диапазона

double find_intervals(double (*fun)(double), double start, double end, double step) {
    for (double i = start; i < end; i += step) {
        if (fun(i) * fun(i + step) < 0) {
            return i;
        }
    }
    return NAN;
}

int check_epsilon(double epsilon) {
    return (epsilon > 0 && epsilon < 1);
}

double dichotomy(double a, double b, double eps, double (*fun)(double)) {
    if (fun(a) * fun(b) >= 0) {
        return NAN;
    }

    if (!check_epsilon(eps)) {
        return NAN;
    }

    double mid;
    double fun_point_c;

    while ((b - a) >= eps) {
        mid = (a + b) / 2.0;
        fun_point_c = fun(mid);

        if (fun_point_c == 0.0) {
            return mid;
        } else if (fun(a) * fun_point_c < 0.0) {
            b = mid;
        } else {
            a = mid;
        }
    }

    return (a + b) / 2;
}

double fun1(double x) {
    return x * x - 4;
}

double fun2(double x) {
    return cos(x) - x; // 0.739085
}

double fun3(double x) {
    return x * x * x - x - 6; // 6
}

double fun4(double x) {
    return x * x * x - 6 * x * x + 11 * x - 6; // 1, 2, 3
}

int main() {
    double start = RANGE_MIN;
    double end = RANGE_MAX;
    double step = STEP;
    double eps = 1e-6;

    double a = find_intervals(fun1, start, end, step);
    if (!isnan(a)) {
        double res = dichotomy(a, a + step, eps, fun1);
        if (!isnan(res)) {
            printf("The root of equation x^2 - 4 = 0 is x = %.6f\n", res); // Корнем уравнения x^2 - 4 = 0 является x = ...
        } else {
            printf("Invalid epsilon. 0 < E < 1.\n"); // Неверный эпсилон. 0 < E < 1
        }
    } else {
        printf("Interval for equation x^2 - 4 = 0 not found.\n"); // Интервал для уравнения x^2 - 4 = 0 не найден
    }

    a = find_intervals(fun2, start, end, step);
    if (!isnan(a)) {
        double res = dichotomy(a, a + step, eps, fun2);
        if (!isnan(res)) {
            printf("The root of equation cos(x) - x = 0 is x = %.6f\n", res); // Корнем уравнения cos(x) - x = 0 является...
        } else {
            printf("Invalid epsilon. 0 < E < 1.\n"); // Неверный эпсилон. 0 < E < 1
        }
    } else {
        printf("Interval for equation cos(x) - x = 0 not found.\n"); // Интервал для уравнения cos(x) - x = 0 не найден
    }

    a = find_intervals(fun3, start, end, step);
    if (!isnan(a)) {
        double res = dichotomy(a, a + step, eps, fun3);
        if (!isnan(res)) {
            printf("The root of equation x^3 - x - 6 = 0 is x = %.6f\n", res); // Корнем уравнения x^3 - x - 6 = 0 является...
        } else {
            printf("Invalid epsilon. 0 < E < 1.\n"); // Неверный эпсилон. 0 < E < 1
        }
    } else {
        printf("Interval for equation x^3 - x - 6 = 0 not found.\n"); // Интервал для уравнения x^3 - x - 6 = 0 не найден
    }

    a = find_intervals(fun4, start, end, step);
    if (!isnan(a)) {
        double res = dichotomy(a, a + step, eps, fun4);
        if (!isnan(res)) {
            printf("The root of equation x^3 - 6x^2 + 11x - 6 = 0 is x = %.6f\n", res); // Корнем уравнения x^3 - 6x^2 + 11x - 6 является...
        } else {
            printf("Invalid epsilon. 0 < E < 1.\n"); // Неверный эпсилон. 0 < E < 1
        }
    } else {
        printf("Interval for equation x^3 - 6x^2 + 11x - 6 = 0 not found.\n"); // Интервал для уравнения x^3 - 6x^2 + 11x - 6 не найден
    }
    return 0;
}
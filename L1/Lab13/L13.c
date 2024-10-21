#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>
#include "L13.h"

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))

int main(int argc, char *argv[]) {
    double eps, a, b, c;
    long int num1, num2;
    int f = 0;
    double real1, imag1, real2, imag2;

    switch (valid(argc, argv, &eps, &a, &b, &c, &num1, &num2)) {
        case OK:
            switch (argv[1][1]) {
                case 'q': {
                    Coefficients seen[6];  // Для хранения уже обработанных перестановок

                    int seen_count = 0;
                    double combinations[6][3] = {
                            {a, b, c}, {a, c, b}, {b, a, c},
                            {b, c, a}, {c, a, b}, {c, b, a}
                    };

                    for (int i = 0; i < 6; ++i) {
                        double curr_a = combinations[i][0];
                        double curr_b = combinations[i][1];
                        double curr_c = combinations[i][2];

                        if (!is_duplicate(seen, seen_count, curr_a, curr_b, curr_c)) {
                            seen[seen_count++] = (Coefficients){curr_a, curr_b, curr_c};  // Сохраняем уникальную комбинацию
                            int mistake = solve_quadratic_equation(eps, curr_a, curr_b, curr_c,
                                                                   &real1, &imag1, &real2, &imag2);
                            print_res(mistake, real1, imag1, real2, imag2, curr_a, curr_b, curr_c);
                        }
                    }
                    break;
                }
                case 'm': {
                    if (num2 == 0) {
                        printf("Cannot divide by 0\n"); // Нельзя делить на 0
                        break;
                    }
                    multiples(num1, num2, &f);
                    if (f == 0) {
                        printf("The first number is not a multiple of the second\n");
                    } else {
                        printf("The first number is a multiple of the second\n");
                    }
                    break;
                }
                case 't': {
                    if (is_right_triangle(eps, a, b, c, &f) == NEGATIVE_SIDE) {
                        printf("The sides of the triangle must be greater than 0\n");
                    } else {
                        if (f == 0) {
                            printf("It is not a right triangle\n");
                        } else {
                            printf("A straight triangle\n");
                        }
                    }
                    break;
                }
                default:
                    printf("Invalid flag\n");
                    break;
            }
            break;

        case NOT_NUM_L_INT:
            printf("The argument is not a decimal number\n");
            break;
        case NOT_NUM:
            printf("The argument is not a number\n");
            break;
        case OVERFLOW_L_INT:
            printf("Overflow of the long int type\n");
            break;
        case OVERFLOW_DUB:
            printf("Double overflow\n");
            break;
        case NOT_NUM_LOOSE_MEAN:
            printf("The argument is not a number or there has been a loss of significance\n");
            break;
        case WRONG_FLAG:
            printf("Invalid flag\n");
            break;
        case CNT_ARGUMENTS:
            printf("Incorrect number of arguments\n");
            break;
        case WRONG_EPS_VALUE:
            printf("eps must be a positive number\n");
            break;
    }

    return 0;
}

// Функция для печати результатов
// Функция для печати результатов
void print_res(int mistake, double real1, double imag1, double real2, double imag2, double a, double b, double c) {
    printf("%lfx^2 + %lfx + %lf = 0\t", a, b, c);

    if (mistake == OK) {
        if (fabs(imag1) < DBL_EPSILON && fabs(imag2) < DBL_EPSILON) {
            // Действительные корни
            printf("%lf, %lf\n", real1, real2);
        } else {
            // Комплексные корни
            printf("%lf %c %lfi, %lf %c %lfi\n",
                   real1, (imag1 < 0) ? '-' : '+', fabs(imag1),
                   real2, (imag2 < 0) ? '-' : '+', fabs(imag2));
        }
    }
    if (mistake == ANY) {
        printf("x -- any\n"); // Любое значение
    }
    if (mistake == ONE_SOLVE) {
        printf("%lf\n", real1); // Один корень
    }
    if (mistake == NOT_SOLVE) {
        printf("The equation has no valid solution\n"); // Уравнение не имеет действительного решения
    }
    if (mistake == NOT_QUADRATIC_EQUATION) {
        printf("%lf (is not a quadratic equation)\n", real1); // Не является квадратным уравнением
    }
}


// Проверка уникальности перестановки
int is_duplicate(Coefficients seen[], int size, double a, double b, double c) {
    for (int i = 0; i < size; ++i) {
        if (fabs(seen[i].a - a) < DBL_EPSILON && fabs(seen[i].b - b) < DBL_EPSILON && fabs(seen[i].c - c) < DBL_EPSILON) {
            return 1;
        }
    }
    return 0;
}


// Решение квадратного уравнения с поддержкой комплексных корней
int solve_quadratic_equation(double eps, double a, double b, double c,
                             double *real1, double *imag1,
                             double *real2, double *imag2) {
    if ((fabs(a) > eps) && (fabs(b) < eps) && (fabs(c) < eps)) {
        *real1 = 0;
        *imag1 = 0;
        return ONE_SOLVE;
    }
    if ((fabs(a) < eps) && (fabs(b) < eps) && (fabs(c) < eps)) {
        return ANY;
    }
    if (fabs(a) < eps) {
        if ((fabs(b) < eps) && (fabs(c) < eps)) {
            return NOT_SOLVE;
        }
        *real1 = -c / b;
        *imag1 = 0; // Мнимая часть отсутствует
        return NOT_QUADRATIC_EQUATION;
    }

    double d = b * b - 4 * a * c;
    if (d < -eps) {
        // Комплексные корни
        *real1 = *real2 = -b / (2 * a);
        *imag1 = sqrt(-d) / (2 * a);
        *imag2 = -sqrt(-d) / (2 * a);
        return OK;
    } else if (fabs(d) < eps) {
        *real1 = -b / (2 * a); // Один корень
        *imag1 = 0;            // Мнимая часть отсутствует
        return ONE_SOLVE;
    } else {
        *real1 = (-b + sqrt(d)) / (2 * a);
        *imag1 = 0; // Мнимая часть отсутствует
        *real2 = (-b - sqrt(d)) / (2 * a);
        *imag2 = 0;
        return OK;
    }
}


// Проверка на кратность
int multiples(long int num1, long int num2, int *f) {
    *f = (abs(num1) % num2 == 0) ? 1 : 0;
    return OK;
}

// Проверка прямоугольного треугольника
int is_right_triangle(double eps, double a, double b, double c, int *f) {
    if ((fabs(a) < eps) || (fabs(b) < eps) || (fabs(c) < eps)) {
        return NEGATIVE_SIDE;
    }
    double max_side = max(max(a, b), c);
    double min_side = min(min(a, b), c);
    double sr_side = a + b + c - min_side - max_side;

    *f = (fabs(min_side * min_side + sr_side * sr_side - max_side * max_side) < eps) ? 1 : 0;
    return OK;
}

// Валидация аргументов
int valid(int argc, char *argv[], double *eps, double *a, double *b, double *c, long int *num_1, long int *num_2) {
    if (argc < 4) {
        return CNT_ARGUMENTS;
    }
    if (!((argv[1][0] == '-' || argv[1][0] == '/') && strstr(" q m t ", argv[1] + 1) && (strlen(argv[1]) == 2))) {
        return WRONG_FLAG;
    }
    enum err mistake = OK;
    if (argv[1][1] == 'q' || argv[1][1] == 't') {
        if (argc != 6) {
            return CNT_ARGUMENTS;
        }
        mistake = is_db_correct(argv[2], eps);
        if (mistake != OK) {
            return mistake;
        }
        if (*eps < 0) {
            return WRONG_EPS_VALUE;
        }
        mistake = is_db_correct(argv[3], a);
        if (mistake != OK) {
            return mistake;
        }
        mistake = is_db_correct(argv[4], b);
        if (mistake != OK) {
            return mistake;
        }
        mistake = is_db_correct(argv[5], c);
        if (mistake != OK) {
            return mistake;
        }
        return OK;
    }
    if (argv[1][1] == 'm') {
        if (argc != 4) {
            return CNT_ARGUMENTS;
        }
        mistake = is_li_correct(argv[2], num_1);
        if (mistake != OK) {
            return mistake;
        }
        mistake = is_li_correct(argv[3], num_2);
        if (mistake != OK) {
            return mistake;
        }
        return OK;
    }
    return WRONG_FLAG;
}

// Проверка правильности числа типа double
int is_db_correct(char *argv, double *a) {
    char *p_last;
    *a = strtod(argv, &p_last);
    if (p_last == argv || *p_last != '\0' || *a == HUGE_VAL || *a == -HUGE_VAL || fabs(*a) > DBL_MAX) {
        return NOT_NUM;
    }
    return OK;
}

// Проверка правильности числа типа long int
int is_li_correct(char *argv, long int *a) {
    char *p_last;
    *a = strtol(argv, &p_last, 10);
    if (p_last == argv || *p_last != '\0' || *a == LONG_MAX || *a == LONG_MIN) {
        return NOT_NUM_L_INT;
    }
    return OK;
}

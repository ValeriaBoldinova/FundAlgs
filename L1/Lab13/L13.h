#ifndef __kOpts_h__
#define __kOpts_h__
#include <stdlib.h>

enum err {
    OK, // успеш выполн
    NOT_NUM, // некорректный ввод
    WRONG_FLAG, // неверный флаг
    OVERFLOW_L_INT, // переполнения long int
    OVERFLOW_DUB, // переполнения double
    CNT_ARGUMENTS, // неверное кол-во арг
    WRONG_EPS_VALUE, // некорректный эпсилон
    ONE_SOLVE, // у ур-ния один корень
    NOT_SOLVE, //  не имеет действ-ных корней
    NOT_QUADRATIC_EQUATION, // коэф-т а=0
    ANY, // а=в=с=0
    NEGATIVE_SIDE, // если одна из сторон не положительная
    NOT_NUM_LOOSE_MEAN, // теряется точность
    NOT_NUM_L_INT // не верное целое число
};

typedef struct {
    double a;
    double b;
    double c;
} Coefficients;

int is_duplicate(Coefficients seen[], int size, double a, double b, double c);
int solve_quadratic_equation(double eps, double a, double b, double c,
                             double *real1, double *imag1,
                             double *real2, double *imag2);
void print_res(int mistake, double real1, double imag1, double real2, double imag2, double a, double b, double c);
int multiples(long int num1, long int num2, int *f);
int is_right_triangle(double eps, double a, double b, double c, int *f);
int is_db_correct(char *argv, double *a);
int is_li_correct(char *argv, long int *a);
int valid(int argc, char *argv[], double *eps, double *a, double *b, double *c, long int *num_1, long int *num_2);

#endif

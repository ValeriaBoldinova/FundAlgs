#ifndef __kOpts_h__
#define __kOpts_h__
#include <stdlib.h>

int str_to_double(char *str, double *number);
double integral_a(double x);
double integral_b(double x);
double integral_c(double x);
double integral_d(double x);
double integrate(double epsilon, double (*integrate_function)(double));
double rectangle_method(int number, double epsilon, double (*integrate_function)(double));

enum ERRORS{
    OK,
    INVALID_INPUT,
    PROBLEMS_WITH_EPS,
};

#endif

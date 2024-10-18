#ifndef __kOpts_h__
#define __kOpts_h__
#include <stdlib.h>

typedef enum kOpts {
    OPT_H,   // Флаг для вывода чисел, кратных x
    OPT_P,   // Флаг для проверки числа на простоту
    OPT_S,   // Флаг для разделения числа на цифры в 16-ричной системе
    OPT_E,   // Флаг для вывода таблицы степеней
    OPT_A,   // Флаг для вычисления суммы от 1 до x
    OPT_F,   // Флаг для вычисления факториала
    OPT_UNKNOWN // Неизвестный флаг
} kOpts;

int GetOpts(int argc, char** argv, kOpts* option, int* number);
int IsNumber(const char* str);
void HandlerOptH(int number);
void HandlerOptP(int number);
void HandlerOptS(int number);
void HandlerOptE(int number);
void HandlerOptA(int number);
void HandlerOptF(int number);

#endif

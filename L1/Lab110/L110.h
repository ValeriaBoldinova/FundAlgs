#ifndef __kOpts_h__
#define __kOpts_h__
#include <stdlib.h>

enum my_bool{FALSE, TRUE};

enum error_state{
    DONE,
    INVALID_INPUT,
    WRONG_PARAMETERS,
    WRONG_PARAMETERS_NUMBER,
    OVERFLOW,
    NULL_PTR,
    INVALID_MEMORY
};

enum my_bool convert_check(enum error_state condition);
enum error_state to_decimal_num(char* word, long int* res, int base);
void print_num_in_base(long int init_number, int base);

#endif
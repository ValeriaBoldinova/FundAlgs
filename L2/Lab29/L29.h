#ifndef ERRORS_H
#define ERRORS_H

typedef enum ErrorCode {
    SUCCESS,
    OUT_OF_RANGE,
    BASE_TOO_LOW,
    NO_NUMBERS_PROVIDED,
    BELOW_MIN_THRESHOLD,
    FINITE_REPRESENTATION,
    INFINITE_REPRESENTATION
} ErrorCode;

const char* error_messages[] = {
        "Success.",
        "Error: Number out of range (0, 1).", // Ошибка: число вне диапазона (0, 1)
        "Error: Base must be greater than or equal to 2.", // Ошибка: основание должно быть больше или равно 2.
        "Error: No numbers provided.", // Ошибка: не передано чисел.
        "Error: Number is below the minimum threshold.", // Ошибка: число меньше минимального порога (0.0000000001).
        "The number has a finite representation in the specified base.", // Число имеет конечное представление в указанной системе счисления.
        "The number does not have a finite representation in the specified base." // Число не имеет конечного представления в указанной системе счисления.
};

#endif
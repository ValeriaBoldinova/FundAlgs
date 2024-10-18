#include <ctype.h>
#include <stdio.h>
#include <limits.h>
#include <windows.h>

#define MAX_LEN 100

int IsValidNumber(const char* knum_str) {
    for (int i = 0; knum_str[i] != '\0'; i++) {
        int c = tolower(knum_str[i]);
        if (!isdigit(c) && (c < 'a' || c > 'z')) {
            return 0;
        }
    }
    return 1;
}

int FindMinBase(const char* knum_str) {
    int min_base = 2;
    for (int i = 0; knum_str[i] != '\0'; i++) {
        int c = tolower(knum_str[i]);
        if (isdigit(c)) {
            int digit = c - '0';
            if (digit + 1 > min_base) {
                min_base = digit + 1;
            }
        } else if (isalpha(c)) {
            int digit = c - 'a' + 10;
            if (digit + 1 > min_base) {
                min_base = digit + 1;
            }
        }
    }
    return min_base;
}

long long ConvertToDecimal(const char* knum_str, int base) {
    long long result = 0;
    for (int i = 0; knum_str[i] != '\0'; i++) {
        int c = tolower(knum_str[i]);
        if (isdigit(c)) {
            result = result * base + (c - '0');
        } else if (isalpha(c)) {
            result = result * base + (c - 'a' + 10);
        }
    }
    return result;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    FILE* input_file = fopen(argv[1], "r");
    if (input_file == NULL) {
        perror("Error opening input file");
        fclose(input_file);
        return 1;
    }

    FILE* output_file = fopen(argv[2], "w");
    if (output_file == NULL) {
        perror("Error opening output file");
        fclose(input_file);
        return 1;
    }
    char input_realpath[PATH_MAX];
    char output_realpath[PATH_MAX];

// Преобразуем оба пути в абсолютные
    if (!GetFullPathName(argv[1], MAX_PATH, input_realpath, NULL)) {
        printf("Error: not udalos' preobrazovat' put' %s an absolyutnyj.\n", argv[1]);
        return 1;
    }
    if (!GetFullPathName(argv[2], MAX_PATH, output_realpath, NULL)) {
        printf("Error: not udalos' preobrazovat' put' %s an absolyutnyj.\n", argv[2]);
        return 1;
    }
    if (strcmp(input_realpath, output_realpath) == 0) {
        printf("Error: input and output file not dolgny sovpadat'.\n");
        if (strchr(argv[1], 'n') == NULL) {
            free(argv[2]);
        }
        return 1; // Завершаем программу с ошибкой
    }

    char* num_str_without_zeros;
    char num_str[MAX_LEN];
    while (fscanf(input_file, "%s", num_str) != EOF) {
        int n_flag = 0;
        // Removing leading zeros.
        if (num_str[0] == '-') {
            n_flag = 1;
            num_str_without_zeros = &num_str[1];

        } else {
            num_str_without_zeros = num_str;
        }

        while (*num_str_without_zeros == '0' && *(num_str_without_zeros + 1) != '\0') {
            num_str_without_zeros++;
        }

        if (!IsValidNumber(num_str_without_zeros)) {
            fprintf(stderr, "Error: invalid character in number '%s'\n", num_str_without_zeros);
            continue;
        }

        int min_base = FindMinBase(num_str_without_zeros);

        long long decimal_value = ConvertToDecimal(num_str_without_zeros, min_base);

        if (n_flag) {
            fprintf(output_file, "-%s %d -%lld\n", num_str_without_zeros, min_base, decimal_value);
        } else {
            fprintf(output_file, "%s %d %lld\n", num_str_without_zeros, min_base, decimal_value);
        }
    }

    fclose(input_file);
    fclose(output_file);
    return 0;
}

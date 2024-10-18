#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <windows.h>
#include "L14.h"


// Исключить арабские цифры (-d)
void HandlerOptD(const char* input_path, const char* output_path) {
    FILE *inputFile = fopen(input_path, "r");
    if (!inputFile) {
        printf("Error: not udalos open file %s.\n", input_path);
        return;
    }
    FILE *outputFile = fopen(output_path, "w");
    if (!outputFile) {
        printf("Error: not udalos sozdat file for output %s.\n", output_path);
        fclose(inputFile);
        return;
    }

    int c;
    do {
        c = fgetc(inputFile);
        if (!isdigit(c)) {  // Пропускаем арабские цифры
            fputc(c, outputFile);
        }
    } while (c != EOF);

    fclose(inputFile);
    fclose(outputFile);
    printf("Numbers was deleted from file and result is saved in %s.\n", output_path);
}

// Подсчитать количество латинских букв (-i)
void HandlerOptI(const char* input_path, const char* output_path) {
    FILE *inputFile = fopen(input_path, "r");
    if (!inputFile) {
        printf("Error: not udalos open file %s.\n", input_path);
        return;
    }

    FILE *outputFile = fopen(output_path, "w");
    if (!outputFile) {
        printf("Error: not udalos sozdat file for output %s.\n", output_path);
        fclose(inputFile);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), inputFile)) {
        int latinCount = 0;
        for (int i = 0; line[i] != '\0'; i++) {
            if (isalpha(line[i])) {
                latinCount++;
            }
        }

        fprintf(outputFile, "Number of Latin letters: %d\n", latinCount);
    }

    fclose(inputFile);
    fclose(outputFile);
    printf("Podschet of Latin letters finish. Result saved in %s.\n", output_path);
}

// Подсчитать символы, отличные от латинских букв, цифр и пробелов (-s)
void HandlerOptS(const char* input_path, const char* output_path) {
    FILE *inputFile = fopen(input_path, "r");
    if (!inputFile) {
        printf("Error: not udalos open file %s.\n", input_path);
        return;
    }

    FILE *outputFile = fopen(output_path, "w");
    if (!outputFile) {
        printf("Error: not udalos sozdat file for output %s.\n", output_path);
        fclose(inputFile);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), inputFile)) {
        int specialCharCount = 0;

        for (int i = 0; line[i] != '\0'; i++) {
            if (!isalnum(line[i]) && !isspace(line[i])) {  // Не буквы, не цифры, не пробелы
                specialCharCount++;
            }
        }

        fprintf(outputFile, "Kolichestvo special symbols: %d\n", specialCharCount);
    }

    fclose(inputFile);
    fclose(outputFile);
    printf("Podschet special symbols finish. Result saved in %s.\n", output_path);
}



// Заменить символы, отличные от цифр, на их ASCII код в 16-ричной системе (-a)
void HandlerOptA(const char* input_path, const char* output_path) {
    FILE *inputFile = fopen(input_path, "r");
    if (!inputFile) {
        printf("Error: not udalos open file %s.\n", input_path);
        return;
    }

    FILE *outputFile = fopen(output_path, "w");
    if (!outputFile) {
        printf("Error: not udalos sozdat' file for output %s.\n", output_path);
        fclose(inputFile);
        return;
    }

    int c;
    while ((c = fgetc(inputFile)) != EOF) {
        if (!isdigit(c)) {  // Если не цифра, заменяем на ASCII-код
            fprintf(outputFile, "%X ", (unsigned char)c);  // Печатаем ASCII-код в 16-ричной системе
        } else {
            fputc(c, outputFile);  // Если цифра, просто записываем её в выходной файл
        }
    }

    fclose(inputFile);
    fclose(outputFile);
    printf("Replacing symbols with their ASCII-cod finish. Result saved in %s.\n", output_path);
}


// Функция для извлечения имени файла из пути
const char* GetFileName(const char* path) {
    // Ищем последний символ '/' или '\\' в пути
    const char* lastSlash = strrchr(path, '/');
    const char* lastBackslash = strrchr(path, '\\');

    // Возвращаем указатель на начало имени файла после последнего слэша
    if (lastSlash) {
        return lastSlash + 1;
    }
    if (lastBackslash) {
        return lastBackslash + 1;
    }
    return path;
}

// Функция для парсинга аргументов командной строки
int GetOpts(int argc, char** argv, kOpts* opt) {
    if (argv[1][0] == '/' || argv[1][0] == '-') {
        size_t key_len = strlen(argv[1]);
        if (key_len < 2 || key_len > 3) {
            printf("Error: line key must be 2 or 3 symbol. Input key: %s\n", argv[1]);
            return 3;
        }
        int hasN = strchr(argv[1], 'n') != NULL;

        switch (argv[1][strlen(argv[1]) - 1]) {
            case 'd':
                *opt = OPT_D;
                break;
            case 'i':
                *opt = OPT_I;
                break;
            case 's':
                *opt = OPT_S;
                break;
            case 'a':
                *opt = OPT_A;
                break;
            default:
                *opt = OPT_UNKNOWN;
        }

        if (hasN && argc != 4) {
            return 3;
        }
    } else {
        return 2;
    }

    return 0;
}

int main(int argc, char** argv) {
    if (argc < 3 || argc > 4) {
        printf("Error: false Kolichestvo of arguments. <flag> <input_file> [output_file]\n");
        return 1;
    }

    char *input_path = argv[2];
    char *output_path = NULL;
    kOpts opt = OPT_UNKNOWN;
    int opt_result = GetOpts(argc, argv, &opt);
    if (opt_result == 2) {
        printf("Error: flag must start with '/' or '-'.\n");
        return 1;
    } else if (opt_result == 3) {
        printf("Error: for flag with 'n' neobhodimo ukazat' output file.\n");
        return 1;
    }

    // Проверяем, содержит ли флаг "n", и назначаем путь к выходному файлу
    if (strchr(argv[1], 'n')) {
        output_path = argv[3];
    } else {
        const char* input_filename = GetFileName(input_path);
        output_path = (char *)malloc(strlen(input_filename) + 5); // +5 для "out_" и '\0'
        if (!output_path) {
            printf("Error vydeleniya pamyati for output_path.\n");
            return 1;
        }
        snprintf(output_path, strlen(input_filename) + 5, "out_%s", input_filename);
    }

    char input_realpath[PATH_MAX];
    char output_realpath[PATH_MAX];

    // Преобразуем оба пути в абсолютные
    if (!GetFullPathName(input_path, MAX_PATH, input_realpath, NULL)) {
        printf("Error: not udalos' preobrazovat' put' %s an absolyutnyj.\n", input_path);
        if (strchr(argv[1], 'n') == NULL) {
            free(output_path); // Освобождаем память, если путь был сгенерирован
        }
        return 1;
    }

    if (!GetFullPathName(output_path, MAX_PATH, output_realpath, NULL)) {
        printf("Error: not udalos' preobrazovat' put' %s an absolyutnyj.\n", output_path);
        if (strchr(argv[1], 'n') == NULL) {
            free(output_path); // Освобождаем память, если путь был сгенерирован
        }
        return 1;
    }

    // Проверяем, не совпадают ли абсолютные пути входного и выходного файлов
    if (strcmp(input_realpath, output_realpath) == 0) {
        printf("Error: input and output file not dolgny sovpadat'.\n");
        if (strchr(argv[1], 'n') == NULL) {
            free(output_path);
        }
        return 1; // Завершаем программу с ошибкой
    }

    void (*handlers[4])(const char*, const char*) = {
            HandlerOptD, // Для флага 'd'
            HandlerOptI, // Для флага 'i'
            HandlerOptS, // Для флага 's'
            HandlerOptA  // Для флага 'a'
    };

    if (opt != OPT_UNKNOWN) {
        handlers[opt](input_path, output_path); // Вызов функции из массива
    } else {
        printf("Error: unknown flag.\n");
        // Освобождаем память, если она была выделена
        if (strchr(argv[1], 'n') == NULL) {
            free(output_path);
        }
        return 5;
    }


    if (strchr(argv[1], 'n') == NULL) {
        free(output_path);
    }

    return 0;
}

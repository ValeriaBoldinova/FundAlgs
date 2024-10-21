#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

enum err {
    OK,
    FILE_NOT_OPEN,
    FEW_ARGUMENTS,
    TOO_MUCH_ARGUMENTS,
    WRONG_FLAG,
    FILES_SAME
};

int get_absolute_path(const char *input_path, char *output_realpath);
int check_unique_paths(int argc, char *argv[]);
void skip_white_space(FILE *file, char *c);
int merge_files(const char *file1, const char *file2, const char *file_out_path);
void write_to_base(int n, int base, FILE *file_out);
int change_words(const char *file_in_path, const char *file_out_path);
int valid(int argc, char *argv[]);


// Пропуск пробелов
void skip_white_space(FILE *file, char *c) {
    while ((*c == ' ') || (*c == '\t') || (*c == '\n') || (*c == '\r')) {
        *c = fgetc(file);
    }
}

int get_absolute_path(const char *input_path, char *output_realpath) {
    if (!GetFullPathName(input_path, MAX_PATH, output_realpath, NULL)) {
        printf("Error: не удалось преобразовать путь %s в абсолютный.\n", input_path);
        return FILES_SAME;
    }
    return OK;
}

// Функция для проверки, что пути всех файлов уникальны
int check_all_unique_paths(int argc, char *argv[]) {
    char (*realpath)[MAX_PATH] = malloc((argc - 2) * MAX_PATH); // Массив для хранения абсолютных путей
    if (!realpath) return FILES_SAME;

    for (int i = 2; i < argc; ++i) {
        if (get_absolute_path(argv[i], realpath[i - 2]) != OK) {
            free(realpath);
            return FILES_SAME;
        }
    }

    // Сравниваем все пути между собой, чтобы убедиться в их уникальности
    for (int i = 0; i < argc - 3; ++i) {
        for (int j = i + 1; j < argc - 2; ++j) {
            if (strcmp(realpath[i], realpath[j]) == 0) {
                free(realpath);
                return FILES_SAME;
            }
        }
    }
    free(realpath);
    return OK;
}

// Объединение файлов
int merge_files(const char *file1, const char *file2, const char *file_out_path) {
    FILE *file1_in;
    FILE *file2_in;
    FILE *file_out;

    if (fopen_s(&file1_in, file1, "r") != 0 ||
        fopen_s(&file2_in, file2, "r") != 0 ||
        fopen_s(&file_out, file_out_path, "w") != 0) {
        if (file1_in) fclose(file1_in);
        if (file2_in) fclose(file2_in);
        if (file_out) fclose(file_out);
        return FILE_NOT_OPEN;
    }

    char c1 = ' ', c2 = ' ';
    int file1_done = 0, file2_done = 0;

    skip_white_space(file1_in, &c1);
    skip_white_space(file2_in, &c2);

    while (!file1_done || !file2_done) {
        // Лексема из file1
        if (!file1_done) {
            while (c1 != EOF && c1 != ' ' && c1 != '\t' && c1 != '\n' && c1 != '\r') {
                fputc(c1, file_out);
                c1 = fgetc(file1_in);
            }
            skip_white_space(file1_in, &c1);
            if (c1 == EOF) file1_done = 1;
        }
        fputc(' ', file_out);

        // Лексема из file2
        if (!file2_done) {
            while (c2 != EOF && c2 != ' ' && c2 != '\t' && c2 != '\n' && c2 != '\r') {
                fputc(c2, file_out);
                c2 = fgetc(file2_in);
            }
            skip_white_space(file2_in, &c2);
            if (c2 == EOF) file2_done = 1;
        }
        if (!file1_done || !file2_done) fputc(' ', file_out);
    }

    fclose(file1_in);
    fclose(file2_in);
    fclose(file_out);

    return OK;
}

// Преобразование числа в нужную систему счисления
void write_to_base(int n, int base, FILE *file_out) {
    if (n == 0) return;
    write_to_base(n / base, base, file_out);
    fputc('0' + n % base, file_out);
}

// Преобразование лексем
int change_words(const char *file_in_path, const char *file_out_path) {
    FILE *file_in;
    FILE *file_out;

    if (fopen_s(&file_in, file_in_path, "r") != 0 ||
        fopen_s(&file_out, file_out_path, "w") != 0) {
        if (file_in) fclose(file_in);
        if (file_out) fclose(file_out);
        return FILE_NOT_OPEN;
    }


    char c = ' ';
    int word_count = 1;

    skip_white_space(file_in, &c);
    while (c != EOF) {
        // Лексема
        if (c != ' ' && c != '\t' && c != '\n' && c != '\r') {
            if (word_count % 10 == 0) {
                while (c != EOF && c != ' ' && c != '\t' && c != '\n' && c != '\r') {
                    if ((c >= 'A' && c <= 'Z')) c = c - 'A' + 'a';
                    write_to_base(c, 4, file_out); // В систему счисления с основанием 4
                    c = fgetc(file_in);
                }
            } else if (word_count % 2 == 0) { // Каждая 2-я лексема
                while (c != EOF && c != ' ' && c != '\t' && c != '\n' && c != '\r') {
                    if (c >= 'A' && c <= 'Z') c = c - 'A' + 'a'; // К нижнему регистру
                    fputc(c, file_out);
                    c = fgetc(file_in);
                }
            } else if (word_count % 5 == 0) { // Каждая 5-я лексема
                while (c != EOF && c != ' ' && c != '\t' && c != '\n' && c != '\r') {
                    write_to_base(c, 8, file_out);
                    c = fgetc(file_in);
                }
            } else { // Обычная лексема
                while (c != EOF && c != ' ' && c != '\t' && c != '\n' && c != '\r') {
                    fputc(c, file_out);
                    c = fgetc(file_in);
                }
            }
            word_count++;
        }
        // Пробел между лексемами
        fputc(' ', file_out);
        skip_white_space(file_in, &c);
    }

    fclose(file_in);
    fclose(file_out);

    return OK;
}

// Проверка аргументов
int valid(int argc, char *argv[]) {
    if (argc < 4) return FEW_ARGUMENTS;
    if (argc > 5) return TOO_MUCH_ARGUMENTS;
    if (!(strlen(argv[1]) == 2 && (argv[1][0] == '-' || argv[1][0] == '/') && (argv[1][1] == 'a' || argv[1][1] == 'r'))) return WRONG_FLAG;
    return OK;
}

int main(int argc, char *argv[]) {
    enum err mistake;

    switch (valid(argc, argv)) {
        case OK:
            mistake = check_all_unique_paths(argc, argv);
            if (mistake != OK) {
                printf("Error: пути файлов не должны совпадать.\n");
                break;
            }
            if (argv[1][1] == 'r') {
                if (argc != 5) {
                    printf("Not enough command line arguments have been entered\n"); // Введено неверное количество аргументов командной строки
                    break;
                }
                mistake = merge_files(argv[2], argv[3], argv[4]);
            } else if (argv[1][1] == 'a') {
                if (argc != 4) {
                    printf("Not enough command line arguments have been entered\n"); // Введено неверное количество аргументов командной строки

                    break;
                }
                mistake = change_words(argv[2], argv[3]);
            }

            if (mistake == OK)
                printf("The program finished its work successfully\n"); //Программа закончила работу успешно
            else
                printf("The file could not be opened or its name is incorrect\n"); // Файл не удалось открыть либо его название неверное
            break;

        case FILES_SAME:
            printf("Error: пути файлов не должны совпадать.\n");
            break;

        case FEW_ARGUMENTS:
            printf("Not enough command line arguments have been entered\n"); // Введено недостаточно аргументов командной строки
            break;


        case TOO_MUCH_ARGUMENTS:
            printf("Too many command line arguments have been entered\n"); // Введено слишком много аргументов командной строки
            break;

        case WRONG_FLAG:
            printf("The wrong flag was entered\n"); // Введён неверный флаг
            break;
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

/**
 * Программа 2: Динамическая загрузка библиотек во время выполнения
 * Использует dlopen/dlsym для загрузки функций
 */

// Указатели на функции из библиотек
typedef int (*PrimeCountFunc)(int, int);
typedef int (*GCFFunc)(int, int);

typedef struct {
    void *handle;
    PrimeCountFunc PrimeCount;
    GCFFunc GCF;
    const char *name;
} Library;

Library current_lib = {NULL, NULL, NULL, NULL};

int load_library(const char *lib_path, const char *lib_name) {
    // Закрываем предыдущую библиотеку, если она была загружена
    if (current_lib.handle != NULL) {
        dlclose(current_lib.handle);
        current_lib.handle = NULL;
        current_lib.PrimeCount = NULL;
        current_lib.GCF = NULL;
    }
    
    // Загружаем новую библиотеку
    current_lib.handle = dlopen(lib_path, RTLD_LAZY);
    if (!current_lib.handle) {
        fprintf(stderr, "Ошибка загрузки библиотеки %s: %s\n", lib_path, dlerror());
        return 0;
    }
    
    // Очищаем предыдущие ошибки
    dlerror();
    
    // Загружаем функцию PrimeCount
    current_lib.PrimeCount = (PrimeCountFunc)dlsym(current_lib.handle, "PrimeCount");
    char *error = dlerror();
    if (error != NULL) {
        fprintf(stderr, "Ошибка загрузки функции PrimeCount: %s\n", error);
        dlclose(current_lib.handle);
        current_lib.handle = NULL;
        return 0;
    }
    
    // Загружаем функцию GCF
    current_lib.GCF = (GCFFunc)dlsym(current_lib.handle, "GCF");
    error = dlerror();
    if (error != NULL) {
        fprintf(stderr, "Ошибка загрузки функции GCF: %s\n", error);
        dlclose(current_lib.handle);
        current_lib.handle = NULL;
        current_lib.PrimeCount = NULL;
        return 0;
    }
    
    current_lib.name = lib_name;
    printf("Библиотека %s успешно загружена.\n", lib_name);
    return 1;
}

void print_help() {
    printf("\n=== Программа 2: Динамическая загрузка библиотек ===\n");
    printf("Доступные команды:\n");
    printf("  0     - Переключить библиотеку (lib1 <-> lib2)\n");
    printf("  1 A B - Подсчет простых чисел на отрезке [A, B]\n");
    printf("  2 A B - Наибольший общий делитель чисел A и B\n");
    printf("  help  - Показать эту справку\n");
    printf("  exit  - Выход из программы\n\n");
}

int main() {
    char input[256];
    int command, A, B, result;
    int using_lib1 = 1; // По умолчанию используем lib1
    
    printf("=== Лабораторная работа №4 ===\n");
    printf("Программа 2: Динамическая загрузка библиотек\n\n");
    
    // Загружаем первую библиотеку
    if (!load_library("./libmath1.so", "lib1 (наивные алгоритмы)")) {
        fprintf(stderr, "Не удалось загрузить начальную библиотеку.\n");
        return 1;
    }
    
    print_help();
    
    while (1) {
        printf("> ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        
        // Убираем символ новой строки
        input[strcspn(input, "\n")] = 0;
        
        // Проверка на exit
        if (strcmp(input, "exit") == 0) {
            printf("Выход из программы.\n");
            break;
        }
        
        // Проверка на help
        if (strcmp(input, "help") == 0) {
            print_help();
            continue;
        }
        
        // Парсинг команды
        if (strcmp(input, "0") == 0) {
            // Переключение библиотеки
            if (using_lib1) {
                if (load_library("./libmath2.so", "lib2 (оптимизированные алгоритмы)")) {
                    using_lib1 = 0;
                }
            } else {
                if (load_library("./libmath1.so", "lib1 (наивные алгоритмы)")) {
                    using_lib1 = 1;
                }
            }
            printf("Текущая библиотека: %s\n", current_lib.name);
            continue;
        }
        
        int parsed = sscanf(input, "%d %d %d", &command, &A, &B);
        
        if (parsed < 3) {
            printf("Ошибка: Неверный формат команды. Введите 'help' для справки.\n");
            continue;
        }
        
        // Проверяем, что библиотека загружена
        if (current_lib.handle == NULL) {
            printf("Ошибка: Библиотека не загружена.\n");
            continue;
        }
        
        switch (command) {
            case 1:
                // Подсчет простых чисел
                if (A < 0 || B < 0) {
                    printf("Ошибка: A и B должны быть натуральными числами (>= 0).\n");
                    continue;
                }
                if (A > B) {
                    printf("Ошибка: A должно быть меньше или равно B.\n");
                    continue;
                }
                result = current_lib.PrimeCount(A, B);
                printf("Количество простых чисел на отрезке [%d, %d]: %d\n", A, B, result);
                printf("(Использована библиотека: %s)\n", current_lib.name);
                break;
                
            case 2:
                // Наибольший общий делитель
                if (A <= 0 || B <= 0) {
                    printf("Ошибка: A и B должны быть натуральными числами (> 0).\n");
                    continue;
                }
                result = current_lib.GCF(A, B);
                printf("Наибольший общий делитель чисел %d и %d: %d\n", A, B, result);
                printf("(Использована библиотека: %s)\n", current_lib.name);
                break;
                
            default:
                printf("Ошибка: Неизвестная команда %d. Доступны команды 0, 1 и 2.\n", command);
                break;
        }
    }
    
    // Освобождаем библиотеку перед выходом
    if (current_lib.handle != NULL) {
        dlclose(current_lib.handle);
    }
    
    return 0;
}

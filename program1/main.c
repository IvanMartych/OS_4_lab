#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/contracts.h"

/**
 * Программа 1: Использование динамической библиотеки через линковку на этапе компиляции
 * Библиотека подключается во время компиляции
 */

void print_help() {
    printf("\n=== Программа 1: Статическая линковка ===\n");
    printf("Доступные команды:\n");
    printf("  1 A B - Подсчет простых чисел на отрезке [A, B]\n");
    printf("  2 A B - Наибольший общий делитель чисел A и B\n");
    printf("  help  - Показать эту справку\n");
    printf("  exit  - Выход из программы\n\n");
}

int main() {
    char input[256];
    int command, A, B, result;
    
    printf("=== Лабораторная работа №4 ===\n");
    printf("Программа 1: Использование библиотеки через линковку\n");
    printf("Текущая библиотека: lib1 (наивные алгоритмы)\n");
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
        int parsed = sscanf(input, "%d %d %d", &command, &A, &B);
        
        if (parsed < 3) {
            printf("Ошибка: Неверный формат команды. Введите 'help' для справки.\n");
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
                result = PrimeCount(A, B);
                printf("Количество простых чисел на отрезке [%d, %d]: %d\n", A, B, result);
                break;
                
            case 2:
                // Наибольший общий делитель
                if (A <= 0 || B <= 0) {
                    printf("Ошибка: A и B должны быть натуральными числами (> 0).\n");
                    continue;
                }
                result = GCF(A, B);
                printf("Наибольший общий делитель чисел %d и %d: %d\n", A, B, result);
                break;
                
            default:
                printf("Ошибка: Неизвестная команда %d. Доступны команды 1 и 2.\n", command);
                break;
        }
    }
    
    return 0;
}

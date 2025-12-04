#include "../include/contracts.h"
#include <stdlib.h>
#include <string.h>

/**
 * Реализация 2: Решето Эратосфена
 * Подсчёт количества простых чисел на отрезке [A, B]
 */
int PrimeCount(int A, int B) {
    if (A < 0 || B < 0 || A > B) {
        return 0;
    }
    
    if (B < 2) {
        return 0;
    }
    
    // Создаем массив для решета
    int *is_prime = (int *)malloc((B + 1) * sizeof(int));
    if (is_prime == NULL) {
        return 0;
    }
    
    // Инициализация: все числа считаем простыми
    for (int i = 0; i <= B; i++) {
        is_prime[i] = 1;
    }
    is_prime[0] = is_prime[1] = 0;
    
    // Решето Эратосфена
    for (int i = 2; i * i <= B; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= B; j += i) {
                is_prime[j] = 0;
            }
        }
    }
    
    // Подсчет простых чисел на отрезке [A, B]
    int count = 0;
    for (int i = A; i <= B; i++) {
        if (is_prime[i]) {
            count++;
        }
    }
    
    free(is_prime);
    return count;
}

/**
 * Реализация 2: Наивный алгоритм поиска НОД
 * Пытаемся разделить числа на все числа, что меньше A и B
 */
int GCF(int A, int B) {
    if (A <= 0 || B <= 0) {
        return 0;
    }
    
    int min = (A < B) ? A : B;
    
    // Идем от минимального числа вниз
    for (int i = min; i >= 1; i--) {
        if (A % i == 0 && B % i == 0) {
            return i;
        }
    }
    
    return 1;
}

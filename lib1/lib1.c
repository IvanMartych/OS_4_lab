#include "../include/contracts.h"
#include <math.h>

/**
 * Реализация 1: Наивный алгоритм проверки простоты
 * Проверяет делимость числа на все предыдущие числа
 */
static int is_prime_naive(int n) {
    if (n <= 1) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;
    
    for (int i = 3; i < n; i += 2) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

/**
 * Подсчёт количества простых чисел на отрезке [A, B]
 * Реализация 1: Наивный алгоритм
 */
int PrimeCount(int A, int B) {
    if (A < 0 || B < 0 || A > B) {
        return 0;
    }
    
    int count = 0;
    for (int i = A; i <= B; i++) {
        if (is_prime_naive(i)) {
            count++;
        }
    }
    return count;
}

/**
 * Подсчёт наибольшего общего делителя
 * Реализация 1: Алгоритм Евклида
 */
int GCF(int A, int B) {
    if (A <= 0 || B <= 0) {
        return 0;
    }
    
    while (B != 0) {
        int temp = B;
        B = A % B;
        A = temp;
    }
    return A;
}

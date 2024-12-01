#include <stdio.h>

//осуществляет ввод массива a размера n
void inputArray(int *a, const size_t n) {
    for (size_t i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
}
//выводит массив a размера n
void printArray(int *a, const size_t n) {
    for (size_t i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
}

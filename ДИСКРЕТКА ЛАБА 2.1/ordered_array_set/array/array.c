#ifndef INC_ARRAY_C
#define INC_ARRAY_C

#include <stdio.h>
#include <limits.h>
#include <memory.h>
#include <malloc.h>
#include <assert.h>
#include "array.h"
#include "C:\Users\sovac\Desktop\ОП, преимущественно лабы\second_semester\libs\algorithms\math_basics\math_basics.c"


void swapVoid (void *a, void *b, int type_size) {
    void *temp = malloc(type_size);
    memcpy(temp, a, type_size);
    memcpy(a, b, type_size);
    memcpy(b, temp, type_size);
}

int getSmallSum(int *a, int n) {
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum;
}

long long getSum(int *a, int n) {
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum;
}

int getMax(int *a, int n) {
    int max = a[0];
    for (int i = 1; i < n; i++) {
        max = max2(a[i], max);
    }
    return max;
}

int getMin(int *a, int n) {
    int min = a[0];
    for (int i = 1; i < n; i++) {
        min = min2(a[i], min);
    }
    return min;
}

bool isUnique(int *a, int n) {
    bool result = 1;
    for (int i = 0; i < n-1 && result; i++) {
        for (int j = i + 1; j < n && result; j++) {
            if (a[i] == a[j]) {
                result = 0;
            }
        }
    }
    return result;
}

bool isNonDescendingSorted(int *a, int n) {
    bool result = 1;
    for (int i = 0; i < n-1; i++) {
        if (a[i] > a[i+1]) {
            result = 0;
            goto exit;
        }
    }
    exit:
    return result;
}

float getDistance(int *a, int n) {
    int sqr_distance = 0;
    for (int i = 0; i < n; i++) {
         sqr_distance += a[i] * a[i];
    }
    return sqrt(sqr_distance);
}

double getScalarProduct(int *a, int *b, int n) {
    double scalar_product = 0;
    for (int i = 0; i < n; i++) {
        scalar_product += a[i]*b[i];
    }
    return scalar_product;
}

double getVectorLength(int *a, int n) {
    return (double) getDistance(a, n);
}

double getCosine(int *a, int *b, int n) {
    return (getScalarProduct(a, b, n)) / (getVectorLength(a, n) * getVectorLength(b, n));
}

int countNUnique(long long *a, int n) {
    int unique_counter = n;
    for (int i = 0; i < n-1; i++) {
        if (a[i] == a[i+1]) {
            unique_counter -= 1;
        }
    }
    return unique_counter;
}

int countValues(const int *a, int n, int value) {
    int value_counter = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == value) {
            value_counter += 1;
        }
    }
    return value_counter;
}

void inputArray_(int *const a, const size_t n) {
    for (size_t i = 0; i < n; i++)
        scanf("%d", &a[i]);
}

void outputArray_(const int * const a, const size_t n) {
    for (size_t i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf ("\n");
}

void append_(int * const a, size_t * const n, const int value) {
    a [*n] = value;
    (*n)++;
}

void insert_(int *const a, size_t *const n, const size_t pos, const int value) {
    assert(pos < *n);
    if (*n != 0) {
        (*n) ++;
        for (size_t i = *n; i > pos; i--) {
            a[i] = a[i - 1];
        }
        a[pos] = value;
    } else {
        (*n)++;
        a[pos]= value;
    }
}

void deleteByPosSaveOrder_(int *a, size_t *n, const size_t pos) {
    for (size_t i = pos; i < *n - 1; i++)
        a[i]= a[i + 1];
    (*n)--;
}

void deleteByPosUnsaveOrder_(int *a, size_t *n, size_t pos) {
    a[pos]= a[*n-1];
    (*n)--;
}

size_t linearSearch_ (const int *a, const size_t n, int x) {
    for (size_t i = 0; i < n; i++)
        if (a[i] == x)
            return i;
    return n;
}

int any_(const int *a, size_t n, int (*predicate)(int)) {
    for (size_t i = 0; i < n; i++)
        if (predicate (a[i]))
            return 1;
    return 0;
}

int all_(const int *a, size_t n, int(*predicate)(int)) {
    for (size_t i = 0; i < n; i++)
        if (!predicate(a[i]))
            return 0;
     return 1;
}

int countIf_(const int * const a, const size_t n, int(*predicate)(int)) {
    int count = 0;
    for (size_t i = 0; i < n; i ++)
        count += predicate ( a[i ]);
    return count;
}

void deleteIf_(int *const a, size_t *const n, int (*deletePredicate)(int)) {
    size_t iRead = 0;
    while ( iRead < * n && ! deletePredicate ( a[iRead ]) )
        iRead ++;
    size_t iWrite = iRead;
    while ( iRead < * n ) {
        if (! deletePredicate ( a[iRead ]) ) {
            a[iWrite]= a[iRead];
            iWrite ++;
        }
        iRead ++;
    }
    *n = iWrite;
}

void forEach_(const int *source, int *dest, const size_t n, const int (*predicate)(int)) {
    for (size_t i = 0; i < n; i ++)
        dest[i]= predicate (source[i]);
}

size_t binarySearch_(const int *a, size_t n, int x) {
    int left = 0;
    int right = n - 1;
    while (left <= right) {
        int middle = (left + right) / 2;
        if (a[middle] < x)
            left = middle + 1;
        else if (a[middle] > x)
            right = middle - 1;
        else
            return middle;
        }
    return SIZE_MAX;
}

size_t binarySearchMoreOrEqual_ ( const int *a, size_t n, int x ) {
    if (a[0] >= x)
        return 0;
    size_t left = 0;
    size_t right = n;
    while (right - left > 1) {
        size_t middle = left + (right - left) / 2;
        if (a[middle] < x)
            left = middle;
        else
            right = middle;
    }
    return right;
}

#endif
#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include <assert.h>

#ifndef BIN_REL_DEF_IO
#define BIN_REL_DEF_IO

//Структура, отображающая отношение на множестве {1, ..., max_value};
//Какие упорядоченные пары присутствуют в этом отношении, показывает массив целых чисел values; целые числа в двоичной записи представляют собой строки матрицы, отображающей отношение
typedef struct {
    int max_value;
    int *values;
} bin_relation;

//Возвращает пустое отношение на множестве {1, ..., max_value}, проверяя при этом, что max_value не превышает 32 (количество двоичных разрядов в типе int)
bin_relation bin_relation_createEmpty(int max_value) {
    if (max_value > 32) {
        fprintf(stderr, "Too large power of set");
        exit(1);
    }
    int *values = (int*) malloc (max_value * sizeof(int));
    for (int i = 0; i < max_value; i++) {
        values[i] = 0;
    }
    return (bin_relation) {max_value, values};
}

//возвращает 1, если упорядоченная пара (x, y) входит в множество a, и 0 в противном случае
bool bin_relation_getValue(bin_relation a, int x, int y) {
    return (a.values[x-1] >> (y-1)) & 1;
}

//Меняет ячейку матрицы отношения a, соответствующую паре (x, y), на значение value
void bin_relation_changeValue(bin_relation *a, int x, int y, bool value) {
    if (value == 1) {
        a->values[x-1] |= 1 << (y-1);
    } else {
        a->values[x-1] &= ~(1 << (y-1));
    }
}

//Осуществляет ввод матрицы отношения по адресу a
void bin_relation_input(bin_relation *a) {
    for (int i = 1; i <= a->max_value; i++) {
        for (int j = 1; j <= a->max_value; j++) {
            int cur_value;
            scanf("%d", &cur_value);
            assert(cur_value == 1 || cur_value == 0);
            bin_relation_changeValue(a, i, j, cur_value);
        }
    }
}

//Осуществляет вывод матрицы отношения a
void bin_relation_matrixPrint(bin_relation a) {
    for (int i = 1; i <= a.max_value; i++) {
        for (int j = 1; j <= a.max_value; j++) {
            printf("%d ", bin_relation_getValue(a, i, j));
        }
        printf(" \n");
    }
}

//Осуществляет вывод упорядоченных пар, входящих в отношение a
void bin_relation_pairPrint(bin_relation a) {
    for (int i = 1; i <= a.max_value; i++) {
        bool are_pairs_for_cur_i = false;
        for (int j = 1; j <= a.max_value; j++) {
            if (bin_relation_getValue(a, i, j)) {
                are_pairs_for_cur_i = true;
                printf("(%d, %d); ", i, j);
            }
        }
        if (are_pairs_for_cur_i) {
            printf("\n");
        }
    }
}
#endif
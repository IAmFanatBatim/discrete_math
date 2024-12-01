#ifndef INC_MATRIX_H
#define INC_MATRIX_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    int **values; // элементы матрицы
    int nRows; // количество рядов
    int nCols; // количество столбцов
} matrix;

//размещает в динамической памяти и возвращает матрицу размером nRows на nCols
matrix getMemMatrix(int nRows, int nCols);

//возвращает матрицу размера nRows на nCols, построенную из элементов массива a
matrix createMatrixFromArray(const int *a, size_t nRows, size_t nCols);

#endif

#ifndef INC_MATRIX_C
#define INC_MATRIX_C
#include "matrix.h"
#include <malloc.h>

matrix getMemMatrix(int nRows, int nCols) {
    int **values = (int **) malloc(sizeof(int*) * nRows);
    for (int row_ind = 0; row_ind < nRows; row_ind++) {
        values[row_ind] = (int *) malloc(sizeof(int) * nCols);
    }
    return (matrix){values, nRows, nCols};
}

//возвращает матрицу размера nRows на nCols, построенную из элементов массива a
matrix createMatrixFromArray(const int *a, size_t nRows, size_t nCols) {
    matrix m = getMemMatrix(nRows, nCols);
    int k = 0;
    for (int row_ind = 0; row_ind < nRows; row_ind++) {
        for (int col_ind = 0; col_ind < nCols; col_ind++) {
            m.values[row_ind][col_ind] = a[k++];
        }
    }
    return m;
}

#endif
#include "matrix.h"
#include <malloc.h>
#include <stdio.h>
#include <assert.h>
#ifndef INC_MATRIX_C
#define INC_MATRIX_C

matrix getMemMatrix(int nRows, int nCols) {
    int **values = (int **) malloc(sizeof(int*) * nRows);
    for (int row_ind = 0; row_ind < nRows; row_ind++) {
        values[row_ind] = (int *) malloc(sizeof(int) * nCols);
    }
    return (matrix){values, nRows, nCols};
}

void inputMatrix(matrix *m) {
    for (int row_ind = 0; row_ind < m->nRows; row_ind++) {
        for (int col_ind = 0; col_ind < m->nCols; col_ind++) {
            scanf("%d", &(m->values[row_ind][col_ind]));
        }
    }
}

void outputMatrix(matrix m) {
    if (m.nRows != 0 && m.nCols != 0) {
        for (int row_ind = 0; row_ind < m.nRows; row_ind++) {
            printf("|");
            for (int col_ind = 0; col_ind < m.nCols; col_ind++) {
                printf("%d ", m.values[row_ind][col_ind]);
            }
            printf("\b|\n");
        }
    }
}

position getValuePos(matrix m, int value) {
    position pos = (position) {0, 0};
    for (int row_index = 0; row_index < m.nRows; row_index++) {
        for (int col_index = 0; col_index < m.nCols; col_index++) {
            if (m.values[row_index][col_index] == value) {
                pos.rowIndex = row_index;
                pos.colIndex = col_index;
                break;
            }
        }
    }
    return pos;
}

matrix mulMatrices(matrix m1, matrix m2) {
    assert(m1.nCols == m2.nRows);
    matrix result = getMemMatrix(m1.nRows, m2.nCols);
    for (int row_ind = 0; row_ind < result.nRows; row_ind++) {
        for (int col_ind = 0; col_ind < result.nCols; col_ind++) {
            result.values[row_ind][col_ind] = 0;
            for (int summand_ind = 0; summand_ind < m1.nRows; summand_ind++) {
                result.values[row_ind][col_ind] += m1.values[row_ind][summand_ind] * m2.values[summand_ind][col_ind];
            }
        }
    }
    return result;
}

matrix createMatrixFromArray(const int *values, size_t nRows, size_t nCols) {
    matrix m = getMemMatrix(nRows, nCols);
    int k = 0;
    for (int row_ind = 0; row_ind < nRows; row_ind++) {
        for (int col_ind = 0; col_ind < nCols; col_ind++) {
            m.values[row_ind][col_ind] = values[k++];
        }
    }
    return m;
}

#endif
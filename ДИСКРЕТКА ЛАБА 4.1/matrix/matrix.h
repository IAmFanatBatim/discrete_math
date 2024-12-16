#ifndef INC_MATRIX_H
#define INC_MATRIX_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    int **values; // элементы матрицы
    int nRows; // количество рядов
    int nCols; // количество столбцов
} matrix;
typedef struct {
    int rowIndex;
    int colIndex;
} position;

//размещает в динамической памяти и возвращает матрицу размером nRows на nCols
matrix getMemMatrix(int nRows, int nCols);
//осуществляет ввод матрицы и записывает данные по адресу m
void inputMatrix(matrix *m);
// выводит на экран матрицу m
void outputMatrix(matrix m);
//возвращает позицию последнего элемента со значением value, если идти по матрице сверху вниз и по ее строкам слева направо
position getValuePos(matrix m, int value);
//возвращает матрицу - произведение матриц m1 и m2
matrix mulMatrices(matrix m1, matrix m2);
//возвращает матрицу размера nRows на nCols, построенную из элементов массива a
matrix createMatrixFromArray(const int *values, size_t nRows, size_t nCols);

#endif
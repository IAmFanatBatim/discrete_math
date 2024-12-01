#include <stdio.h>
#include <stdlib.h>
//Функция для обмена двух элементов
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

//Функция для генерации всех перестановок массива
void permute(int *array, int start, int end, void (*callback) (int *array, int size)) {
    if (start == end) {
        callback(array, end + 1);
    } else {
        for (int i = start; i <= end; i++) {
            swap(array + start, array + i);
            permute(array, start + 1, end, callback);
            swap(array + start, array + i); // backtrack
        }
    }
}
// Функция для проверки, находятся ли нули в нижних позициях каждого столбца
int checkZeros(int **matrix, int n, int m) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] == 0) {
                return 0;
            }
        }
    }
    return 1;
}
void printMatrix(int **matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

//Функция для применения перестановки к строкам матрицы и проверки выполнения условия
void applyPermutationAndCheck(int *perm, int size) {
    extern int **matrix;
    extern int n, m;
    int **tempMatrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        tempMatrix[i] = matrix[perm[i]];
    }
    if (checkZeros(tempMatrix, n, m)) {
        printMatrix(tempMatrix, n, m);
    }
    free(tempMatrix);
}


int **matrix;
int n, m;
int main() {
    printf("Enter the number of rows and columns of the matrix:");
    scanf("%d %d", &n, &m);
    matrix = (int **) malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) { 
        matrix[i] = (int *) malloc(m * sizeof(int));
        for (int j = 0; j < m; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    int *perm = (int *) malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        perm[i] = i;
    }
    permute(perm, 0, n - 1, applyPermutationAndCheck);
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(perm);
    return 0;
}
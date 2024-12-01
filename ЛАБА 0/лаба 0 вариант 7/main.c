#include <stdio.h>
#include "C:\Users\sovac\Desktop\дискретная математика\ЛАБА 0\array_input_output\library.c"

int isArraysDisjoint(const int *a, const int a_len, const int *b, const int b_len) {
    int is_arrays_disjoint = 1;
    for (int a_ind = 0; a_ind < a_len; a_ind++) {
        for (int b_ind = 0; b_ind < b_len; b_ind++) {
            if (b[b_ind] == a[a_ind]) {
                is_arrays_disjoint = 0;
                break;
            }
        }
    }
    return is_arrays_disjoint;
}

int main() {
    int first_len;
    scanf("%d\n", &first_len);
    int first_array[first_len];
    inputArray(first_array, first_len);

    int second_len;
    scanf("%d\n", &second_len);
    int second_array[second_len];
    inputArray(second_array, second_len);

    printf("%d", isArraysDisjoint(first_array, first_len, second_array, second_len));
}

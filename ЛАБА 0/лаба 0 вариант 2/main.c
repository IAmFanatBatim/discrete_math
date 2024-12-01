#include <stdio.h>
#include "C:\Users\sovac\Desktop\дискретная математика\ЛАБА 0\array_input_output\library.c"

void getIntersectionArray(const int *a, const int a_len, const int *b, const int b_len, int *c, int *c_len) {
    *c_len = 0;
    for (int a_index = 0; a_index < a_len; a_index++) {
        for (int b_index = 0; b_index < b_len; b_index++) {
            if (a[a_index] == b[b_index]) {
                c[*c_len] = a[a_index];
                *c_len += 1;
                break;
            }
        }
    }
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

    int result_array[0];
    int result_len = 0;

    getIntersectionArray(first_array, first_len, second_array, second_len, result_array, &result_len);

    printArray(result_array, result_len);

}

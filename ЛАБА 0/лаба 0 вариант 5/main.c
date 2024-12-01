#include <stdio.h>
#include "C:\Users\sovac\Desktop\дискретная математика\ЛАБА 0\array_input_output\library.c"

int isAPartOfB(const int *a, const int a_len, const int *b, const int b_len) {
    int is_a_part_of_b = 1;
    for (int a_index = 0; a_index < a_len; a_index++) {
        int is_element_in_b = 0;
        for (int b_index = 0; b_index < b_len; b_index++) {
            if (b[b_index] == a[a_index]) {
                is_element_in_b = 1;
                break;
            }
        }
        if (!is_element_in_b) {
            is_a_part_of_b = 0;
            break;
        }
    }
    return is_a_part_of_b;
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

    printf("%d", isAPartOfB(first_array, first_len, second_array, second_len));
}

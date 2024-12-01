#include <stdio.h>
#include "C:\Users\sovac\Desktop\дискретная математика\ЛАБА 0\array_input_output\library.c"

int isAPartOfB(const int *a, const int a_len, const int *b, const int b_len) {
    int a_index = 0;
    int b_index = 0;
    int counter_of_doubles = 0;
    while (a_index < a_len || b_index < b_len) {
        if (b_index >= b_len || a_index < a_len && a[a_index] < b[b_index]) {;
            a_index++;
        } else {
            if (a[a_index] == b[b_index]) {
                counter_of_doubles++;
                a_index++;
            }
            b_index++;
        }
    }
    return counter_of_doubles == a_len;
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

#include <stdio.h>
#include "C:\Users\sovac\Desktop\дискретная математика\ЛАБА 0\array_input_output\library.c"

int getExceptionArray(const int *a, const int a_len, const int *b, const int b_len, int *c, int *c_len) {
    *c_len = 0;
    int a_index = 0;
    int b_index = 0;
    while (a_index < a_len || b_index < b_len) {
        if (b_index >= b_len || a_index < a_len && a[a_index] < b[b_index]) {
            c[*c_len] = a[a_index];
            *c_len += 1;
            a_index++;
        } else {
            if (a[a_index] == b[b_index]) {
                a_index++;
            } else {
                c[*c_len] = b[b_index];
                *c_len += 1;
            }
            b_index++;
        }
    }
}

int main() {
    //Общая часть, где осуществляется ввод сначала длины, а потом элементов каждого из массивов A и B
    int first_len;
    scanf("%d\n", &first_len);
    int first_array[first_len];
    inputArray(first_array, first_len);

    int second_len;
    scanf("%d\n", &second_len);
    int second_array[second_len];
    inputArray(second_array, second_len);

    //Часть для задач, которые требуют создания массива C. Изначальная длина устанавливается как сумма длин A и B, каждая из функций меняет его в соответствии с количеством подходящих элементов
    int result_len = first_len + second_len;
    int *result_array[result_len];

    //Вызовы функций для заполнения массива C и вывод массива C
    getExceptionArray(first_array, first_len, second_array, second_len, result_array, &result_len);
    printArray(result_array, result_len);

    //Вывод значений истина-ложь (для задач 5, 6, 7, 12)
}

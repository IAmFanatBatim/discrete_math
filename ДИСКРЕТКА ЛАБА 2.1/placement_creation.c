#include "ordered_array_set\ordered_array_set.c"
#include <assert.h>

//Выводит на экран все размещения множества set по placement_power с помощью алгоритма поиска с возвращением
//Рекурсивная функция без обертки; на каждой итерации она опирается на текущее значение формируемого размещения cur_placement
//ее длину cur_len и множество вариантов для текущего элемента set_of_variants
void print_all_placements_(int *cur_placement, size_t cur_len, ordered_array_set set_of_variants, int placement_power, ordered_array_set set) {
    for (int i = 0; i < set_of_variants.size; i++) {
        append_(cur_placement, &cur_len, set_of_variants.data[i]);
        ordered_array_set_deleteElement(&set_of_variants, cur_placement[cur_len - 1]);
        //Полученное размещение считается решением, если его длина равна placement_power
        if (cur_len == placement_power) {
            outputArray_(cur_placement, placement_power);
        } else {
            print_all_placements_(cur_placement, cur_len, set_of_variants, placement_power, set);
        }
        ordered_array_set_insert(&set_of_variants, cur_placement[cur_len - 1]);
        deleteByPosSaveOrder_(cur_placement, &cur_len, cur_len - 1);
    }
}

//Выводит на экран все размещения множества set с помощью алгоритма поиска с возвращением
//Обертка функции print_all_placements_, начинающая работу с пустым стартовым размещением, его длиной 0 и множеством вариантов, равным исходному; все это создается в теле функции
//Также здесь обрабатывается случай, когда длина требуемого размещения равна 0
void print_all_placements(int placement_power, ordered_array_set set) {
    assert(placement_power <= set.size);
    if (set.size == 0) {
        ordered_array_set_print(ordered_array_set_create(0));
    } else {
        ordered_array_set start_set_of_variants = ordered_array_set_create_from_array(set.data, set.size);
        int start_placement[set.size];
        int start_len = 0;
        print_all_placements_(start_placement, start_len, start_set_of_variants, placement_power, set);
    }
}

int main() {
    int a[3] = {1, 2, 3};
    ordered_array_set A = ordered_array_set_create_from_array(a, 3);
    print_all_placements(2, A);
}
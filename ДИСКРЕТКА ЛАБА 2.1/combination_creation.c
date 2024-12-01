#include "ordered_array_set\ordered_array_set.c"
#include <assert.h>

//Выводит на экран все сочетания множества set по combination_power с помощью алгоритма поиска с возвращением
//Рекурсивная функция без обертки; на каждой итерации она опирается на текущее значение формируемого сочетания cur_combination
//И значения "левой границы" подходящих на данной итерации элементов
void print_all_combinations_(ordered_array_set cur_combination, int left_border, int combination_power, ordered_array_set set) {
    //В цикле for перебираются возможные значения для текущего элемента
    for (int i = left_border; i <= (set.size - combination_power + left_border) && (i < set.size); i++) {
        //В подмножество-сочетание добавляется новый элемент, выбранный в цикле for
        ordered_array_set_insert(&cur_combination, set.data[i]);
        //Если полученное сочетание - решение, оно выводится на экран
        if (cur_combination.size == combination_power) {
            ordered_array_set_print(cur_combination);
        //Если полученное сочетание - не решение, этой же функцией добавляется его следующий элемент
        //При этом "левая граница" - элемент, следующий после добавленного на текущей итерации
        } else {
            print_all_combinations_(cur_combination, i+1, combination_power, set);
        }
        //Независимо от результата итерации, только что добавленный элемент удаляется, откатывая "заготовку" для сочетания к исходному варианту
        ordered_array_set_deleteElement(&cur_combination, set.data[i]);
    }
}

//Выводит на экран все сочетания множества set по combination_power с помощью алгоритма поиска с возвращением
//Обертка функции print_all_combinations_, начинающая работу с пустым стартовым сочетанием cur_combination и индексом левой границы 0
//Также здесь обрабатывается случай, когда длина требуемого сочетания равна 0
void print_all_combinations(int combination_power, ordered_array_set set) {
    assert(combination_power <= set.size);
    if (combination_power == 0) {
        ordered_array_set_print(ordered_array_set_create(0));
    } else {
        print_all_combinations_(ordered_array_set_create(combination_power), 0, combination_power, set);
    }
}

//Выводит на экран все подмножества множества set в порядке неубывания мощности
void print_all_subsets_power_increment(ordered_array_set set) {
    for (int k = 0; k <= set.size; k++) {
        print_all_combinations(k, set);
    }
}

int main() {
    int a[4] = {1, 2, 3, 4};
    ordered_array_set A = ordered_array_set_create_from_array(a, 4);
    print_all_subsets_power_increment(A);
}
#include "ordered_array_set\ordered_array_set.c"
#include <sys/time.h>

//Выводит на экран все перестановки множества set с помощью алгоритма поиска с возвращением
//Рекурсивная функция без обертки; на каждой итерации она опирается на текущее значение формируемой перестановки cur_arrangement
//ее длину cur_len и множество вариантов для текущего элемента set_of_variants
void print_all_arrangements_(int *cur_arrangement, size_t cur_len, ordered_array_set set_of_variants, ordered_array_set set) {
    //В цикле for перебираются возможные значения для текущего элемента
    for (int i = 0; i < set_of_variants.size; i++) {
        //В перестановку добавляется новый элемент, выбранный в цикле for, он же удаляется из множества вариантов
        append_(cur_arrangement, &cur_len, set_of_variants.data[i]);
        ordered_array_set_deleteElement(&set_of_variants, cur_arrangement[cur_len - 1]);
        //Если полученная перестановка - решение, она выводится на экран
        if (cur_len == set.size) {
            outputArray_(cur_arrangement, set.size);
        //Если полученная перестановка - не решение, этой же функцией добавляется ее следующий элемент
        //Значение сur_len е увеличивается на 1, потому что это уже выполняет функция append_
        } else {
            print_all_arrangements_(cur_arrangement, cur_len, set_of_variants, set);
        }
        //Независимо от результата итерации, только что добавленный элемент удаляется из перестановки и добавляется обратно в массив вариантов
        ordered_array_set_insert(&set_of_variants, cur_arrangement[cur_len - 1]);
        deleteByPosSaveOrder_(cur_arrangement, &cur_len, cur_len - 1);
    }
}

//Выводит на экран все перестановки множества set с помощью алгоритма поиска с возвращением
//Обертка функции print_all_arrangements_, начинающая работу с пустой стартовой перестановкой, ее длиной 0 и множеством вариантов, равным исходному; все это создается в теле функции
//Также здесь обрабатывается случай, когда длина исходного множества равна 0
void print_all_arrangements(ordered_array_set set) {
    if (set.size == 0) {
        ordered_array_set_print(ordered_array_set_create(0));
    } else {
        ordered_array_set start_set_of_variants = ordered_array_set_create_from_array(set.data, set.size);
        int start_arrangement[set.size];
        int start_len = 0;
        print_all_arrangements_(start_arrangement, start_len, start_set_of_variants, set);
    }
}

//Выводит на экран структуру timeval time
void print_timeval(struct timeval time) {
    printf("%ld,%.6ld", time.tv_sec, time.tv_usec);
}

//Выводит на экран все перестановки множества set и сообщение о том, сколько времени выполнялся алгоритм
void print_arrangements_and_time_of_generating (ordered_array_set set) {
    //Заранее объявляем структуры timeval для хранения времени начала, конца и длительности процесса генерации
    struct timeval start, end, difference;
    //Задаем значение временной метки перед генерацией и после нее
    gettimeofday(&start, NULL);
    print_all_arrangements(set);
    gettimeofday(&end, NULL);
    //Высчитываем разницу в секундах и микросекундах и сохраняем в структуру difference
    difference.tv_sec = end.tv_sec - start.tv_sec - (end.tv_usec < start.tv_usec);
    difference.tv_usec = (end.tv_usec + (end.tv_usec < start.tv_usec) * 1000000)-start.tv_usec;

    //Вывод сообщения на экран
    printf("|M| = %llu; time of generation = ", set.size);
    print_timeval(difference);
    printf("\n");
}

int main() {
    int a[0] = {};
    ordered_array_set A = ordered_array_set_create_from_array(a, 0);
    print_arrangements_and_time_of_generating(A);
}
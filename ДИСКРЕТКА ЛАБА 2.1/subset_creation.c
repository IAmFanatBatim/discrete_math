#include "ordered_array_set\ordered_array_set.c"
#include <sys/time.h>

//Возвращает подмножество множества set, заданное двоичным вектором vector
ordered_array_set create_subset_by_binary_vector(ordered_array_set set, int vector) {
    assert(1<<set.size > vector);
    ordered_array_set result = ordered_array_set_create(set.capacity);
    for (int i = 0; i < set.capacity; i++) {
        if (vector >> i & 1) {
            ordered_array_set_insert(&result, set.data[i]);
        }
    }
    ordered_array_set_shrinkToFit(&result);
    return result;
}

//Выводит на экран все подмножества множества set с помощью алгоритма поиска с возвращением
//Рекурсивная функция без обертки; на каждой итерации она опирается на текущее значение формируемого двоичного вектора cur_vector
//и номер обрабатываемого разряда (слева направо) cur_digit
void print_all_subsets_(int cur_vector, int cur_digit, ordered_array_set set) {
    //В цикле for перебираются возможные значения для разряда двоичного вектора
    for (int i = 0; i <= 1; i++) {
        //В конец вектора добавляется новый разряд, обращенный в 0 или 1 в зависимости от итерации цикла for
        int plus_cur_vector = (cur_vector << 1) + i;
        //Если полученный вектор - решение, на его основе генерируется подмножество, выводимое на экран
        if (cur_digit == set.size) {
            ordered_array_set cur_subset = create_subset_by_binary_vector(set, plus_cur_vector);
            ordered_array_set_print(cur_subset);
        //Если полученный вектор - не решение, этой же функцией обрабатывается его следующий разряд
        } else {
            print_all_subsets_(plus_cur_vector, cur_digit+1, set);
        }
    }
}

//Выводит на экран все подмножества множества set с помощью алгоритма поиска с возвращением
//Обертка функции print_all_subsets_, начинающая работу с пустым стартовым вектором cur_vector и номером обрабатываемого разряда 1
//Также здесь обрабатывается случай, когда длина исходного множества равна 0
void print_all_subsets(ordered_array_set set) {
    if (set.size == 0) {
        ordered_array_set_print(ordered_array_set_create(0));
    }
    else {
        print_all_subsets_(0, 1, set);
    }
}

//Выводит на экран структуру timeval time
void print_timeval(struct timeval time) {
    printf("%ld,%.6ld", time.tv_sec, time.tv_usec);
}

//Выводит на экран все подмножества множества set и сообщение о том, сколько времени выполнялся алгоритм
void print_subsets_and_time_of_generating (ordered_array_set set) {
    //Заранее объявляем структуры timeval для хранения времени начала, конца и длительности процесса генерации
    struct timeval start, end, difference;
    //Задаем значение временной метки перед генерацией и после нее
    gettimeofday(&start, NULL);
    print_all_subsets(set);
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
    int a[6] = {1, 2, 3, 4, 5, 6};
    ordered_array_set A = ordered_array_set_create_from_array(a, 6);
    print_subsets_and_time_of_generating(A);
}
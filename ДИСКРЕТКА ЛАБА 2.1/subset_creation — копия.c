#include "ordered_array_set\ordered_array_set.c"
#include <sys/time.h>

//Возвращает подмножество множества set, заданное двоичным вектором vector
ordered_array_set create_subset_by_binary_vector(ordered_array_set set, int vector) {
    ordered_array_set result = ordered_array_set_create(set.capacity);
    for (int i = 0; i < set.capacity; i++) {
        if (vector >> i & 1) {
            ordered_array_set_insert(&result, set.data[i]);
        }
    }
    ordered_array_set_shrinkToFit(&result);
    return result;
}

void generate_all_subsets_(int cur_vector, int cur_digit, ordered_array_set set, bool need_to_print) {
    for (int i = 0; i <= 1; i++) {
        int plus_cur_vector = (cur_vector << 1) + i;
        if (cur_digit >= set.size) {
            ordered_array_set cur_subset = create_subset_by_binary_vector(set, plus_cur_vector);
            if (need_to_print) {
                ordered_array_set_print(cur_subset);
            }
            if (cur_digit > set.size) {
                break;
            }
        } else {
            generate_all_subsets_(plus_cur_vector, cur_digit+1, set, need_to_print);
        }
    }
}

void generate_all_subsets(ordered_array_set set, bool need_to_print) {
    generate_all_subsets_(0, 1, set, need_to_print);
}

struct timeval get_time_of_subsets_generating (ordered_array_set set, bool need_to_print) {
    struct timeval start, end, difference;

    gettimeofday(&start, NULL);
    generate_all_subsets_(0, 1, set, need_to_print);
    gettimeofday(&end, NULL);

    difference.tv_sec = (end.tv_sec - start.tv_sec);
    difference.tv_usec = (((difference.tv_sec * 1000000)+end.tv_usec)-(start.tv_usec)) % 1000000;

    return difference;
}

void print_timeval(struct timeval time) {
    printf("%ld.%.6ld", time.tv_sec, time.tv_usec);
};

void print_time_of_subsets_generating (int max_power) {
    ordered_array_set main_set = ordered_array_set_create(max_power+1);
    for (int i = 0; i <= max_power; i++) {
        struct timeval time_of_generation = get_time_of_subsets_generating(main_set, 0);
        printf("|M| = %d; time of generation = ", i);
        print_timeval(time_of_generation);
        printf("\n");
        ordered_array_set_insert(&main_set, i+1);
    }
}

int main() {
    /*ordered_array_set A = ordered_array_set_create_from_array((int[4]) {1, 2, 3, 4}, 4);
    struct timeval start, end, difference;
    gettimeofday(&start, NULL);
    generate_all_subsets(A, 1);
    //sleep(5);
    gettimeofday(&end, NULL);

    difference.tv_sec = (end.tv_sec - start.tv_sec);
    difference.tv_usec = (((difference.tv_sec * 1000000)+end.tv_usec)-(start.tv_usec)) % 1000000;

    printf("%llu %llu\n", start.tv_sec, start.tv_usec);
    printf("%llu %llu\n", end.tv_sec, end.tv_usec);
    printf("%llu %llu\n", difference.tv_sec, difference.tv_usec);*/
    print_time_of_subsets_generating(24);
}
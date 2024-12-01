#include <stdio.h>
#include <stdbool.h>
#define UNIVERSE_LENGTH 12

typedef struct {
    int set[UNIVERSE_LENGTH];
    size_t lenght;
} unordSet;

const unordSet UNIVERSUM = {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}, UNIVERSE_LENGTH};

unordSet join(unordSet set_a, unordSet set_b) {
    unordSet result = {{}, 0};

    for (int a_index = 0; a_index < set_a.lenght; a_index++) {
        result.set[a_index] = set_a.set[a_index];
    }
    result.lenght = set_a.lenght;

    for (int b_index = 0; b_index < set_b.lenght; b_index++) {
        bool is_element_unique = true;
        for (int a_index = 0; a_index < set_a.lenght; a_index++) {
            if (set_b.set[b_index] == set_a.set[a_index]) {
                is_element_unique = false;
                break;
            }
        }
        if (is_element_unique) {
            result.set[result.lenght] = set_b.set[b_index];
            result.lenght += 1;
        }
    }
    return result;
}

unordSet intersection(unordSet set_a, unordSet set_b) {
    unordSet result = {{}, 0};

    for (int a_index = 0; a_index < set_a.lenght; a_index++) {
        for (int b_index = 0; b_index < set_b.lenght; b_index++) {
            if (set_a.set[b_index] == set_b.set[a_index]) {
                result.set[result.lenght] = set_a.set[b_index];
                break;
            }
        }
    }
    return result;
}

unordSet difference(unordSet set_a, unordSet set_b) {
    unordSet result = {{}, 0};

    for (int a_index = 0; a_index < set_a.lenght; a_index++) {
        bool is_element_unique = true;
        for (int b_index = 0; b_index < set_b.lenght; b_index++) {
            if (set_a.set[b_index] == set_b.set[a_index]) {
                is_element_unique = false;
                break;
            }
        }
        if (is_element_unique) {
            result.set[result.lenght] = set_b.set[a_index];
            result.lenght += 1;
        }
    }
    return result;
}

unordSet symmetricalDifference(unordSet set_a, unordSet set_b) {
    unordSet a_minus_b = difference(set_a, set_b);
    unordSet b_minus_a = difference(set_b, set_a);
    return join(a_minus_b, b_minus_a);
}

unordSet addition(unordSet set_a) {
    return difference(UNIVERSUM, set_a);
}

bool inclusion(unordSet set_a, unordSet set_b) {
    bool is_b_part_of_a = true;
    for (int b_index = 0; b_index < set_b.lenght; b_index++) {
        bool is_element_unique = true;
        for (int a_index = 0; a_index < set_a.lenght; a_index++) {
            if (set_a.set[b_index] == set_b.set[a_index]) {
                is_element_unique = false;
                break;
            }
        }
        if (is_element_unique) {
            is_b_part_of_a = false;
            break;
        }
    }
    return is_b_part_of_a;
}

bool strictInclusion(unordSet set_a, unordSet set_b) {
    return inclusion(set_a, set_b) && (set_a.lenght != set_b.lenght);
}

bool equality(unordSet set_a, unordSet set_b) {
    return inclusion(set_a, set_b) && (set_a.lenght == set_b.lenght);
}


int main() {
    printf("Hello, World!\n");
    return 0;
}

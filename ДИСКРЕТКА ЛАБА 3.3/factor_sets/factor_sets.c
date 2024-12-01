#include "../../ДИСКРЕТКА ЛАБА 3.1/bin_relations/bin_relation_definition_input_output.c"
#include <stdlib.h>

typedef struct {
    int *display;
    int max_value;
} splitting;

splitting splitting_createEmpty(int max_value) {
    int *display = malloc(sizeof(int) * max_value);
    for (int cur_el = 0; cur_el < max_value; cur_el++) {
        display[cur_el] = 0;
    }
    return (splitting) {display, max_value};
}

void splitting_print(splitting s) {
    printf("{");
    int max_set = 0;
    for (int cur_x = 1; cur_x <= 10; cur_x ++) {
        if (s.display[cur_x-1] > max_set) {
            max_set = s.display[cur_x-1];
        }
    }
    for (int cur_set = 1; cur_set <= max_set; cur_set++) {
        printf("{");
        for (int cur_y = 1; cur_y <= s.max_value; cur_y++) {
            if (s.display[cur_y-1] == cur_set) {
                printf("%d, ", cur_y);
            }
        }
        printf("\b\b}, ");
    }
    printf("\b\b}");
}

splitting getFactorSet (bin_relation A) {
    splitting s = splitting_createEmpty(A.max_value);
    int classes_amount = 1;
    for (int cur_x = 1; cur_x <= A.max_value; cur_x++) {
        if (s.display[cur_x - 1] == 0) {
            for (int cur_y = 1; cur_y <= A.max_value; cur_y++) {
                if (bin_relation_getValue(A, cur_y, cur_x)) {
                    s.display[cur_y - 1] = classes_amount;
                }
            }
            classes_amount += 1;
        }
    }
    return s;
}

int main() {
    bin_relation A = bin_relation_createEmpty(10);
    for (int x = 1; x <= 10; x++) {
        for (int y = 1; y <= 10; y++) {
            if (abs(x-y) % 2 == 0) {
                bin_relation_changeValue(&A, x, y, 1);
            }
        }
    }
    splitting Phi = getFactorSet(A);
    splitting_print(Phi);
}
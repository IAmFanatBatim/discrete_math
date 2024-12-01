#include "../../ДИСКРЕТКА ЛАБА 3.1/bin_relations/bin_relation_definition_input_output.c"
#include "../../ДИСКРЕТКА ЛАБА 3.1/bin_relations/bin_relations_operations.c"
#include "../../ДИСКРЕТКА ЛАБА 3.1/bin_relations/bin_relations_properties.c"
#include <stdbool.h>

typedef struct {
    int x;
    int y;
} Point;

#define M1_LEN 9
#define M2_LEN 13

Point M1[M1_LEN] = {
        {-1, 1}, {0, 1}, {1, 1},
        {-1, 0}, {0, 0}, {1, 0},
        {-1, -1}, {0, -1}, {1, -1}
};
Point M2[M2_LEN] = {
        {0, 2},
        {-1, 1}, {0, 1}, {1, 1},
        {-2, 0}, {-1, 0}, {0, 0}, {1, 0},{2, 0},
        {-1, -1}, {0, -1}, {1, -1},
        {0, -2}
};

bin_relation createForVariant6(Point *set, int set_len) {
    bin_relation result = bin_relation_createEmpty(set_len);
    for (int i = 1; i <= set_len; i++) {
        Point first_point = set[i];
        for (int j = 1; j <= set_len; j++) {
            Point second_point = (set[j]);
            if (first_point.x - second_point.x < first_point.y - second_point.y) {
                bin_relation_changeValue(&result, i, j, 1);
            }
        }
    }
    return result;
}

bin_relation createStrictOrderRelation(bin_relation A) {
    for (int i = 1; i <= A.max_value; i++) {
        bin_relation_changeValue(&A, i, i, 0);
    }
    return A;
}

bin_relation createDominationRelation(bin_relation A) {
    bin_relation strict_A = createStrictOrderRelation(A);
    return bin_relation_difference(strict_A, bin_relation_degree(strict_A, 2));
}

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
    printf("[");
    int max_set = 0;
    for (int cur_x = 1; cur_x <= s.max_value; cur_x ++) {
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
    printf("\b\b]");
}

splitting getTopologicalSorting (bin_relation A) {
    splitting l = splitting_createEmpty(A.max_value);
    int levels_amount = 1;
    int w_array[A.max_value];
    int i = -1;

    for (int cur_col_ind = 1; cur_col_ind <= A.max_value; cur_col_ind++) {
        int cur_sum = 0;
        for (int cur_row_ind = 1; cur_row_ind <= A.max_value; cur_row_ind++) {
            cur_sum += bin_relation_getValue(A, cur_row_ind, cur_col_ind);
        }
        w_array[cur_col_ind-1] = cur_sum;
    }

    bool flag = false;
    for (int w_el_ind = 0; w_el_ind < A.max_value; w_el_ind++) {
        flag += w_array[w_el_ind] >= 0;
    }

    while (flag) {
        for (int w_el_ind = 0; w_el_ind < A.max_value; w_el_ind++) {
            if (w_array[w_el_ind] == 0) {
                l.display[w_el_ind] = levels_amount;
                w_array[w_el_ind] = i;
            }
        }

        for (int w_el_ind = 0; w_el_ind < A.max_value; w_el_ind++) {
            if (w_array[w_el_ind] == i) {
                for (int cur_col_ind = 1; cur_col_ind <= A.max_value; cur_col_ind++) {
                    w_array[cur_col_ind-1] -= bin_relation_getValue(A, w_el_ind+1, cur_col_ind);
                }
            }
        }

        i--;
        levels_amount++;
        flag = false;
        for (int w_el_ind = 0; w_el_ind < A.max_value; w_el_ind++) {
            flag += w_array[w_el_ind] >= 0;
        }
    }
    return l;
}

int main () {
    bin_relation A1 = createForVariant6(M1, M1_LEN);
    bin_relation A2 = createForVariant6(M2, M2_LEN);

    printf("Matrix of relation A1:\n");
    bin_relation_matrixPrint(A1);
    printf("\nMatrix of relation A2:\n");
    bin_relation_matrixPrint(A2);

    printf("\nProperties of relation A1:\n");
    bin_relation_print_all_properties(A1);
    printf("\nProperties of relation A2:\n");
    bin_relation_print_all_properties(A2);

    bin_relation dom_A1 = createDominationRelation(A1);
    printf("\nMatrix of domination relation over A1:\n");
    bin_relation_matrixPrint(dom_A1);
    bin_relation dom_A2 = createDominationRelation(A2);
    printf("\nMatrix of domination relation over A2:\n");
    bin_relation_matrixPrint(dom_A2);

    printf("\n");
    splitting L1 = getTopologicalSorting(createDominationRelation(dom_A1));
    splitting L2 = getTopologicalSorting(createDominationRelation(dom_A2));
    splitting_print(L1);
    printf("\n");
    splitting_print(L2);
}
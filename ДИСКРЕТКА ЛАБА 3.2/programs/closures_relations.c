#include "../../ДИСКРЕТКА ЛАБА 3.1/bin_relations/bin_relation_definition_input_output.c"
#include "../../ДИСКРЕТКА ЛАБА 3.1/bin_relations/bin_relations_operations.c"

bin_relation transitive_closure_algorithm1(bin_relation A) {
    bin_relation C = A;
    bin_relation S = bin_relation_composition(A, A);
    while (!bin_relation_inclusion(S, C)) {
        C = bin_relation_union(C, S);
        S = bin_relation_composition(S, A);
    }
    return C;
}
bin_relation transitive_closure_algorithm2(bin_relation A) {
    bin_relation C = A;
    bin_relation C2 = bin_relation_composition(C, C);
    while (!bin_relation_inclusion(C2, C)) {
        C = bin_relation_union(C, C2);
        C2 = bin_relation_composition(C, C);
    }
    return C;
}
bin_relation transitive_closure_algorithm3(bin_relation A) {
    bin_relation C = A;
    for (int z = 1; z <= A.max_value; z++) {
        for (int x = 1; x <= A.max_value; x++) {
            if (bin_relation_getValue(C, x, z)) {
                for (int y = 1; y <= A.max_value; y++) {
                    if (bin_relation_getValue(C, z, y)) {
                        C.values[x-1] |=  1 << (y-1);
                    }
                }
            }
        }
    }
    return C;
}

bin_relation transitive_closure_algorithm1_experiment(bin_relation A, int *composition_amount) {
    bin_relation C = A;
    bin_relation S = bin_relation_composition(A, A);
    (*composition_amount) = 1;
    while (!bin_relation_inclusion(S, C)) {
        C = bin_relation_union(C, S);
        S = bin_relation_composition(S, A);
        (*composition_amount)++;
    }
    return C;
}
bin_relation transitive_closure_algorithm2_experiment(bin_relation A, int *composition_amount) {
    bin_relation C = A;
    bin_relation C2 = bin_relation_composition(C, C);
    (*composition_amount) = 1;
    while (!bin_relation_inclusion(C2, C)) {
        C = bin_relation_union(C, C2);
        C2 = bin_relation_composition(C, C);
        (*composition_amount)++;
    }
    return C;
}
bin_relation transitive_closure_algorithm3_experiment(bin_relation A, int *compares_amount) {
    bin_relation C = A;
    (*compares_amount) = 1;
    for (int z = 1; z <= A.max_value; z++, (*compares_amount)++) {
        (*compares_amount)++;
        for (int x = 1; x <= A.max_value; x++, (*compares_amount)++) {
            (*compares_amount)++;
            if (bin_relation_getValue(C, x, z)) {
                for (int y = 1; y <= A.max_value; y++, (*compares_amount)++) {
                    (*compares_amount)++;
                    if (bin_relation_getValue(C, z, y)) {
                        C.values[x-1] |=  1 << (y-1);
                    }
                }
            }
        }
    }
    return C;
}

int main() {
    bin_relation min_of_compos = bin_relation_createEmpty(10);
    int x_values[5] = {1, 2, 4, 5, 7};
    int y_values[3] = {3, 8, 10};
    for (int ind_x = 0; ind_x < 5; ind_x ++) {
        for (int ind_y = 0; ind_y < 3; ind_y++) {
            bin_relation_changeValue(&min_of_compos, x_values[ind_x], y_values[ind_y], 1);
        }
    }

    int compos_amount_for_min1 = 0;
    bin_relation min_of_compos_closure1 = transitive_closure_algorithm1_experiment(min_of_compos, &compos_amount_for_min1);
    bin_relation_matrixPrint(min_of_compos_closure1);
    printf("Compositions: %d\n\n", compos_amount_for_min1);

    int compos_amount_for_min2 = 0;
    bin_relation min_of_compos_closure2 = transitive_closure_algorithm2_experiment(min_of_compos, &compos_amount_for_min2);
    bin_relation_matrixPrint(min_of_compos_closure2);
    printf("Compositions: %d\n\n", compos_amount_for_min2);


    bin_relation max_of_compos = bin_relation_createEmpty(10);
    for (int i = 1; i <= 10; i++) {
        bin_relation_changeValue(&max_of_compos, i, (i%10)+1, 1);
    }

    int compos_amount_for_max1 = 0;
    bin_relation max_of_compos_closure1 = transitive_closure_algorithm1_experiment(max_of_compos, &compos_amount_for_max1);
    bin_relation_matrixPrint(max_of_compos_closure1);
    printf("Compositions: %d\n\n", compos_amount_for_max1);

    int compos_amount_for_max2 = 0;
    bin_relation max_of_compos_closure2 = transitive_closure_algorithm2_experiment(max_of_compos, &compos_amount_for_max2);
    bin_relation_matrixPrint(max_of_compos_closure2);
    printf("Compositions: %d\n\n", compos_amount_for_max2);
    
    bin_relation min_of_compares = bin_relation_createEmpty(10);

    int compares_amount_for_min = 0;
    bin_relation min_of_compares_closure = transitive_closure_algorithm3_experiment(min_of_compares, &compares_amount_for_min);
    bin_relation_matrixPrint(min_of_compares_closure);
    printf("Compares: %d\n\n", compares_amount_for_min);

    bin_relation max_of_compares = bin_relation_createEmpty(10);
    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= 10; j++) {
            bin_relation_changeValue(&max_of_compares, i, j, 1);
        }
    }

    int compares_amount_for_max = 0;
    bin_relation max_of_compares_closure = transitive_closure_algorithm3_experiment(max_of_compares, &compares_amount_for_max);
    bin_relation_matrixPrint(max_of_compares_closure);
    printf("Compares: %d\n\n", compares_amount_for_max);
}
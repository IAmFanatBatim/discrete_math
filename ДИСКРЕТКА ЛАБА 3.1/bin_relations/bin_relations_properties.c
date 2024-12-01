#include <stdbool.h>
#include "bin_relation_definition_input_output.c"

#ifndef BIN_REL_PROPERTIES
#define BIN_REL_PROPERTIES

//Возвращает 1, если отношение a рефлексивно, и 0 в противном случае, а также печатает соответствующее сообщение
bool bin_relation_is_reflexive(bin_relation a) {
    for (int x = 1; x <= a.max_value; x++) {
        if (!bin_relation_getValue(a, x, x)) {
            printf("This relation is not reflexive, because the pair (%d, %d) doesn't belong it.\n", x, x);\
            return false;
        }
    }
    printf("This relation is reflexive.\n");
    return true;
}

//Возвращает 1, если отношение aнтирефлексивно, и 0 в противном случае, а также печатает соответствующее сообщение
bool bin_relation_is_antireflexive(bin_relation a) {
    for (int x = 1; x <= a.max_value; x++) {
        if (bin_relation_getValue(a, x, x)) {
            printf("This relation is not antireflexive, because the pair (%d, %d) belongs it.\n", x, x);
            return false;
        }
    }
    printf("This relation is antireflexive.\n");
    return true;
}

//Возвращает 1, если отношение симметрично, и 0 в противном случае, а также печатает соответствующее сообщение
bool bin_relation_is_symmetrical(bin_relation a) {
    for (int x = 1; x <= a.max_value; x++) {
        for (int y = x+1; y <= a.max_value; y++) {
            if (bin_relation_getValue(a, x, y) && !bin_relation_getValue(a, y, x)) {
                printf("This relation is not symmetrical, because the pair (%d, %d) belongs it and the pair (%d, %d) doesn't.\n", x, y, y, x);
                return false;
            }
        }
    }
    printf("This relation is symmetrical.\n");
    return true;
}

//Возвращает 1, если отношение антисимметрично, и 0 в противном случае, а также печатает соответствующее сообщение
bool bin_relation_is_antisymmetrical(bin_relation a) {
    for (int x = 1; x <= a.max_value; x++) {
        for (int y = x+1; y <= a.max_value; y++) {
            if (bin_relation_getValue(a, x, y) && bin_relation_getValue(a, y, x)) {
                printf("This relation is not antisymmetrical, because both pairs (%d, %d) and (%d, %d) belong it.\n", x, y, y, x);
                return false;
            }
        }
    }
    printf("This relation is antisymmetrical.\n");
    return true;
}

//Возвращает 1, если отношение транзитивно, и 0 в противном случае, а также печатает соответствующее сообщение
bool bin_relation_is_transitive(bin_relation a) {
    for (int x = 1; x <= a.max_value; x++) {
        for (int z = 1; z <= a.max_value; z++) {
            if (bin_relation_getValue(a, x, z) && a.values[z-1] != 0) {
                for (int y = 1; y <= a.max_value; y++) {
                    if (bin_relation_getValue(a, z, y) && !bin_relation_getValue(a, x, y)) {
                        printf("This relation is not transitive, because both pairs (%d, %d) and (%d, %d) belong it, but pair (%d, %d) doesn't.\n", x, z, z, y, x, y);
                        return false;
                    }
                }
            }
        }
    }
    printf("This relation is transitive.\n");
    return true;
}

//Возвращает 1, если отношение антитранзитивно, и 0 в противном случае, а также печатает соответствующее сообщение
bool bin_relation_is_antitransitive(bin_relation a) {
    for (int x = 1; x <= a.max_value; x++) {
        for (int z = 1; z <= a.max_value; z++) {
            if (bin_relation_getValue(a, x, z) && a.values[z-1] != 0) {
                for (int y = 1; y <= a.max_value; y++) {
                    if (bin_relation_getValue(a, z, y) && bin_relation_getValue(a, x, y)) {
                        printf("This relation is not antitransitive, because both pairs (%d, %d) and (%d, %d) belong it, and also the pair (%d, %d) does.\n", x, z, z, y, x, y);
                        return false;
                    }
                }
            }
        }
    }
    printf("This relation is antitransitive.\n");
    return true;
}

//Возвращает 1, если отношение полно, и 0 в противном случае, а также печатает соответствующее сообщение
bool bin_relation_is_full(bin_relation a) {
    for (int x = 1; x <= a.max_value; x++) {
        for (int y = x+1; y <= a.max_value; x++) {
            if (!bin_relation_getValue(a, x, y) && !bin_relation_getValue(a, y, x)) {
                printf("This relation is not full, because none of the pairs (%d, %d) and (%d, %d) belong it.\n", x, y, y, x);
                return false;
            }
        }
    }
    printf("This relation is full.\n");
    return true;
}

//Выводит на экран сообщения, обладает или не обладает отношение a каждым из основных свойств, а также выводит производные свойства, которыми обладает это отношение
void bin_relation_print_all_properties(bin_relation a) {
    printf("\tSimple properties of a relation: \n");
    bool is_reflexive = bin_relation_is_reflexive(a);
    bool is_antireflexive = bin_relation_is_antireflexive(a);
    bool is_symmetrical = bin_relation_is_symmetrical(a);
    bool is_antisymmetrical = bin_relation_is_antisymmetrical(a);
    bool is_transitive = bin_relation_is_transitive(a);
    bool is_antitransitive = bin_relation_is_antitransitive(a);
    bool is_full = bin_relation_is_full(a);

    bool has_derived_properties = false;

    printf("\tDerived properties of a relation: \n");
    if (is_reflexive && is_symmetrical) {
        has_derived_properties = true;
        printf("This relation has the tolerance property.\n");
        if (is_transitive) {
            printf("This relation has the equivalence property.\n");
        }
    }
    if (is_antisymmetrical && is_transitive) {
        has_derived_properties = true;
        printf("This relation has the order property.\n");
        if (is_reflexive) {
            printf("This relation has the non-strict order property.\n");
        }
        if (is_antireflexive) {
            printf("This relation has the strict order property.\n");
        }
        if (is_full) {
            printf("This relation has the linear order property.\n");
            if (is_reflexive) {
                printf("This relation has the non-strict linear order property.\n");
            }
            if (is_antireflexive) {
                printf("This relation has the non-strict linear order property.\n");
            }
        }
    }
    if (!has_derived_properties) {
        printf("This relation hasn't derived properties.\n");
    }
}

#endif
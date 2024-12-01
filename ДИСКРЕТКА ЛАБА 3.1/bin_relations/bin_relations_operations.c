#include <stdbool.h>
#include "bin_relation_definition_input_output.c"

#ifndef BIN_REL_OPERATIONS
#define BIN_REL_OPERATIONS

int max2 (int x, int y) {
    return (x > y) ? x : y;
}

//Возвращает 1, если отношение a включено в отношение b, и 0 в противном случае
bool bin_relation_inclusion(bin_relation a, bin_relation b) {
    bool is_inclusion = true;
    for (int i = 0; i < max2(a.max_value, b.max_value) && is_inclusion; i++) {
        is_inclusion = (b.values[i] | a.values[i]) == b.values[i];
    }
    return is_inclusion;
}

//Возвращает 1, если отношения a и b равны, и 0 в противном случае
bool bin_relation_equality(bin_relation a, bin_relation b) {
    bool is_equality = true;
    for (int i = 0; i < max2(a.max_value, b.max_value) && is_equality; i++) {
        is_equality = b.values[i] == a.values[i];
    }
    return is_equality;
}

//Возвращает 1, если отношение a строго включено в отношение b, и 0 в противном случае
bool bin_relation_strictInclusion(bin_relation a, bin_relation b) {
    bool is_inclusion = true;
    bool is_equality = true;
    for (int i = 0; i < max2(a.max_value, b.max_value); i++) {
        is_inclusion &= (b.values[i] | a.values[i]) == b.values[i];
        is_equality &= b.values[i] == a.values[i];
    }
    return is_inclusion && !is_equality;
}

//Возвращает отношение — объединение отношений a и b
bin_relation bin_relation_union(bin_relation a, bin_relation b) {
    bin_relation c = bin_relation_createEmpty(max2(a.max_value, b.max_value));
    for (int i = 0; i < c.max_value; i++) {
        c.values[i] = a.values[i] | b.values[i];
    }
    return c;
}

//Возвращает отношение — пересечение отношений a и b
bin_relation bin_relation_intersection(bin_relation a, bin_relation b) {
    bin_relation c = bin_relation_createEmpty(max2(a.max_value, b.max_value));
    for (int i = 0; i < c.max_value; i++) {
        c.values[i] = a.values[i] & b.values[i];
    }
    return c;
}

//Возвращает отношение — разность отношений a и b
bin_relation bin_relation_difference(bin_relation a, bin_relation b) {
    bin_relation c = bin_relation_createEmpty(max2(a.max_value, b.max_value));
    for (int i = 0; i < c.max_value; i++) {
        c.values[i] = a.values[i] & ~b.values[i];
    }
    return c;
}

//Возвращает отношение — симметрическую разность отношений a и b
bin_relation bin_relation_symmetricalDifference(bin_relation a, bin_relation b) {
    bin_relation c = bin_relation_createEmpty(max2(a.max_value, b.max_value));
    for (int i = 0; i < c.max_value; i++) {
        c.values[i] = a.values[i] ^ b.values[i];
    }
    return c;
}

//Возвращает отношение — дополнение до универсального отношения на множестве {1, ..., a.max_value} отношения a
bin_relation bin_relation_complement(bin_relation a) {
    bin_relation c = bin_relation_createEmpty(a.max_value);
    for (int i = 0; i < c.max_value; i++) {
        c.values[i] = ~a.values[i] & ((1<<a.max_value) - 1);
    }
    return c;
}

//Возвращает отношение — обращение отношения a
bin_relation bin_relation_conversion(bin_relation a) {
    bin_relation c = bin_relation_createEmpty(a.max_value);
    for (int i = 1; i <= c.max_value; i++) {
        for (int j = 1; j <= c.max_value; j++) {
            bin_relation_changeValue(&c, i, j, bin_relation_getValue(a, j, i));
        }
    }
    return c;
}

//Возвращает отношение — композицию отношений a и b
bin_relation bin_relation_composition(bin_relation a, bin_relation b) {
    bin_relation c = bin_relation_createEmpty(max2(a.max_value, b.max_value));
    for (int i = 1; i <= c.max_value; i++) {
        for (int j = 1; j <= c.max_value; j++) {
            if (bin_relation_getValue(a, i, j)) {
                c.values[i-1] |= b.values[j-1];
            }
        }
    }
    return c;
}

//Возвращает отношение — композицию отношений a и b
bin_relation bin_relation_composition2(bin_relation a, bin_relation b) {
    bin_relation c = bin_relation_createEmpty(max2(a.max_value, b.max_value));
    for (int i = 1; i <= c.max_value; i++) {
        for (int j = 1; j <= c.max_value; j++) {
            if (bin_relation_getValue(a, i, j)) {
                for (int k = 1; k <= c.max_value; k++) {
                    c.values[i-1] |= bin_relation_getValue(b, j, k) << (k-1);
                }
            }
        }
    }
    return c;
}

//Возвращает отношение — степень degree отношения a, то есть композицию отношения a с самим собой, выполненную degree-1 раз
bin_relation bin_relation_degree(bin_relation a, int degree) {
    bin_relation c = a;
    for (int i = 1; i < degree; i++) {
        c = bin_relation_composition(c, a);
    }
    return c;
}
#endif
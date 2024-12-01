#ifndef INC_ORDERED_ARRAY_SET_C
#define INC_ORDERED_ARRAY_SET_C

#include "ordered_array_set.h"
#include "array\array.c"
#include "C:\Users\sovac\Desktop\ОП, преимущественно лабы\second_semester\libs\algorithms\math_basics\math_basics.c"

ordered_array_set ordered_array_set_create (size_t capacity) {
   return (ordered_array_set) {
       malloc(sizeof(int) * capacity),
       0,
       capacity
   };
}

ordered_array_set ordered_array_set_create_from_array (const int *a, size_t size) {
    ordered_array_set result = ordered_array_set_create(size);
    for (size_t i = 0; i < size; i++) {
        ordered_array_set_insert(&result, a[i]);
    }
    qsort(result.data, size, sizeof(int), compare_ints);
    ordered_array_set_shrinkToFit(&result);
    return result;
}

static void ordered_array_set_shrinkToFit (ordered_array_set *a) {
    if (a->size != a->capacity) {
        a->data = (int *) realloc(a->data, sizeof(int) * a->size);
        a->capacity = a->size;
    }
}

static void ordered_array_set_increaseCapacity (ordered_array_set *a, size_t slots) {
    a->data = (int *) realloc(a->data, sizeof(int) * (a->size + slots));
    a->capacity += slots;
}

size_t ordered_array_set_in (ordered_array_set *set, int value) {
    size_t index = binarySearch_(set->data, set->size,value);
    return (index != SIZE_MAX) ? index : set->size;
}

bool ordered_array_set_isEqual (ordered_array_set set1, ordered_array_set set2) {
    return memcmp(set1.data, set2.data, sizeof(int) * set1.size) == 0;
}

bool ordered_array_set_isSubset (ordered_array_set subset, ordered_array_set set) {
    bool is_subset = 1;
    for (size_t i = 0; i < subset.size; i++) {
        if (ordered_array_set_in(&set, subset.data[i]) == set.size) {
            is_subset = 0;
            break;
        }
    }
    return is_subset;
}

void ordered_array_set_isAbleAppend (ordered_array_set *set) {
    assert(set->size < set->capacity);
}

void ordered_array_set_insert (ordered_array_set *set, int value) {
    ordered_array_set_isAbleAppend(set);
    if (set->size == 0 || value > set->data[(set->size)-1]) {
        append_(set->data, &(set->size), value);
    } else if (ordered_array_set_in(set, value) == set->size) {
        size_t start_index = binarySearchMoreOrEqual_(set->data, set->size, value);
        insert_(set->data, &(set->size), start_index, value);
    }
}

void ordered_array_set_deleteElement (ordered_array_set *set, int value) {
    if (ordered_array_set_in(set, value) != set-> size) {
        deleteByPosSaveOrder_(set->data, &(set->size), ordered_array_set_in(set, value));
    }
}

ordered_array_set join (ordered_array_set set1, ordered_array_set set2) {
    ordered_array_set result = ordered_array_set_create(set1.capacity + set2.capacity);
    size_t index1 = 0;
    size_t index2 = 0;
    while (index1 < set1.size && index2 < set2.size) {
        if (set1.data[index1] == set2.data[index2]) {
            ordered_array_set_insert(&result, set1.data[index1]);
            index1++;
            index2++;
        } else if (set1.data[index1] < set2.data[index2]) {
            ordered_array_set_insert(&result, set1.data[index1]);
            index1++;
        } else {
            ordered_array_set_insert(&result, set2.data[index2]);
            index2++;
        }
    }
    while (index1 < set1.size) {
        ordered_array_set_insert(&result, set1.data[index1]);
        index1++;
    }
    while (index2 < set2.size) {
        ordered_array_set_insert(&result, set2.data[index2]);
        index2++;
    }
    ordered_array_set_shrinkToFit(&result);
    return result;
}

ordered_array_set intersection (ordered_array_set set1, ordered_array_set set2) {
    ordered_array_set result = ordered_array_set_create(set1.capacity);
    size_t index1 = 0;
    size_t index2 = 0;
    while (index1 < set1.size && index2 < set2.size) {
        if (set1.data[index1] == set2.data[index2]) {
            ordered_array_set_insert(&result, set1.data[index1]);
            index1++;
            index2++;
        } else if (set1.data[index1] < set2.data[index2]) {
            index1++;
        } else {
            index2++;
        }
    }
    ordered_array_set_shrinkToFit(&result);
    return result;
}

ordered_array_set difference (ordered_array_set set1, ordered_array_set set2) {
    ordered_array_set result = ordered_array_set_create(set1.capacity);
    size_t index1 = 0;
    size_t index2 = 0;
    while (index1 < set1.size && index2 < set2.size) {
        if (set1.data[index1] == set2.data[index2]) {
            index1++;
            index2++;
        } else if (set1.data[index1] < set2.data[index2]) {
            ordered_array_set_insert(&result, set1.data[index1]);
            index1++;
        } else {
            index2++;
        }
    }
    while (index1 < set1.size) {
        ordered_array_set_insert(&result, set1.data[index1]);
        index1++;
    }
    ordered_array_set_shrinkToFit(&result);
    return result;
}

ordered_array_set symmetricDifference (ordered_array_set set1, ordered_array_set set2) {
    ordered_array_set result = ordered_array_set_create(set1.capacity + set2.capacity);
    size_t index1 = 0;
    size_t index2 = 0;
    while (index1 < set1.size && index2 < set2.size) {
        if (set1.data[index1] == set2.data[index2]) {
            index1++;
            index2++;
        } else if (set1.data[index1] < set2.data[index2]) {
            ordered_array_set_insert(&result, set1.data[index1]);
            index1++;
        } else {
            ordered_array_set_insert(&result, set2.data[index2]);
            index2++;
        }
    }
    while (index1 < set1.size) {
        ordered_array_set_insert(&result, set1.data[index1]);
        index1++;
    }
    while (index2 < set2.size) {
        ordered_array_set_insert(&result, set2.data[index2]);
        index2++;
    }
    ordered_array_set_shrinkToFit(&result);
    return result;
}

ordered_array_set complement (ordered_array_set set, ordered_array_set universumSet) {
    return difference(universumSet, set);
}

void ordered_array_set_print (ordered_array_set set) {
    if (set.size == 0) {
        printf("Empty set\n");
    } else {
        printf("{");
        for (int i = 0; i < set.size; i++) {
            printf("%d ", set.data[i]);
        }
        printf("\b}\n");
    }
}

void ordered_array_set_delete (ordered_array_set *set) {
    free(set->data);
    set->size = 0;
    set->capacity = 0;
}

#endif
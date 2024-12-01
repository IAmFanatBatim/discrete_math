#ifndef INC_BITSET_C
#define INC_BITSET_C

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

typedef struct bitset {
    uint32_t values; //множество
    uint32_t maxValue; //максимальный элемент универсума
} bitset;

//возвращает пустое множество c универсумом 0, 1,..., maxValue
bitset bitset_create (unsigned maxValue) {
    assert(maxValue < 32);
    return (bitset) {0, maxValue};
}

//возвращает значение ’истина’, если значение value имеется в множестве set, иначе - ’ложь’
bool bitset_in (bitset set, unsigned int value) {
    return set.values & 1 << value;
}

//возвращает значение ’истина’, если множества set1 и set2 равны, иначе - ’ложь’
bool bitset_isEqual (bitset set1, bitset set2) {
    return set1.values == set2.values;
}

//возвращает значение ’истина’ если множество subset является подмножеством множества set, иначе - ’ложь’.
bool bitset_isSubset (bitset subset, bitset set) {
    return set.values == (set.values | subset.values);
}

//добавляет элемент value в множество set
void bitset_insert (bitset *set, unsigned int value) {
    set->values = set->values | 1 << value;
}

//возвращает множество c универсумом 0, 1,..., maxValue и элементами из массива array длины len
bitset bitset_create_from_array (int *array, int len, unsigned maxValue) {
    assert(maxValue < 32);
    bitset result = bitset_create(maxValue);
    for (int i = 0; i < len; i++) {
        assert(array[i] <= maxValue);
        bitset_insert(&result, array[i]);
    }
    return result;
}

//возвращает множество c универсумом 0, 1,..., maxValue и элементами из массива array длины len
bitset bitset_universum_create (unsigned maxValue) {
    assert(maxValue < 32);
    bitset result = bitset_create(maxValue);
    result.values =
    return result;
}

//удаляет элемент value из множества set
void bitset_deleteElement (bitset *set, unsigned int value) {
    set->values = set->values & ~(1 << value);
}

//возвращает объединение множеств set1 и set2
bitset bitset_union (bitset set1, bitset set2) {
    bitset result;
    result.maxValue = (set1.maxValue > set2.maxValue) ? set1.maxValue : set2.maxValue;
    result.values = set1.values | set2.values;
    return result;
}

//возвращает пересечение множеств set1 и set2
bitset bitset_intersection (bitset set1, bitset set2) {
    bitset result;
    result.maxValue = (set1.maxValue > set2.maxValue) ? set1.maxValue : set2.maxValue;
    result.values = set1.values & set2.values;
    return result;
}

//возвращает разность множеств set1 и set2
bitset bitset_difference (bitset set1, bitset set2) {
    bitset result;
    result.maxValue = (set1.maxValue > set2.maxValue) ? set1.maxValue : set2.maxValue;
    result.values = set1.values & ~set2.values;
    return result;
}

//возвращает симметрическую разность множеств set1 и set2
bitset bitset_symmetricDifference (bitset set1, bitset set2) {
    bitset result;
    result.maxValue = (set1.maxValue > set2.maxValue) ? set1.maxValue : set2.maxValue;
    result.values = set1.values ^ set2.values;
    return result;
}

//возвращает дополнение до универсума множества set
bitset bitset_complement (bitset set) {
    bitset result;
    result.maxValue = set.maxValue;
    int unused_bits = set.maxValue;
    int copy_set_values = set.values;
    while (copy_set_values > 0) {
        unused_bits--;
        copy_set_values >>= 1;
    }
    result.values = (~(set.values) << unused_bits) >> unused_bits;
    return result;
}

//вывод множества set
void bitset_print (bitset set) {
    printf ("{");
    if (set.values == 0) {
        printf("}\n");
    } else {
        for (int i = 0; i <= set.maxValue; ++ i) {
            if (bitset_in(set, i)) {
                printf("%d, ", i);
            }
        }
        printf("\b\b}\n");
    }
}

#endif
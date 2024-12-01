#include <stdio.h>
#include "C:\Users\sovac\Desktop\дискретная математика\ЛАБА 1\array_input_output\library.c"
#include <stdbool.h>
#define UNIVERSE_LENGTH 12

typedef struct {
    bool *set;
} bitSet;

const bitSet UNIVERSUM = {{true, true, true, true, true, true, true, true, true, true, true, true}};
const bitSet EMPTY_BIT_SET = {{false, false, false, false, false, false, false, false, false, false, false, false}};
bitSet initBitSet() {
    return EMPTY_BIT_SET;
};

bitSet join(bitSet set_a, bitSet set_b) {
    bitSet result = initBitSet();
    for (int index = 0; index < UNIVERSE_LENGTH; index++) {
        result.set[index] = set_a.set[index] || set_b.set[index];
    }
    return result;
}

bitSet intersection(bitSet set_a, bitSet set_b) {
    bitSet result;
    for (int index = 0; index < UNIVERSE_LENGTH; index++) {
        result.set[index] = set_a.set[index] && set_b.set[index];
    }
    return result;
}

bitSet difference(bitSet set_a, bitSet set_b) {
    bitSet result = {{}};
    for (int index = 0; index < UNIVERSE_LENGTH; index++) {
        result.set[index] = set_a.set[index] && !set_b.set[index];
    }
    return result;
}

bitSet symmetricalDifference(bitSet set_a, bitSet set_b) {
    bitSet result = {{}};
    for (int index = 0; index < UNIVERSE_LENGTH; index++) {
        result.set[index] = set_a.set[index] ^ set_b.set[index];
    }
    return result;
}

bitSet addition(bitSet set_a) {
    return difference(UNIVERSUM, set_a);
}

bool inclusion(bitSet set_a, bitSet set_b) {
    bool is_b_part_of_a = true;
    for (int index = 0; index < UNIVERSE_LENGTH; index++) {
        if (!set_a.set[index] && set_b.set[index]) {
            is_b_part_of_a = false;
            break;
        }
    }
    return is_b_part_of_a;
}

bool equality(bitSet set_a, bitSet set_b) {
    bool are_sets_equal = 1;
    for (int index = 0; index < UNIVERSE_LENGTH; index++) {
        if (set_a.set[index] != set_b.set[index]) {
            are_sets_equal = false;
            break;
        }
    }
    return are_sets_equal;
}

bool strictInclusion(bitSet set_a, bitSet set_b) {
    return inclusion(set_a, set_b) && !equality(set_a, set_b);
}

int main() {
    bitSet a = {{true, true, true, true, true, false, false, false, false, false, false, false}};
    bitSet b = {{true, true, false, false, false, true,false, false, false, false, false, false}};

    bitSet c = join(a, b);

    printArray(c.set, UNIVERSE_LENGTH);
}
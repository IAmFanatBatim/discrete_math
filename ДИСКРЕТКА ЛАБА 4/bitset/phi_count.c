#include "bitset.c"

bitset equation (bitset X, bitset A, bitset B, bitset C) {
    bitset exp1 = bitset_symmetricDifference(A, X);
    bitset exp2 = bitset_union(B, X);
    bitset exp3 = bitset_intersection(exp1, exp2);
    bitset exp4 = bitset_difference(exp3, C);
    bitset exp5 = bitset_union(A, X);
    bitset exp6 = bitset_complement(exp5);
    bitset exp7 = bitset_symmetricDifference(C, X);
    bitset exp8 = bitset_union(exp6, exp7);
    bitset result = bitset_symmetricDifference(exp4, exp8);
    return result;
}

int main() {
    int array_a[5] = {1, 3, 5, 6, 8};
    int array_b[4] = {2, 4, 6, 9};
    int array_c[4] = {2, 6, 7, 10};
    int array_u[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    bitset A = bitset_create_from_array(array_a, 5, 10);
    bitset B = bitset_create_from_array(array_b, 4, 10);
    bitset C = bitset_create_from_array(array_c, 4, 10);
    bitset_print(A);
    bitset_print(B);
    bitset_print(C);
}
#include <stdio.h>
#include "bin_relation_definition_input_output.c"
#include "ABC_forming.c"
#include "bin_relations_operations.c"

bin_relation expression_D_variant6 (bin_relation A, bin_relation B, bin_relation C) {
    bin_relation exp_left = bin_relation_intersection(A, bin_relation_conversion(B));
    bin_relation exp_right = bin_relation_composition(bin_relation_composition(A, C), B);
    bin_relation result = bin_relation_symmetricalDifference(exp_left, exp_right);
    return result;
}

int main() {
    bin_relation A = relation_A_variant6();
    bin_relation B = relation_B_variant6();
    bin_relation C = relation_C_variant6();

    bin_relation D = expression_D_variant6(A, B, C);
    printf("Relation D as matrix: \n");
    bin_relation_matrixPrint(D);
    printf("\nRelation D as list of pairs: \n");
    bin_relation_pairPrint(D);
}

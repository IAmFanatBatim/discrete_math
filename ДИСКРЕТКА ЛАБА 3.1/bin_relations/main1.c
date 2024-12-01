#include <stdio.h>
#include "bin_relation_definition_input_output.c"
#include "ABC_forming.c"


int main() {
    bin_relation A = relation_A_variant6();
    bin_relation B = relation_B_variant6();
    bin_relation C = relation_C_variant6();

    printf("Relation A as matrix: \n");
    bin_relation_matrixPrint(A);
    printf("\nRelation B as matrix: \n");
    bin_relation_matrixPrint(B);
    printf("\nRelation C as matrix: \n");
    bin_relation_matrixPrint(C);
}

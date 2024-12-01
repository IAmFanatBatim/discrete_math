#include <stdio.h>
#include "bin_relation_definition_input_output.c"
#include "ABC_forming.c"
#include "bin_relations_properties.c"


int main() {
    bin_relation A = relation_A_variant6();
    bin_relation B = relation_B_variant6();
    bin_relation C = relation_C_variant6();

    bin_relation I = bin_relation_createEmpty(4); //Можно заменить значение max_value на 1, чтобы увидеть, какие свойства при этом меняются
    for (int x = 1; x <= I.max_value; x++) {
        bin_relation_changeValue(&I, x, x, 1);
    }

    printf("All properties of relation A: \n");
    bin_relation_print_all_properties(A);
    printf("\nAll properties of relation B: \n");
    bin_relation_print_all_properties(B);
    printf("\nAll properties of relation C: \n");
    bin_relation_print_all_properties(C);


    printf("\nAll properties of relation I with power of set = %d: \n", I.max_value);
    bin_relation_print_all_properties(I);
}

#include "bin_relation_definition_input_output.c"

//Возвращает отношение A, заданное условием варианта 6 лабораторной работы 3.1 (см. "Варианты заданий", пункт а))
bin_relation relation_A_variant6 () {
    bin_relation A = bin_relation_createEmpty(10);
    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= 10; j++) {
            if (i + j > 8 && (i + j) % 2 == 0) {
                bin_relation_changeValue(&A, i, j, 1);
            }
        }
    }
    return A;
}

//Возвращает отношение B, заданное условием варианта 6 лабораторной работы 3.1 (см. "Варианты заданий", пункт а))
bin_relation relation_B_variant6 () {
    bin_relation B = bin_relation_createEmpty(10);
    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= 10; j++) {
            if (i + 2*j > 20) {
                bin_relation_changeValue(&B, i, j, 1);
            }
        }
    }
    return B;
}

//Возвращает отношение С, заданное условием варианта 6 лабораторной работы 3.1 (см. "Варианты заданий", пункт а))
bin_relation relation_C_variant6 () {
    bin_relation C = bin_relation_createEmpty(10);
    int c1[4] = {1, 2, 4, 8};
    int c2[4] = {3, 5, 7, 10};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            bin_relation_changeValue(&C, c1[i], c2[j], 1);
        }
    }
    return C;
}

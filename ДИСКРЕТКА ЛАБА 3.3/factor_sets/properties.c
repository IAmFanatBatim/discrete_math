#include "../../ДИСКРЕТКА ЛАБА 3.1/bin_relations/bin_relations_properties.c"

int main() {
    bin_relation A = bin_relation_createEmpty(10);
    for (int x = 1; x <= 10; x++) {
        for (int y = 1; y <= 10; y++) {
            if (abs(x-y) % 2 == 0) {
                bin_relation_changeValue(&A, x, y, 1);
            }
        }
    }
    bin_relation_print_all_properties(A);
}

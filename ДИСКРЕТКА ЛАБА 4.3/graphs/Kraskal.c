#include "../../ДИСКРЕТКА ЛАБА 3.1/bin_relations/bin_relation_definition_input_output.c"
#include "../../ДИСКРЕТКА ЛАБА 3.1/bin_relations/bin_relations_operations.c"
#include "../../ДИСКРЕТКА ЛАБА 4.1/matrix/matrix.c"

typedef bin_relation graph;


graph graph_coveringByKraskal(graph A) {
    graph KraskalForest = bin_relation_createEmpty(A.max_value);
    int bunches[A.max_value];
    for (int i = 0; i < A.max_value; i++) {
        bunches[i] = i+1;
    }
    for (int i = 1; i <= A.max_value; i++) {
        for (int j = 1; j <= A.max_value; j++) {
            if (bin_relation_getValue(A, i, j) && bunches[i-1] != bunches[j-1]) {
                bin_relation_changeValue(&KraskalForest, i, j, 1);
                bin_relation_changeValue(&KraskalForest, j, i, 1);
                int bunch_i = bunches[i-1];
                for (int k = 0; k < A.max_value; k++) {
                   if (bunches[k] == bunch_i) {
                       bunches[k] = bunches[j-1];
                   }
                }
            }
        }
    }
    return KraskalForest;
}
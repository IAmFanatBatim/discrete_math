#include "../../ДИСКРЕТКА ЛАБА 3.1/bin_relations/bin_relation_definition_input_output.c"
#include "../../ДИСКРЕТКА ЛАБА 3.1/bin_relations/bin_relations_operations.c"
#include "../../ДИСКРЕТКА ЛАБА 4.1/matrix/matrix.c"

#include <assert.h>

typedef bin_relation graph;

graph graph_createFromMatrix(matrix M) {
    graph result = bin_relation_createEmpty(M.nRows);
    for (int i = 1; i <= M.nRows; i++) {
        for (int j = 1; j <= M.nRows; j++) {
            bin_relation_changeValue(&result, i, j, M.values[i-1][j - 1]);
        }
    }
    return result;
}

typedef struct {
    int max_amount;
    int *vertexes;
    int cur_amount;
} bunch;

void bunch_createFor(bunch *B, graph G) {
    B->max_amount = G.max_value;
    B->vertexes = malloc(G.max_value * sizeof(int));
    B->cur_amount = 0;
}

void bunch_addVert(bunch *B, int vert) {
    assert(B->cur_amount < B->max_amount);
    B->vertexes[B->cur_amount] = vert;
    B->cur_amount++;
}

int bunch_isVertIn(bunch *B, int vert) {
    for (int i = 0; i < B->cur_amount; i++) {
        if (B->vertexes[i] == vert) {
            return 1;
        }
    }
    return 0;
}

void bunch_Merge(bunch *B1, bunch *B2) {
    for (int i = 0; i < B2->cur_amount; i++) {
        if (bunch_isVertIn(B1, B2->vertexes[i])) {
            bunch_addVert(B1, B2->vertexes[i]);
        }
    }
}

graph graph_coveringByKraskal(graph A) {
    graph KraskalForest = bin_relation_createEmpty(A.max_value);
    bunch bunches[A.max_value];
    for (int i = 1; i <= A.max_value; i++) {
        bunch_createFor(bunches + i-1, A);
        bunch_addVert(bunches + i-1, i);
    }
    int bunch_array_len = A.max_value;
    for (int i = 1; i <= A.max_value; i++) {
        for (int j = 1; j <= A.max_value; j++) {
            if (bin_relation_getValue(A, i, j)) {
                int bunch_num_i = 0;
                int bunch_num_j = 0;
                for (int k = 0; k < bunch_array_len; k++) {
                    if (bunch_isVertIn(bunches+ k, i)) {
                        bunch_num_i = k;
                    }
                    if (bunch_isVertIn(bunches+ k, j)) {
                        bunch_num_j = k;
                    }
                }
                if (bunch_num_i != bunch_num_j) {
                    bin_relation_changeValue(&KraskalForest, i, j, 1);
                    bin_relation_changeValue(&KraskalForest, j, i, 1);
                    bunch_Merge(bunches + bunch_num_i, bunches + bunch_num_j);
                    bunches[bunch_num_j] = bunches[bunch_array_len-1];
                    bunch_array_len--;
                }
            }
        }
    }
    return KraskalForest;
}

int main() {
    matrix M1 = createMatrixFromArray((int[]) {
        0, 1, 0, 0, 1, 1,
        1, 0, 0, 1, 1, 0,
        0, 0, 0, 1, 0, 0,
        0, 1, 1, 0, 1, 0,
        1, 1, 0, 1, 0, 0,
        1, 0, 0, 0, 0, 0
    }, 6, 6);
    graph G1 = graph_createFromMatrix(M1);
    graph covering1 = graph_coveringByKraskal(G1);
    bin_relation_matrixPrint(covering1);
}
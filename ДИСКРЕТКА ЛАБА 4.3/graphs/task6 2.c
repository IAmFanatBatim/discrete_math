#include "../../ДИСКРЕТКА ЛАБА 3.1/bin_relations/bin_relation_definition_input_output.c"
#include "../../ДИСКРЕТКА ЛАБА 3.1/bin_relations/bin_relations_operations.c"
#include "../../ДИСКРЕТКА ЛАБА 4.1/matrix/matrix.c"

#include "Kraskal.c"

int graph_getAmountOfEdges(graph A, graph *K) {
    *K = bin_relation_createEmpty(A.max_value);
    int edges_counter = 0;
    int bunches[A.max_value];
    for (int i = 0; i < A.max_value; i++) {
        bunches[i] = i+1;
    }
    for (int i = 1; i <= A.max_value; i++) {
        for (int j = 1; j <= A.max_value; j++) {
            if (bin_relation_getValue(A, i, j) && bunches[i] != bunches[j]) {
                bin_relation_changeValue(K, i, j, 1);
                bin_relation_changeValue(K, j, i, 1);
                edges_counter++;
                for (int k = 0; k < A.max_value; k++) {
                    if (bunches[k] == bunches[i]) {
                        bunches[k] = bunches[j];
                    }
                }
            }
        }
    }
    return edges_counter;
}

bool isInSequence(int *W, int n, int value) {
    for (int j = 0; j < n; j++) {
        if (W[j] == value) {
            return true;
        }
    }
    return false;
}

void printSequence(int *W, int n) {
    printf("(");
    for (int j = 0; j < n; j++) {
        printf("%d, ", W[j]);
    }
    printf("\b\b)\t");
}

int amountOfIsolated(graph A) {
    int result = 0;
    for (int i = 1; i <= A.max_value; i++) {
        if (A.values[i-1] == 0) {
            result++;
        }
    }
    return result;
}

void deleteVert(graph *A, int vert) {
    for (int cur_vert = 1; cur_vert <= A->max_value; cur_vert++) {
        bin_relation_changeValue(A, cur_vert, vert, 0);
        bin_relation_changeValue(A, vert, cur_vert, 0);
    }
}

void vertexesToSplitGraphInTwo_(graph G, int *W, int cur_pos) {
    for (int cur_el = 1; cur_el <= G.max_value; cur_el++) {
        if (bin_relation_getValue(G, W[cur_pos−1], cur_el) &&
        !isInSequence(W, cur_pos, cur_el))
    for (int vector_of_set = 1; vector_of_set < 1<<A.max_value; vector_of_set++) {
        graph copyA = A;
        graph coveringA;
        deleteVerts(&copyA, vector_of_set);
        //printVectorOfVerts(vector_of_set);
        //bin_relation_matrixPrint(copyA);
        //printf("\n");

        int cur_amount = graph_getAmountOfEdges(A, &coveringA);
        if (cur_amount == A.max_value - 2 && amountOfIsolated(A) == A.max_value - amountOfVertsInVector(vector_of_set)) {
            printf("Here!");
            printVectorOfVerts(vector_of_set);
        }
    }
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
    vertexesToSplitGraphInTwo(G1);
}
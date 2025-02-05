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

void printVectorOfVerts(int vector) {
    int cur_vert = 1;
    while (vector > 0) {
        if (vector & 1) {
            printf("%d ", cur_vert);
        }
        cur_vert++;
        vector >>= 1;
    }
    printf("\n");
}

int amountOfVertsInVector(int vector) {
    int result = 0;
    while (vector > 0) {
        if (vector & 1) {
            result++;
        }
        vector >>= 1;
    }
    return result;
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

void deleteVerts(graph *A, int vector) {
    int cur_vert = 1;
    while (vector > 0) {
        if (vector & 1) {
            for (int i = 1; i <= A->max_value; i++) {
                bin_relation_changeValue(A, cur_vert, i, 0);
                bin_relation_changeValue(A, i, cur_vert, 0);
            }
        }
        cur_vert++;
        vector >>= 1;
    }
}

void vertexesToSplitGraphInTwo(graph A) {
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
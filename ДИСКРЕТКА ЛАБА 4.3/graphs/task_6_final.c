#include "../../ДИСКРЕТКА ЛАБА 3.1/bin_relations/bin_relation_definition_input_output.c"
#include "../../ДИСКРЕТКА ЛАБА 3.1/bin_relations/bin_relations_operations.c"
#include "../../ДИСКРЕТКА ЛАБА 4.1/matrix/matrix.c"

#include "Kraskal.c"

void printSequence(int *W, int n) {
    printf("(");
    for (int j = 0; j < n; j++) {
        printf("%d, ", W[j]);
    }
    printf("\b\b)\t");
}

bool isInSequence(int *W, int n, int value) {
    for (int j = 0; j < n; j++) {
        if (W[j] == value) {
            return true;
        }
    }
    return false;
}

void getSequenceByVector(int vector, int *W, int *n) {
    int cur_vert = 1;
    (*n) = 0;
    while (vector > 0) {
        if (vector & 1) {
           W[*n] = cur_vert;
            (*n)++;
        }
        cur_vert++;
        vector >>= 1;
    }
}

graph formGraphWithoutVertex (graph A, int *W, int n) {
    graph B = bin_relation_createEmpty(A.max_value);
    for (int i = 1; i <= A.max_value; i++) {
        for (int j = 1; j <= A.max_value; j++) {
            if (!isInSequence(W, n, i) && !isInSequence(W, n, j)) {
                bin_relation_changeValue(&B, i, j, bin_relation_getValue(A, i, j));
                bin_relation_changeValue(&B, j, i, bin_relation_getValue(A, j, i));
            }
        }
    }
    return B;
}

int count_edges(graph G) {
    int result = 0;
    for (int i = 1; i <= G.max_value; i++) {
        for (int j = i+1; j<= G.max_value; j++) {
            result += bin_relation_getValue(G, i, j);
        }
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

void vertexesToSplitGraphInTwo(graph A) {
    int W[A.max_value];
    int n;
    for (int vector_of_set = 1; vector_of_set < (1<<A.max_value)-1; vector_of_set++) {
        getSequenceByVector(vector_of_set, W, &n);
        if (A.max_value - n >= 4) {
            graph copyA = formGraphWithoutVertex(A, W, n);
            graph covering_copyA = graph_coveringByKraskal(copyA);

            if (count_edges(covering_copyA) == A.max_value - 2 - n && amountOfIsolated(copyA) == n) {
                printSequence(W, n);
            }
        }
    }
}
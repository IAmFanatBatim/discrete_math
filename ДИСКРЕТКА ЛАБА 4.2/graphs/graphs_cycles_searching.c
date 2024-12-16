
#include "../../ДИСКРЕТКА ЛАБА 3.1/bin_relations/bin_relation_definition_input_output.c"
#include "../../ДИСКРЕТКА ЛАБА 3.1/bin_relations/bin_relations_operations.c"
#include "../../ДИСКРЕТКА ЛАБА 3.1/bin_relations/bin_relations_properties.c"
#include "../../ДИСКРЕТКА ЛАБА 4.1/matrix/matrix.c"
#include <stdbool.h>

typedef bin_relation graph;

bool isInSequence(int *W, int n, int value) {
    for (int j = 0; j < n; j++) {
        if (W[j] == value) {
            return true;
        }
    }
    return false;
}

graph graph_createFromMatrix(matrix M) {
    graph result = bin_relation_createEmpty(M.nRows);
    for (int i = 1; i <= M.nRows; i++) {
        for (int j = 1; j <= M.nRows; j++) {
            bin_relation_changeValue(&result, i, j, M.values[i-1][j - 1]);
        }
    }
    return result;
}

void printSequence(int *W, int n) {
    printf("(");
    for (int cur_ind = 0; cur_ind < n; cur_ind++) {
        printf("%d, ", W[cur_ind]);
    }
    printf("\b\b)\t");
}

void graph_allHamiltonCycles_(graph G, int *W, int cur_pos) {
    for (int cur_el = 1; cur_el <= G.max_value; cur_el++) {
        if (bin_relation_getValue(G, W[cur_pos-1], cur_el) && !isInSequence(W, cur_pos, cur_el)) {
            W[cur_pos] = cur_el;
            if (cur_pos + 1 == G.max_value) {
                if (bin_relation_getValue(G, cur_el, W[0])) {
                    W[cur_pos+1] = W[0];
                    printSequence(W, cur_pos + 2);
                }
            } else {
                graph_allHamiltonCycles_(G, W, cur_pos + 1);
            }
        }
    }
}

void graph_allHamiltonCycles(graph G) {
    int W[G.max_value + 1];
    for (int cur_start_el = 1; cur_start_el <= G.max_value; cur_start_el++) {
        W[0] = cur_start_el;
        graph_allHamiltonCycles_(G, W, 1);
    }
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

void graph_allEulerCycles_(graph G, int *W, bin_relation E, int cur_pos) {
    for (int cur_el = 1; cur_el <= G.max_value; cur_el++) {
        if (bin_relation_getValue(G, W[cur_pos-1], cur_el) && !bin_relation_getValue(E, cur_el, W[cur_pos-1])) {
            bin_relation_changeValue(&E, cur_el, W[cur_pos-1], 1);
            bin_relation_changeValue(&E, W[cur_pos-1], cur_el, 1);
            W[cur_pos] = cur_el;
            if (cur_pos + 1 == count_edges(G)) {
                if (bin_relation_getValue(G, cur_el, W[0]) && !bin_relation_getValue(E, cur_el, W[0])) {
                    W[cur_pos+1] = W[0];
                    printSequence(W, cur_pos + 2);
                }
            } else {
                graph_allEulerCycles_(G, W, E, cur_pos + 1);
            }
            bin_relation_changeValue(&E, cur_el, W[cur_pos-1], 0);
            bin_relation_changeValue(&E, W[cur_pos-1], cur_el, 0);
        }
    }
}

void graph_allEulerCycles(graph G) {
    bin_relation E = bin_relation_createEmpty(G.max_value);
    int W[count_edges(G) + 1];
    for (int cur_start_el = 1; cur_start_el <= G.max_value; cur_start_el++) {
        W[0] = cur_start_el;
        graph_allEulerCycles_(G, W, E, 1);
    }
}

int main () {
    matrix M1 = createMatrixFromArray((int[25]) {
            0, 1, 1, 0, 0,
            1, 0, 1, 1, 1,
            1, 1, 0, 0, 0,
            0, 1, 0, 0, 1,
            0, 1, 0, 1,  0
    }, 5, 5);
    graph G1 = graph_createFromMatrix(M1);
    printf("\n\nAll Hamilton cycles for G1:\n");
    graph_allHamiltonCycles(G1);
    printf("\nAll Euler cycles for G1:\n");
    graph_allEulerCycles(G1);

    matrix M2 = createMatrixFromArray((int[25]) {
            0, 0, 1, 0, 1,
            0, 0, 0, 1, 1,
            1, 0, 0, 1, 0,
            0, 1, 1, 0, 1,
            1, 1, 0, 1,  0
    }, 5, 5);
    graph G2 = graph_createFromMatrix(M2);
    printf("\n\nAll Hamilton cycles for G2:\n");
    graph_allHamiltonCycles(G2);
    printf("\nAll Euler cycles for G2:\n");
    graph_allEulerCycles(G2);

    matrix M3 = createMatrixFromArray((int[25]) {
            0, 1, 0, 0, 1,
            1, 0, 1, 0, 0,
            0, 1, 0, 1, 0,
            0, 0, 1, 0, 1,
            1, 0, 0, 1, 0
    }, 5, 5);
    graph G3 = graph_createFromMatrix(M3);
    printf("\n\nAll Hamilton cycles for G3:\n");
    graph_allHamiltonCycles(G3);
    printf("\nAll Euler cycles for G3:\n");
    graph_allEulerCycles(G3);

    matrix M4 = createMatrixFromArray((int[25]) {
            0, 1, 0, 0, 0,
            1, 0, 1, 1, 1,
            0, 1, 0, 1, 0,
            0, 1, 1, 0, 0,
            0, 1, 0, 0, 0
    }, 5, 5);
    graph G4 = graph_createFromMatrix(M4);
    printf("\n\nAll Hamilton cycles for G4:\n");
    graph_allHamiltonCycles(G4);
    printf("\nAll Euler cycles for G4:\n");
    graph_allEulerCycles(G4);
}
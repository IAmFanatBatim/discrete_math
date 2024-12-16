#include "../../ДИСКРЕТКА ЛАБА 3.1/bin_relations/bin_relation_definition_input_output.c"
#include "../../ДИСКРЕТКА ЛАБА 3.1/bin_relations/bin_relations_operations.c"
#include "../../ДИСКРЕТКА ЛАБА 3.1/bin_relations/bin_relations_properties.c"
#include "../matrix/matrix.c"

#include <stdbool.h>

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

bool isSequenceRoute(graph G, int *s, int n) {
    bool result = s[0] <= G.max_value;
    for (int vert_ind = 1; vert_ind < n && result; vert_ind++) {
        if (s[vert_ind] > G.max_value || !bin_relation_getValue(G, s[vert_ind], s[vert_ind-1])) {
            result = false;
        }
    }
    return result;
}

bool isSequenceChain(graph G, int *s, int n) {
    bool result = s[0] <= G.max_value;
    graph passed_edges = bin_relation_createEmpty(G.max_value);
    for (int vert_ind = 1; vert_ind < n && result; vert_ind++) {
        bool cond1 = s[vert_ind] > G.max_value;
        bool cond2 = !bin_relation_getValue(G, s[vert_ind], s[vert_ind-1]);
        bool cond3 = bin_relation_getValue(passed_edges, s[vert_ind], s[vert_ind-1]);
        if (cond1 || cond2 || cond3) {
            result = false;
        } else {
            bin_relation_changeValue(&passed_edges, s[vert_ind], s[vert_ind-1], 1);
            bin_relation_changeValue(&passed_edges, s[vert_ind-1], s[vert_ind], 1);
        }
    }
    return result;
}

bool isSequenceSimpleChain(graph G, int *s, int n) {
    bool result = s[0] <= G.max_value;
    int V_array[n];
    V_array[0] = s[0];
    for (int vert_ind = 1; vert_ind < n && result; vert_ind++) {
        if (s[vert_ind] > G.max_value || !bin_relation_getValue(G, s[vert_ind], s[vert_ind-1])) {
            result = false;
        } else {
            V_array[vert_ind] = s[vert_ind];
            for (int vert_ind2 = 0; vert_ind2 < vert_ind-1; vert_ind2++) {
                if (V_array[vert_ind2] == V_array[vert_ind] && !(vert_ind2 == 0 && vert_ind == n-1)) {
                    result = false;
                }
            }
        }
    }
    return result;
}

bool isSequenceCycle(graph G, int *s, int n) {
    return isSequenceChain(G, s, n) && s[0] == s[n-1];
}

bool isSequenceSimpleCycle(graph G, int *s, int n) {
    return isSequenceSimpleChain(G, s, n) && s[0] == s[n-1];
}

void printSequenceProperties(graph G, int *s, int n) {
    printf("This sequence is: ");
    if (isSequenceRoute(G, s, n)) {
        printf("route, ");
    } else {
        printf("not route, ");
    }
    if (isSequenceChain(G, s, n)) {
        printf("chain, ");
    } else {
        printf("not chain, ");
    }
    if (isSequenceSimpleChain(G, s, n)) {
        printf("simple chain, ");
    } else {
        printf("not simple chain, ");
    }
    if (isSequenceCycle(G, s, n)) {
        printf("cycle, ");
    } else {
        printf("not cycle, ");
    }
    if (isSequenceSimpleCycle(G, s, n)) {
        printf("simple cycle.\n");
    } else {
        printf("not simple cycle.\n");
    }
}

void printSequence(int *W, int n) {
    printf("(");
    for (int cur_ind = 0; cur_ind < n; cur_ind++) {
        printf("%d, ", W[cur_ind]);
    }
    printf("\b\b)\t");
}

void allRoutesWithLenFromVert_(graph G, int len, int *W, int cur_pos) {
    for (int cur_el = 1; cur_el <= G.max_value; cur_el++) {
        if (bin_relation_getValue(G, W[cur_pos-1], cur_el)) {
            W[cur_pos] = cur_el;
            if (cur_pos == len) {
                printSequence(W, len+1);
            } else {
                allRoutesWithLenFromVert_(G, len, W, cur_pos+1);
            }
        }
    }
}

void allRoutesWithLenFromVert(graph G, int len, int vert) {
    int W[G.max_value];
    W[0] = vert;
    allRoutesWithLenFromVert_(G, len, W, 1);
}

void allRoutesWithLen(graph G, int len) {
    for (int cur_start_el = 1; cur_start_el <= G.max_value; cur_start_el++) {
        allRoutesWithLenFromVert(G, len, cur_start_el);
        printf("\n");
    }
}

void getMatrixOfRoutesAmount(graph G, int len, matrix *M) {
    matrix result = getMemMatrix(G.max_value, G.max_value);
    for (int row_ind = 0; row_ind < G.max_value; row_ind++) {
        for (int col_ind = 0; col_ind < G.max_value; col_ind++) {
            result.values[row_ind][col_ind] = bin_relation_getValue(G, row_ind+1, col_ind+1);
            M->values[row_ind][col_ind] = bin_relation_getValue(G, row_ind+1, col_ind+1);
        }
    }
    for (int degree = 1; degree < len; degree++) {
        for (int row_ind = 0; row_ind < G.max_value; row_ind++) {
            for (int col_ind = 0; col_ind < G.max_value; col_ind++) {
                M->values[row_ind][col_ind] = 0;
                for (int summand_ind = 0; summand_ind < G.max_value; summand_ind++) {
                    M->values[row_ind][col_ind] += result.values[row_ind][summand_ind] * bin_relation_getValue(G, summand_ind + 1, col_ind + 1);
                }
            }
        }
        for (int row_ind = 0; row_ind < G.max_value; row_ind++) {
            for (int col_ind = 0; col_ind < G.max_value; col_ind++) {
                result.values[row_ind][col_ind] = M->values[row_ind][col_ind];
            }
        }
    }
}

void allRoutesWithLenFromVertToVert_(graph G, int len, int vert2, int *W, int cur_pos) {
    for (int cur_el = 1; cur_el <= G.max_value; cur_el++) {
        if (bin_relation_getValue(G, W[cur_pos-1], cur_el)) {
            W[cur_pos] = cur_el;
            if (cur_pos == len) {
                if (cur_el == vert2) {
                    printSequence(W, len+1);
                }
            } else {
                allRoutesWithLenFromVertToVert_(G, len, vert2, W, cur_pos+1);
            }
        }
    }
}

void allRoutesWithLenFromVertToVert(graph G, int len, int vert, int vert2) {
    int W[G.max_value];
    W[0] = vert;
    allRoutesWithLenFromVertToVert_(G, len, vert2, W, 1);
}

bool isInSequence(int *W, int n, int value) {
    for (int j = 0; j < n; j++) {
        if (W[j] == value) {
            return true;
        }
    }
    return false;
}

void allMaxSimpleChainsFromVert_(graph G, int *W, int cur_pos) {
    for (int cur_el = 1; cur_el <= G.max_value; cur_el++) {
        if (bin_relation_getValue(G, W[cur_pos-1], cur_el) && !isInSequence(W, cur_pos, cur_el)) {
            W[cur_pos] = cur_el;
            bool final_flag = true;
            for (int k = 1; k <= G.max_value; k++) {
                final_flag *= !bin_relation_getValue(G, k, cur_el) || isInSequence(W, cur_pos, k);
            }
            if (final_flag) {
                printSequence(W, cur_pos+1);
            } else {
                allMaxSimpleChainsFromVert_(G, W, cur_pos+1);
            }
        }
    }
}

void allMaxSimpleChainsFromVert(graph G, int vert) {
    int W[G.max_value], V[G.max_value];
    W[0] = vert;
    allMaxSimpleChainsFromVert_(G, W, 1);
}

int main () {
    matrix M1 = createMatrixFromArray(
            (int[]) {
                0, 1, 0, 1, 0, 1, 1,
	 	        1, 0, 1, 1, 0, 0, 0,
	 	        0, 1, 0, 1, 1, 1, 0,
	 	        1, 1, 1, 0, 0, 0, 0,
	 	        0, 0, 1, 0, 0, 1, 0,
	 	        1, 0, 1, 0, 1, 0, 1,
	 	        1, 0, 0, 0, 0, 1, 0
            },7, 7
    );
    matrix M2 = createMatrixFromArray(
            (int[]) {
                0, 1, 0, 0, 0, 0, 1,
                1, 0, 0, 0, 0, 1, 0,
                0, 0, 0, 1, 0, 1, 0,
                0, 0, 1, 0, 1, 0, 0,
                0, 0, 0, 1, 0, 1, 0,
                0, 1, 1, 0, 1, 0, 1,
                1, 0, 0, 0, 0, 1, 0
            }, 7, 7
    );

    graph G1 = graph_createFromMatrix(M1);
    graph G2 = graph_createFromMatrix(M2);

    int sequence1[5] = {1, 7, 6, 3, 5};
    int sequence2[6] = {6, 5, 3, 6, 7, 1};
    int sequence3[6] = {7, 6, 3, 2, 1, 7};
    int sequence4[6] = {4, 3, 5, 3, 6, 5};
    int sequence5[6] = {1, 2, 7, 6, 2, 1};

    int *sequences[5] = {sequence1, sequence2, sequence3, sequence4, sequence5};
    int lens[5] = {5, 6, 6, 6, 6};

    for (int i = 0; i < 5; i++) {
        printf("Sequence No %d, for G1:\n", i+1);
        printSequenceProperties(G1, sequences[i], lens[i]);
        printf("Sequence No %d for G2:\n", i+1);
        printSequenceProperties(G2, sequences[i], lens[i]);
        printf("\n");
    }

    printf("All routes with len 1, for G1:\n");
    allRoutesWithLen(G1, 1);
    printf("All routes with len 2, for G2:\n");
    allRoutesWithLen(G2, 2);
    printf("\n");

    matrix routes = getMemMatrix(7, 7);
    printf("Matrix of the number of paths with length 2 between vertices, for G2:\n");
    getMatrixOfRoutesAmount(G2, 2, &routes);
    outputMatrix(routes);
    printf("Matrix of the number of paths with length 3 between vertices, for G2:\n");
    getMatrixOfRoutesAmount(G2, 3, &routes);
    outputMatrix(routes);

    printf("\nAll routes with len 2 from vertex 3 to vertex 5, for G2:\n");
    allRoutesWithLenFromVertToVert(G2, 2, 3, 5);
    printf("\nAll routes with len 3 from vertex 6 to vertex 5, for G2:\n");
    allRoutesWithLenFromVertToVert(G2, 3, 6, 5);
    printf("\n");

    printf("\nAll ax simple chains from vertex 2, for G1:\n");
    allMaxSimpleChainsFromVert(G1, 2);
    printf("\nAll ax simple chains from vertex 2, for G2:\n");
    allMaxSimpleChainsFromVert(G2, 2);
}
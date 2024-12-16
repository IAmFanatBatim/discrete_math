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

int main () {
    matrix fullM = createMatrixFromArray(
            (int[]) {
                0, 1, 1, 1, 1, 1, 1,
	 	        1, 0, 1, 1, 1, 1, 1,
                 1, 1, 0, 1, 1, 1, 1,
	 	        1, 1, 1, 0, 1, 1, 1,
	 	        1, 1, 1, 1, 0, 1, 1,
	 	        1, 1, 1, 1, 1, 0, 1,
	 	        1, 1, 1, 1, 1, 1, 0
            },7, 7
    );

    graph fullG = graph_createFromMatrix(fullM);

    matrix routes = getMemMatrix(7, 7);
    printf("Matrix of the number of paths with length 2 between vertices, for fullG:\n");
    getMatrixOfRoutesAmount(fullG, 2, &routes);
    outputMatrix(routes);
    printf("Matrix of the number of paths with length 5 between vertices, for fullG:\n");
    getMatrixOfRoutesAmount(fullG, 4, &routes);
    outputMatrix(routes);
}
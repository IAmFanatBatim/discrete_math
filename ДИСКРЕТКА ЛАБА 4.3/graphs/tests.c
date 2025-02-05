#include "../../ДИСКРЕТКА ЛАБА 3.1/bin_relations/bin_relation_definition_input_output.c"
#include "../../ДИСКРЕТКА ЛАБА 3.1/bin_relations/bin_relations_operations.c"
#include "../../ДИСКРЕТКА ЛАБА 4.1/matrix/matrix.c"

#include "task_6_final.c"

graph graph_createFromMatrix(matrix M) {
    graph result = bin_relation_createEmpty(M.nRows);
    for (int i = 1; i <= M.nRows; i++) {
        for (int j = 1; j <= M.nRows; j++) {
            bin_relation_changeValue(&result, i, j, M.values[i-1][j - 1]);
        }
    }
    return result;
}

int main() {
    matrix M1 = createMatrixFromArray((int[]) {
        0, 1, 0, 0, 0, 0,
        1, 0, 1, 0, 0, 0,
        0, 1, 0, 1, 0, 0,
        0, 0, 1, 0, 1, 0,
        0, 0, 0, 1, 0, 1,
        0, 0, 0, 0, 1, 0
    }, 6, 6);
    graph G1 = graph_createFromMatrix(M1);
    printf("Sets of vertexes, which deletion split graph G1 in two components, without isolated vertexes:\n");
    vertexesToSplitGraphInTwo(G1);
    printf("\n");

    matrix M2 = createMatrixFromArray((int[]) {
            0, 1, 0, 0, 0, 0, 0,
            1, 0, 1, 0, 0, 0, 0,
            0, 1, 0, 1, 0, 1, 0,
            0, 0, 1, 0, 1, 0, 0,
            0, 0, 0, 1, 0, 0, 0,
            0, 0, 1, 0, 0, 0, 1,
            0, 0, 0, 0, 0, 1, 0
    }, 7, 7);
    graph G2 = graph_createFromMatrix(M2);
    printf("Sets of vertexes, which deletion split graph G2 in two components, without isolated vertexes:\n");
    vertexesToSplitGraphInTwo(G2);
    printf("\n");

    matrix M3 = createMatrixFromArray((int[]) {
            0, 1, 1, 0, 0,
            1, 0, 1, 0, 0,
            1, 1, 0, 1, 0,
            0, 0, 1, 0, 1,
            0, 0, 0, 1, 0,
            0, 0, 0, 0, 1
    }, 5, 5);
    graph G3 = graph_createFromMatrix(M3);
    printf("Sets of vertexes, which deletion split graph G3 in two components, without isolated vertexes:\n");
    vertexesToSplitGraphInTwo(G3);
    printf("\n");

    matrix M4 = createMatrixFromArray((int[]) {
            0, 1, 1, 0, 0, 0,
            1, 0, 0, 1, 0, 0,
            1, 0, 0, 1, 0, 0,
            0, 1, 1, 0, 1, 1,
            0, 0, 0, 1, 0, 1,
            0, 0, 0, 1, 1, 0
    }, 6, 6);
    graph G4 = graph_createFromMatrix(M4);
    printf("Sets of vertexes, which deletion split graph G4 in two components, without isolated vertexes:\n");
    vertexesToSplitGraphInTwo(G4);
    printf("\n");


    matrix M5 = createMatrixFromArray((int[]) {
            0, 1, 1, 0, 0, 0,
            1, 0, 1, 1, 0, 0,
            1, 1, 0, 0, 1, 0,
            0, 1, 0, 0, 1, 1,
            0, 0, 1, 1, 0, 1,
            0, 0, 0, 1, 1, 0
    }, 6, 6);
    graph G5 = graph_createFromMatrix(M5);
    printf("Sets of vertexes, which deletion split graph G5 in two components, without isolated vertexes:\n");
    vertexesToSplitGraphInTwo(G5);
    printf("\n");
}
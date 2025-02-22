#include "../../ДИСКРЕТКА ЛАБА 3.1/bin_relations/bin_relation_definition_input_output.c"
#include "../../ДИСКРЕТКА ЛАБА 3.1/bin_relations/bin_relations_operations.c"
#include "../../ДИСКРЕТКА ЛАБА 3.1/bin_relations/bin_relations_properties.c"
#include <stdbool.h>
#include <sys/time.h>

typedef bin_relation graph;

graph graph_generate(int n, int m) {
    graph result = bin_relation_createEmpty(n);
    int ones_amount = m;
    int zeros_amount = n*(n-1)/2 - m;
    for (int i = 1; i <= n; i++) {
        for (int j = i+1; j<= n; j++) {
            int value = (ones_amount == 0) ? 0 : ((zeros_amount == 0) ? 1 : rand() % 2);
            bin_relation_changeValue(&result, i, j, value);
            bin_relation_changeValue(&result, j, i, value);
            if (value == 1) {
                ones_amount--;
            } else {
                zeros_amount--;
            }
        }
    }
    return result;
}

bool isInSequence(int *W, int n, int value) {
    for (int j = 0; j < n; j++) {
        if (W[j] == value) {
            return true;
        }
    }
    return false;
}

bool graph_isHamilton_(graph G, int *W, int cur_pos, bool result) {
    for (int cur_el = 1; cur_el <= G.max_value && !result; cur_el++) {
        if (bin_relation_getValue(G, W[cur_pos-1], cur_el) && !isInSequence(W, cur_pos, cur_el)) {
            W[cur_pos] = cur_el;
            if (cur_pos + 1 == G.max_value) {
                if (bin_relation_getValue(G, cur_el, W[0])) {
                    result = 1;
                }
            } else {
                result = graph_isHamilton_(G, W, cur_pos + 1, result);
            }
        }
    }
    return result;
}

bool graph_isHamilton(graph G) {
    int W[G.max_value];
    W[0] = 1;
    return graph_isHamilton_(G, W, 1, 0);
}

bin_relation transitive_closure(bin_relation A) {
    bin_relation C =A;
    bin_relation C2 = bin_relation_composition(C,C);
    while(!bin_relation_inclusion(C2,C)) {
        C = bin_relation_union(C,C2);
        C2 = bin_relation_composition(C,C);
    }
    return C;
}

bool graph_isEuler(graph G) {
    bin_relation transitive = transitive_closure(G);
    for (int i = 1; i <= G.max_value; i++) {
        int sum_of_transitive_row = 0;
        int sum_of_original_row = 0;
        for (int j = 1; j <= G.max_value; j++) {
            sum_of_transitive_row += bin_relation_getValue(transitive, i, j);
            sum_of_original_row += bin_relation_getValue(G, i, j);
        }
        if (sum_of_original_row % 2 != 0 || sum_of_transitive_row != G.max_value) {
            return 0;
        }
    }
    return 1;
}

typedef struct timeval Timeval;

Timeval getDifference(Timeval start, Timeval end) {
    Timeval difference;
    difference.tv_sec = end.tv_sec - start.tv_sec - (end.tv_usec < start.tv_usec);
    difference.tv_usec = (end.tv_usec + (end.tv_usec < start.tv_usec) * 1000000)-start.tv_usec;
    return difference;
}

void graph_generateBunch(int n, int m, int *hamilton_counter, int *euler_counter, int *all_counter) {
    Timeval start, end;
    gettimeofday(&start, NULL);
    gettimeofday(&end, NULL);
    while (getDifference(start, end).tv_sec < 10) {
        graph cur_graph = graph_generate(n, m);
        if (graph_isEuler(cur_graph)) {
            (*euler_counter)++;
        }
        if (graph_isHamilton(cur_graph)) {
            (*hamilton_counter)++;
        }
        (*all_counter)++;
        gettimeofday(&end, NULL);
    }
}

void makeTable(int n) {
    int start_m = n;
    int end_m = n*(n-1)/2;
    int diff_m = end_m - start_m;
    int h = 1;
    while (diff_m / h > 30) {
        h+=1;
    }
    if (diff_m / h < 20) {
        h-=1;
    }
    while (start_m <= end_m) {
        int hamilton = 0;
        int euler = 0;
        int all = 0;
        graph_generateBunch(n, start_m, &hamilton, &euler, &all);
        printf("%d %d %d %d %d\n", n, start_m, euler, hamilton, all);
        start_m += h;
    }
}

int main () {
    graph G1 = graph_generate(5, 0);
    bin_relation_matrixPrint(G1);
    printf("\n");
    graph G2 = graph_generate(5, 7);
    bin_relation_matrixPrint(G2);
    printf("\n");
    graph G3 = graph_generate(5, 10);
    bin_relation_matrixPrint(G3);
    printf("\n");
    graph G4 = graph_generate(8, 8);
    bin_relation_matrixPrint(G4);
    printf("\n");

    int vertex_amount;
    scanf("%d", &vertex_amount);
    makeTable(vertex_amount);
}

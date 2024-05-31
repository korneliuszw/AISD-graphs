#include <cstdio>
#include "containers.h"
#include "solutions.h"

int main() {
    int k, n, s, e;

    scanf_s("%d", &k);
    for (int i = 0; i < k; i++) {
        scanf_s("%d", &n);
        Graph graph(n);
        for (int j = 0; j < n; j++) {
            scanf_s("%d", &s);
            for (int l = 0; l < s; l++) {
                scanf_s("%d", &e);
                graph.add_edge(j, e - 1);
            }
        }
        Memory memory;
        solution_1(graph);
        solution_2(graph, memory);
        solution_3(graph, memory);
        solution_4(graph, memory);
        solution_5(graph);
        solution_6a(graph);
        solution_6b(graph);
        solution_6c(graph);
        solution_7(graph);
        solution_8(graph);
        std::printf("\n");
    }

    return 0;
}

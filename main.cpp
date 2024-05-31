#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include "containers.h"
#include "solutions.h"

int main() {
    int k, n, s, e;
    scanf("%d", &k);
    for (int i = 0; i < k; i++) {
        scanf("%d", &n);
        Graph graph(n);
        for (int j = 0; j < n; j++) {
            scanf("%d", &s);
            for (int l = 0; l < s; l++) {
                scanf("%d", &e);
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

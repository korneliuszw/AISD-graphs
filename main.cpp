#include <cstdio>
#include "containers.h"
#include "solutions.h"

int main() {
    int k, n, s, e;
    std::scanf("%d", &k);
    for (int i = 0; i < k; i++) {
        std::scanf("%d", &n);
        Graph graph(n);
        for (int j = 0; j < n; j++) {
            std::scanf("%d", &s);
            for (int l = 0; l < s; l++) {
                std::scanf("%d", &e);
                graph.add_edge(j, e - 1);
            }
        }
        solution_1(graph);
        solution_2(graph);
        solution_3(graph);
        solution_4(graph);
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

//
// Created by kwojn on 5/30/2024.
//
#include "solutions.h"
#include "containers.h"
#include "algos.h"
#include <cstdio>
#include <algorithm>
void solution_1(Graph& graph) {
    int* arr = new int[graph.get_size()];
    for (int i = 0; i < graph.get_size(); i++) {
        auto& list = graph.get_adjacency_list(i);
        arr[i] = list.get_size();
    }
    std::sort(arr, arr + graph.get_size());
//    quick_sort(arr, 0, graph.get_size() - 1);
    for (int i = graph.get_size() - 1; i >= 0; i--) {
        std::printf("%d ", arr[i]);
    }
    if (graph.get_size() == 0) {
        std::printf("%d", 0);
    }
    delete[] arr;
    std::printf("\n");
}

void solution_2(Graph& graph) {
    bool* marked = new bool[graph.get_size()];
    for (auto i = 0; i < graph.get_size(); i++) {
        marked[i] = false;
    }
    int counter = 0;
    for (int i = 0; i < graph.get_size(); i++) {
        if (marked[i]) continue;
        counter++;
        dfs_graph(graph, i, marked);
    }
    delete[] marked;
    std::printf("%d\n", counter);
}
void solution_3(Graph& graph) {
    std::printf("F\n");
}
void solution_4(Graph& graph) {
    std::printf("?\n");
}
void solution_5(Graph& graph) {
    std::printf("?\n");
}
void solution_6a(Graph& graph) {
    std::printf("?\n");
}
void solution_6b(Graph& graph) {
    std::printf("?\n");
}
void solution_6c(Graph& graph) {
    std::printf("?\n");
}
void solution_7(Graph& graph) {
    std::printf("?\n");
}
void solution_8(Graph& graph) {
    long long edge_count = 0;
    for (int i = 0; i < graph.get_size(); i++) {
        auto& list = graph.get_adjacency_list(i);
        edge_count += list.get_size();
    }
    long long expected = (long long)graph.get_size() * (graph.get_size() - 1);
    std::printf("%lld", (expected - edge_count) / 2);
}

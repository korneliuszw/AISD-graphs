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
        auto list = graph.get_adjacency_list(i);
        arr[i] = list->get_size();
    }
    quick_sort(arr, 0, graph.get_size() - 1);
    for (int i = graph.get_size() - 1; i >= 0; i--) {
        std::printf("%d ", arr[i]);
    }
    if (graph.get_size() == 0) {
        std::printf("%d", 0);
    }
    delete[] arr;
    std::printf("\n");
}

Vector<Vector<int>*>* get_components(Graph& graph) {
    auto components = new Vector<Vector<int>*>();
    bool* marked = new bool[graph.get_size()];
    int* stack = new int[graph.get_size()];
    for (auto i = 0; i < graph.get_size(); i++) {
        marked[i] = false;
    }
    // wierzcholek ktory nie zostal wczesniej odwiedzony tworzy nowa skladowa
    for (int i = 0; i < graph.get_size(); i++) {
        if (marked[i]) continue;
        marked[i] = true;
        int stack_top = 0;
        stack[stack_top++] = i;
        auto vertices = new Vector<int>();
        vertices->push(i);
        while (stack_top > 0) {
            int q = stack[--stack_top];
            Vector<int>* head = graph.get_adjacency_list(q);
            for (int k = 0; k < head->get_size(); k++) {
                int v = head->get(k);
                if (!marked[v]) {
                    marked[v] = true;
                    stack[stack_top++] = v;
                    vertices->push(v);
                }
            }
        }
        components->push(vertices);

    }
    delete[] marked;
    delete[] stack;
    return components;
}

void solution_2(Graph& graph, Memory& memory) {
    auto components = get_components(graph);
    std::printf("%d\n", components->get_size());
    memory.components = components;
}
bool solution_3_result(Graph& graph, Memory& memory) {
    char* colors = new char[graph.get_size()];
    for (int i = 0; i < graph.get_size(); i++) {
        colors[i] = 0;
    }
    auto components = memory.components;
    int* vertex_stack = new int[graph.get_size()];
    // przechodzimy przez wsyzstkie skladowe bo dwudzielnosc dotyczy grafow spojnych
    for (int j = 0; j < components->get_size(); j++) {
        int i = components->get(j)->get(0);
        int stack_top = 0;
        vertex_stack[stack_top++] = i;
        colors[i] = 1;
        // dfs kolorujacy wierzcholki ktore nie sa jeszcze pokolorowane na kolor przeiwny
        while (stack_top > 0) {
            int q = vertex_stack[--stack_top];
            auto head = graph.get_adjacency_list(q);
            for (int k = 0; k < head->get_size(); k++) {
                int v = head->get(k);
                // sasiad ma ten sam kolor co wierzcholek q, graf nie jest dwudzielny
                if (colors[v] == colors[q]) {
                    delete[] vertex_stack;
                    delete[] colors;
                    return false;
                }
                if (colors[v] == 0) {
                    colors[v] = colors[q] == 1 ? 2 : 1;
                    vertex_stack[stack_top++] = v;
                }
            }
        }
    }
        delete[] colors;
    delete[] vertex_stack;
    return true;
}
void solution_3(Graph& graph, Memory& memory) {
    std::printf("%c\n", solution_3_result(graph, memory) ? 'T' : 'F');
}

void map_vertices_to_component_sizes(Graph& graph, Memory& memory) {
    int* component_sizes = new int[graph.get_size()];
    for (int i = 0; i < memory.components->get_size(); i++) {
        auto component = memory.components->get(i);
        int size = component->get_size();
        for (int k = 0; k < component->get_size(); k++) {
            int vertex = component->get(k);
            component_sizes[vertex] = size;
        }
    }
    memory.component_sizes = component_sizes;
}
void solution_4(Graph &graph, Memory &memory) {
    map_vertices_to_component_sizes(graph, memory);
    int* queue = new int[graph.get_size()];
    int* marked = new int[graph.get_size()];
    int* distance = new int[graph.get_size()];
    for (int i = 0; i < graph.get_size(); i++) {
        marked[i] = -1;
    }
    for (int vertex = 0; vertex < graph.get_size(); vertex++) {
        int size = memory.component_sizes[vertex];
        if (size == 1 || size == 2) {
            printf("%d ", size == 1 ? 0 : 1);
            continue;
        }
        int queue_bottom = 0;
        int queue_top = 1;
        queue[queue_bottom] = vertex;
        marked[vertex] = vertex;
        distance[vertex] = 0;
        int last_dist = 0;
        while (queue_top < size) {
            int q = queue[queue_bottom++];
            auto head = graph.get_adjacency_list(q);
            for (int k = 0; k < head->get_size(); k++) {
                int v = head->get(k);
                if (marked[v] != vertex) {
                    marked[v] = vertex;
                    last_dist = distance[v] = distance[q] + 1;
                    queue[queue_top++] = v;
                }
            }
        }
        printf("%d ", last_dist);
    }
    printf("\n");
    delete[] queue;
    delete[] marked;
    delete[] distance;
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
struct StackElement {
    int q;
    int prev;
    int depth;
};
void solution_7(Graph& graph) {
    int counter = 0;
    auto* stack = new StackElement[graph.get_size() * 4];
    for (int i = 0; i < graph.get_size(); i++) {
        int stack_top = 0;
        stack[stack_top++] = {i, -1, 0};
        while (stack_top > 0) {
            auto elem = stack[--stack_top];
            if (elem.depth == 3) {
                if (elem.q == i)
                    counter++;
                continue;
            }
            auto head = graph.get_adjacency_list(elem.q);
            for (int k = 0; k < head->get_size(); k++) {
                int v = head->get(k);
                if (elem.prev != v) {
                    stack[stack_top++] = {v, elem.q, elem.depth + 1};
                }
            }
        }
    }
    delete[] stack;
    counter /= 8;
    std::printf("%d\n", counter);
//    std::printf("?\n");
}
void solution_8(Graph& graph) {
    long long edge_count = 0;
    for (int i = 0; i < graph.get_size(); i++) {
        auto list = graph.get_adjacency_list(i);
        edge_count += list->get_size();
    }
    long long expected = (long long)graph.get_size() * (graph.get_size() - 1);
    std::printf("%lld", (expected - edge_count) / 2);
}

Memory::~Memory() {
    delete components;
    delete component_sizes;
}

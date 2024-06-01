//
// Created by kwojn on 5/30/2024.
//
#include "solutions.h"
#include "containers.h"
#include "algos.h"
#include <cstdio>
void solution_1(Graph &graph, Memory &memory) {
    // przechowujemy wierzcholki wraz z ich stopniami by wykorzystac je tez w innym rozwiazaniu
    auto* arr = new DegreeCount[graph.get_size()];
    for (int i = 0; i < graph.get_size(); i++) {
        auto list = graph.get_adjacency_list(i);
        arr[i] = {i, list->get_size()};
    }
    // sortujemy wierzcholki po stopniach
    merge_sort(arr, 0, graph.get_size() - 1);
    for (int i = graph.get_size() - 1; i >= 0; i--) {
        std::printf("%d ", arr[i].degree);
    }
    if (graph.get_size() == 0) {
        std::printf("%d", 0);
    }
    memory.degrees = arr;
    std::printf("\n");
}

Vector<Vector<int>*>* get_components(Graph& graph) {
    // przechowujemy wszystkie wierzcholki w skladowych by potem efektywniej kolorowac wierzcholki w 6c
    auto components = new Vector<Vector<int>*>();
    bool* marked = new bool[graph.get_size()]();
    int* stack = new int[graph.get_size()];
    for (int i = 0; i < graph.get_size(); i++) {
        // wierzcholek ktory nie zostal wczesniej odwiedzony tworzy nowa skladowa
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
    char* colors = new char[graph.get_size()]();
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
        // bfs, ale mozemy bezpiecznie przerwac po przejsciu przez wszystkie wierzcholki w skladowej
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

void color(int* sorted_adjacency, int* colors, int vertex, Graph& graph) {
    auto list = graph.get_adjacency_list(vertex);
    int size = list->get_size();
    int min = 1;
    // pobieramy kolory sasiadow
    for (int j = 0; j < size; j++) {
        sorted_adjacency[j] = colors[list->get(j)];
    }
    // sortujemy sasiadow po kolorach by moc przypisac wierzcholkowi najmniejszy mozliwy kolor
    merge_sort(sorted_adjacency, 0, size - 1);
    for (int j = 0; j < size; j++) {
        if (sorted_adjacency[j] == min)
            min++;
    }
    colors[vertex] = min;
}

void solution_6a(Graph& graph) {
    int* colors = new int[graph.get_size()];
    for (int i = 0; i < graph.get_size(); i++) {
        colors[i] = 0;
    }
    int* sorted_adjacency = new int[graph.get_size()]();
    for (int i = 0; i < graph.get_size(); i++) {
        color(sorted_adjacency, colors, i, graph);
        std::printf("%d ", colors[i]);
    }
    delete[] colors;
    delete[] sorted_adjacency;
    std::printf("\n");
}
void solution_6b(Graph &graph, Memory &memory) {
    int* colors = new int[graph.get_size()]();
    int* sorted_adjacency = new int[graph.get_size()]();
    // w tym rozwiazaniu zaczynamy malowanie od wierzcholkow o najwiekszym stopniu
    for (int i = graph.get_size() - 1; i >= 0; i--) {
        // obliczone w pkt 1
        int v = memory.degrees[i].vertex;
        color(sorted_adjacency, colors, v, graph);
    }
    for (int i = 0; i < graph.get_size(); i++) {
        std::printf("%d ", colors[i]);
    }
    delete[] colors;
    delete[] sorted_adjacency;
    std::printf("\n");
}
void solution_6c(Graph &graph, Memory &memory) {
    int* colors = new int[graph.get_size()]();
    int* sorted_adjacency = new int[graph.get_size()];
    int* saturation = new int[graph.get_size()]();
    // komponenty nie caly graf by skrocic wielkosc zagniezdzonej petli
    for (int i = 0 ; i < memory.components->get_size(); i++) {
        auto component = memory.components->get(i);
        int colored = 0;
        while (colored < component->get_size()) {
            int vertex = 0;
            int max_saturation = -1;
            int max_degree = -1;
            for (int k = 0; k < component->get_size(); k++) {
                int w = component->get(k);
                if (colors[w] > 0) {
                    continue;
                }
                int degree = graph.get_adjacency_list(w)->get_size();
                int sat = saturation[w];
                // wybieramy wierzcholek o najwiekszym nasyceniu, a jesli takich jest kilka to o najwiekszym stopniu, a jesli takich jest kilka to o najmniejszym numerze
                if (sat > max_saturation || (sat == max_saturation && (degree > max_degree || (degree == max_degree && w < vertex)))) {
                    max_saturation = sat;
                    vertex = w;
                    max_degree = degree;
                }
            }
            color(sorted_adjacency, colors, vertex, graph);
            auto this_list = graph.get_adjacency_list(vertex);
            // przelicz nasycenie sasiadow
            for (int k = 0; k < this_list->get_size(); k++) {
                int v = this_list->get(k);
                if (colors[v] > 0)
                    continue;
                auto other_list = graph.get_adjacency_list(v);
                bool unique = true;
                for (int j = 0; j < other_list->get_size(); j++) {
                    int w = other_list->get(j);
                    // obecny wierzcholek ma taki sam kolor jak sasiad sasiada, wiec nie musimy zwiekszac nasycenia sasiadowi
                    if (w != vertex && colors[w] == colors[vertex]) {
                        unique = false;
                        break;
                    }
                }
                if (unique)
                    saturation[v]++;
            }
            colored++;
        }
    }
    for (int i = 0; i < graph.get_size(); i++) {
        std::printf("%d ", colors[i]);
    }
    delete[] colors;
    delete[] sorted_adjacency;
    delete[] saturation;
    std::printf("\n");
}
void solution_7(Graph &graph, Memory &memory) {
    std::printf("?\n");
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
    delete degrees;
}

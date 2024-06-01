//
// Created by kwojn on 5/30/2024.
//
#pragma once
class Graph;
template <typename T> class Vector;
struct DegreeCount {
    int vertex;
    int degree;
    bool operator<(const DegreeCount& other) const {
        return degree < other.degree;
    }
    bool operator>(const DegreeCount& other) const {
        return degree > other.degree;
    }
};
struct Memory {
    Vector<Vector<int>*>* components;
    int* component_sizes;
    DegreeCount* degrees;
    Memory() {
        components = nullptr;
        component_sizes = nullptr;
        degrees = nullptr;
    }
    ~Memory();

};
void solution_1(Graph &graph, Memory &memory);
void solution_2(Graph& graph, Memory& memory);
void solution_3(Graph& graph, Memory& memory);
void solution_4(Graph &graph, Memory &memory);
void solution_5(Graph& graph);
void solution_6a(Graph& graph);
void solution_6b(Graph &graph, Memory &memory);
void solution_6c(Graph &graph, Memory &memory);
void solution_7(Graph& graph);
void solution_8(Graph& graph);

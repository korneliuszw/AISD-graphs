//
// Created by kwojn on 5/30/2024.
//
#pragma once
class Graph;
template <typename T> class Vector;
struct Memory {
    Vector<Vector<int>*>* components;
    Memory() {
        components = nullptr;
    }
    ~Memory();

};
void solution_1(Graph& graph);
void solution_2(Graph& graph, Memory& memory);
void solution_3(Graph& graph, Memory& memory);
void solution_4(Graph &graph, Memory &memory);
void solution_5(Graph& graph);
void solution_6a(Graph& graph);
void solution_6b(Graph& graph);
void solution_6c(Graph& graph);
void solution_7(Graph& graph);
void solution_8(Graph& graph);

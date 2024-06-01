//
// Created by kwojn on 5/30/2024.
//

#ifndef GRAPHY_I_TAKIE_TAM_CONTAINERS_H
#define GRAPHY_I_TAKIE_TAM_CONTAINERS_H

#include <cstdlib>
#include <type_traits>

template <typename T>
class Vector {
    T* data;
    int size;
    int capacity;
public:
    Vector(): size(0), capacity(8) {
        data = new T[capacity];
    }
    void push(T element) {
        if (size == capacity) {
            capacity *= 2;
            T* new_data = new T[capacity];
            for (int i = 0; i < size; i++) {
                new_data[i] = data[i];
            }
            delete[] data;
            data = new_data;
        }
        data[size++] = element;
    }
    T& get(int index) {
        return data[index];
    }
    [[nodiscard]] int get_size() const {
        return size;
    }
    ~Vector() {
        if constexpr (std::is_pointer<T>::value) {
            for (int i = 0; i < size; i++) {
                delete data[i];
            }
        }
        delete[] data;
    }

};

class Graph {
    int size;
    Vector<int>* adjacency_list;
public:
    explicit Graph(int size): size(size) {
        adjacency_list = new Vector<int>[size];
    }
    void add_edge(int from, int to) {
        adjacency_list[from].push(to);
    }
    Vector<int>* get_adjacency_list(int vertex) {
        return adjacency_list+vertex;
    }
    [[nodiscard]] int get_size() const {
        return size;
    }
    ~Graph() {
        delete[] adjacency_list;
    }
};

#endif //GRAPHY_I_TAKIE_TAM_CONTAINERS_H

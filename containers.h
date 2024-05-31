//
// Created by kwojn on 5/30/2024.
//

#ifndef GRAPHY_I_TAKIE_TAM_CONTAINERS_H
#define GRAPHY_I_TAKIE_TAM_CONTAINERS_H

#include <cstdlib>

template <typename T>
class List {
    class Node {
        T data;
        Node* next = nullptr;
    public:
        explicit Node(T data): data(data) {}
        T get_data() { return data; }
        Node* get_next() { return next; }
        void set_next(Node* nextNode) { this->next = nextNode; }
        ~Node() {
            if (next != nullptr)
                delete next;
        }
    };
    int size;
    Node* head;
    Node* last;
public:
    List(): size(0), head(nullptr), last(nullptr) {}
    void push(T data) {
        Node* node = new Node(data);
        if (!head)
            head = last = node;
        else
            last->set_next(node);
        last = node;
        size++;
    }
    Node* get_head() {
        return head;
    }
    [[nodiscard]] int get_size() const {
        return size;
    }
    ~List() {
        delete head;
    }
};

template <typename T>
class Vector {
    T* data;
    int size;
    int capacity;
public:
    Vector(): size(0), capacity(8) {
        data = new T[capacity];
    }
    explicit Vector(T* data, int size): size(size), capacity(size) {
        this->data = data;
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
        delete[] data;
    }

};

class Graph {
    int size;
    List<int>* adjacency_list;
public:
    explicit Graph(int size): size(size) {
        adjacency_list = new List<int>[size];
        for (int i = 0; i < size; i++) {
            adjacency_list[i] = List<int>();
        }
    }
    void add_edge(int from, int to) {
        adjacency_list[from].push(to);
    }
    List<int>& get_adjacency_list(int vertex) {
        return adjacency_list[vertex];
    }
    [[nodiscard]] int get_size() const {
        return size;
    }
    ~Graph() {
        delete[] adjacency_list;
    }
};

#endif //GRAPHY_I_TAKIE_TAM_CONTAINERS_H

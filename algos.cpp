//
// Created by kwojn on 5/30/2024.
//

#include "algos.h"
#include "containers.h"

void quick_sort(int* arr, int l, int r) {
    if (l >= r)
        return;
    int pivot = arr[(l + r) / 2];
    int i = l, j = r;
    while (i <= j) {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i <= j) {
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    }
    quick_sort(arr, l, j);
    quick_sort(arr, i, r);
}

void dfs_graph(Graph& graph, int start, bool* marked) {

}
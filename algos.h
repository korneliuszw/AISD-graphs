//
// Created by kwojn on 5/30/2024.
//

#ifndef GRAPHY_I_TAKIE_TAM_ALGOS_H
#define GRAPHY_I_TAKIE_TAM_ALGOS_H
class Graph;

template <typename T>
void merge_sort_inside(T* arr, int l, int r, T* tmp) {
    if (l >= r)
        return;
    int m = (l + r) / 2;
    merge_sort_inside(arr, l, m, tmp);
    merge_sort_inside(arr, m + 1, r, tmp);
    int i = l, j = m + 1, k = 0;
    while (i <= m && j <= r) {
        if (arr[i] < arr[j]) {
            tmp[k++] = arr[i++];
        } else {
            tmp[k++] = arr[j++];
        }
    }
    while (i <= m) {
        tmp[k++] = arr[i++];
    }
    while (j <= r) {
        tmp[k++] = arr[j++];
    }
    for (int i = l; i <= r; i++) {
        arr[i] = tmp[i - l];
    }
}

template <typename T>
void merge_sort(T* arr, int l, int r) {
    T* tmp = new T[r - l + 1];
    merge_sort_inside(arr, l, r, tmp);
    delete[] tmp;
}
#endif //GRAPHY_I_TAKIE_TAM_ALGOS_H

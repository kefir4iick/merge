#include "mergesort.h"

void merge_1(int arr[], int aux[], int low, int mid, int high, SortMetrics *metrics) {
    for (int k = low; k <= high; k++) {
        aux[k] = arr[k];
        metrics->copy_operations++;
    }
    
    int i = low, j = mid + 1;
    for (int k = low; k <= high; k++) {
        if (i > mid) {
            arr[k] = aux[j++];
        } else if (j > high) {
            arr[k] = aux[i++];
        } else {
            metrics->comparisons++;
            if (aux[j] < aux[i]) {
                arr[k] = aux[j++];
            } else {
                arr[k] = aux[i++];
            }
        }
        metrics->copy_operations++;
    }
}

void sort_recursive(int arr[], int aux[], int low, int high, SortMetrics *metrics) {
    if (high <= low) return;
    
    int mid = low + (high - low) / 2;
    sort_recursive(arr, aux, low, mid, metrics);
    sort_recursive(arr, aux, mid + 1, high, metrics);
    merge_1(arr, aux, low, mid, high, metrics);
}

void top_down(int arr[], int n, SortMetrics *metrics) {
    int *aux = (int*)malloc(n * sizeof(int));
    metrics->memory_used += n * sizeof(int);
    
    sort_recursive(arr, aux, 0, n - 1, metrics);
    
    free(aux);
}

#include "mergesort.h"

void bottom_up(int arr[], int n, SortMetrics *metrics) {
    int *aux = (int*)malloc(n * sizeof(int));
    metrics->memory_used += n * sizeof(int);
    
    for (int size = 1; size < n; size = size + size) {
        for (int low = 0; low < n - size; low += size + size) {
            int mid = low + size - 1;
            int high = (low + size + size - 1 < n - 1) ? (low + size + size - 1) : (n - 1);
            
            metrics->comparisons++;
            if (arr[mid] <= arr[mid + 1]) {
                continue;
            }
            
            merge_1(arr, aux, low, mid, high, metrics);
        }
    }
    
    free(aux);
}

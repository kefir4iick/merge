#include "mergesort.h"

void merge_3(int src[], int dst[], int low, int mid, int high, SortMetrics *metrics) {
    int i = low, j = mid + 1;
    for (int k = low; k <= high; k++) {
        if (i > mid) {
            dst[k] = src[j++];
        } else if (j > high) {
            dst[k] = src[i++];
        } else {
            metrics->comparisons++;
            if (src[j] < src[i]) {
                dst[k] = src[j++];
            } else {
                dst[k] = src[i++];
            }
        }
        metrics->copy_operations++;
    }
}

void optimized(int arr[], int n, SortMetrics *metrics) {
    const int CUTOFF = 7;
    
    if (n <= CUTOFF) {
        insertion_sort(arr, 0, n - 1, metrics);
        return;
    }
    
    if (is_sorted(arr, n, metrics)) {
        return;
    }
    
    int *aux = (int*)malloc(n * sizeof(int));
    metrics->memory_used += n * sizeof(int);
    memcpy(aux, arr, n * sizeof(int));
    metrics->copy_operations += n;
    
    int *src = aux;
    int *dst = arr;
    
    for (int size = 1; size < n; size = size + size) {
        for (int low = 0; low < n - size; low += size + size) {
            int mid = low + size - 1;
            int high = (low + size + size - 1 < n - 1) ? (low + size + size - 1) : (n - 1);
            
            metrics->comparisons++;
            if (src[mid] <= src[mid + 1]) {
                for (int k = low; k <= high; k++) {
                    dst[k] = src[k];
                    metrics->copy_operations++;
                }
                continue;
            }
            
            if (high - low + 1 <= CUTOFF) {
                for (int k = low; k <= high; k++) {
                    dst[k] = src[k];
                    metrics->copy_operations++;
                }
                insertion_sort(dst, low, high, metrics);
            } else {
                merge_3(src, dst, low, mid, high, metrics);
            }
        }
        
        int *temp = src;
        src = dst;
        dst = temp;
    }
    
    if (src != arr) {
        memcpy(arr, src, n * sizeof(int));
        metrics->copy_operations += n;
    }
    
    free(aux);
}

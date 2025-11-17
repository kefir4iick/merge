#include "mergesort.h"

void merge_4(int arr[], int aux[], int starts[], int ends[], int num_parts, int low, int high, SortMetrics *metrics) {
    for (int k = low; k <= high; k++) {
        aux[k] = arr[k];
        metrics->copy_operations++;
    }
    
    int indices[10];
    for (int i = 0; i < num_parts; i++) {
        indices[i] = starts[i];
    }
    
    for (int k = low; k <= high; k++) {
        int min_val = INT_MAX;
        int min_idx = -1;
        
        for (int i = 0; i < num_parts; i++) {
            if (indices[i] <= ends[i]) {
                metrics->comparisons++;
                if (aux[indices[i]] < min_val) {
                    min_val = aux[indices[i]];
                    min_idx = i;
                }
            }
        }
        
        if (min_idx != -1) {
            arr[k] = min_val;
            indices[min_idx]++;
            metrics->copy_operations++;
        }
    }
}

void ten_way(int arr[], int n, SortMetrics *metrics) {
    const int NUM_PARTS = 10;
    int *aux = (int*)malloc(n * sizeof(int));
    metrics->memory_used += n * sizeof(int);
    
    int *temp = (int*)malloc(n * sizeof(int));
    metrics->memory_used += n * sizeof(int);
    memcpy(temp, arr, n * sizeof(int));
    metrics->copy_operations += n;
    
    for (int size = 1; size < n; size *= NUM_PARTS) {
        for (int low = 0; low < n; low += size * NUM_PARTS) {
            int starts[NUM_PARTS], ends[NUM_PARTS];
            int num_parts = 0;
            
            for (int i = 0; i < NUM_PARTS; i++) {
                int part_low = low + i * size;
                if (part_low >= n) break;
                
                int part_high = part_low + size - 1;
                if (part_high >= n) part_high = n - 1;
                
                starts[num_parts] = part_low;
                ends[num_parts] = part_high;
                num_parts++;
            }
            
            if (num_parts > 1) {
                merge_4(temp, aux, starts, ends, num_parts, low, 
                            (low + size * NUM_PARTS - 1 < n - 1) ? 
                            (low + size * NUM_PARTS - 1) : (n - 1), metrics);
            }
        }
        
        memcpy(arr, temp, n * sizeof(int));
        metrics->copy_operations += n;
    }
    
    free(aux);
    free(temp);
}

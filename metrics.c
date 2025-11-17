#include "mergesort.h"

void init_metrics(SortMetrics *metrics) {
    metrics->comparisons = 0;
    metrics->copy_operations = 0;
    metrics->memory_used = 0;
    metrics->start_time = 0;
    metrics->end_time = 0;
}

void start_timer(SortMetrics *metrics) {
    metrics->start_time = clock();
}

void stop_timer(SortMetrics *metrics) {
    metrics->end_time = clock();
}

double get_time(SortMetrics *metrics) {
    return ((double)(metrics->end_time - metrics->start_time)) / CLOCKS_PER_SEC;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insertion_sort(int arr[], int low, int high, SortMetrics *metrics) {
    for (int i = low + 1; i <= high; i++) {
        int key = arr[i];
        int j = i - 1;
        
        while (j >= low) {
            metrics->comparisons++;
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                metrics->copy_operations++;
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = key;
        metrics->copy_operations++;
    }
}

int is_sorted(int arr[], int n, SortMetrics *metrics) {
    for (int i = 0; i < n - 1; i++) {
        metrics->comparisons++;
        if (arr[i] > arr[i + 1]) {
            return 0;
        }
    }
    return 1;
}

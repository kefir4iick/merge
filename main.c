#include "mergesort.h"

void print_array(int arr[], int n) {
    for (int i = 0; i < n && i < 20; i++) {
        printf("%d ", arr[i]);
    }
    if (n > 20) printf("...");
    printf("\n");
}

void generate_random_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }
}

void test_algorithm(const char* name, void (*sort_func)(int[], int, SortMetrics*), 
                   int arr[], int n, SortMetrics *metrics) {
    int *test_arr = (int*)malloc(n * sizeof(int));
    memcpy(test_arr, arr, n * sizeof(int));
    
    init_metrics(metrics);
    start_timer(metrics);
    sort_func(test_arr, n, metrics);
    stop_timer(metrics);
    
    printf("%s:\n", name);
    printf("  time: %.6f sec\n", get_time(metrics));
    printf("  comparisons: %lu\n", metrics->comparisons);
    printf("  copies: %lu\n", metrics->copy_operations);
    printf("  memory: %zu bytes\n", metrics->memory_used);
    printf("  sorted: %s\n", is_sorted(test_arr, n, metrics) ? "y" : "n");
    printf("\n");
    
    free(test_arr);
}

int main() {
    srand(time(NULL));
    const int N = 10000;
    int *original_arr = (int*)malloc(N * sizeof(int));
    SortMetrics metrics;
    
    printf("generate array: %d elements\n", N);
    generate_random_array(original_arr, N);
    
    printf("\ninitial array (20 first):\n");
    print_array(original_arr, N);
    
    printf("\ntest:\n\n");
    
    test_algorithm("1. top-down", top_down, original_arr, N, &metrics);
    
    test_algorithm("2. bottom-up", bottom_up, original_arr, N, &metrics);
    
    test_algorithm("3. optimized", optimized, original_arr, N, &metrics);
    
    test_algorithm("4. 10 way", ten_way, original_arr, N, &metrics);
    
    free(original_arr);
    return 0;
}

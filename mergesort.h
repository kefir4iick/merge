#ifndef MERGESORT_H
#define MERGESORT_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>

typedef struct {
    unsigned long comparisons;
    unsigned long copy_operations;
    size_t memory_used;
    clock_t start_time;
    clock_t end_time;
} SortMetrics;


void init_metrics(SortMetrics *metrics);
void start_timer(SortMetrics *metrics);
void stop_timer(SortMetrics *metrics);
double get_time(SortMetrics *metrics);


void swap(int *a, int *b);
void insertion_sort(int arr[], int low, int high, SortMetrics *metrics);
int is_sorted(int arr[], int n, SortMetrics *metrics);


void top_down(int arr[], int n, SortMetrics *metrics);
void bottom_up(int arr[], int n, SortMetrics *metrics);
void optimized(int arr[], int n, SortMetrics *metrics);
void ten_way(int arr[], int n, SortMetrics *metrics);


void print_array(int arr[], int n);
void generate_random_array(int arr[], int n);
void test_algorithm(const char* name, void (*sort_func)(int[], int, SortMetrics*), 
                   int arr[], int n, SortMetrics *metrics);

#endif

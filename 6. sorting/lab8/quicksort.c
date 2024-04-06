#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <sys/time.h>   // for gettimeofday()

int num_quicksort_partition_calls = 0;
int num_quicksort_calls = 0;
int num_quicksort_comparisons = 0;
int num_insertionsort_comparisions = 0;
int num_insertionsort_calls = 0;

void Swap(int* array, int ind1, int ind2) {
    int tmp = array[ind1];
    array[ind1] = array[ind2];
    array[ind2] = tmp;
}

void Shuffle(int* array, int size) {
  unsigned int seed = time(NULL);  // Generate seed based on current time
  for (int i = size - 1; i > 0; i--) {
    unsigned int j = rand_r(&seed) % (i + 1);
    Swap(array, i, j);
  }
}

// Take the first, last and middle element from the array.
void MedianOfThree(int* data, int low, int high) {
    int mid = low + (high - low) / 2;
    if (data[low] > data[mid])
        Swap(data, low, mid);
    if (data[mid] > data[high])
        Swap(data, mid, high);
    if (data[low] > data[mid])
        Swap(data, low, mid);
}

int Partition(int* data, int low, int high) {
    num_quicksort_partition_calls++;
    int pivot = data[low];
    int leftwall = low;
    for (int i = low + 1; i <= high; i++) {
        num_quicksort_comparisons++;
        if (data[i] < pivot) {
            leftwall++;
            Swap(data, i, leftwall);
        }
    }
    Swap(data, low, leftwall);
    return leftwall;
}

// find the median
int MedianPartition(int* data, int low, int high) {
  num_quicksort_partition_calls++;
  MedianOfThree(data, low, high);
  return Partition(data, low, high);
}

// Modify Quicksort median as the pivot
void Quicksort(int* data, int low, int high) {
  num_quicksort_calls++;
  if (low < high) {
    int pivot_location = MedianPartition(data, low, high);
    Quicksort(data, low, pivot_location);
    Quicksort(data, pivot_location + 1, high);
    }
}

void InsertionSort(int* arr, int n) {
    num_insertionsort_calls++;
    int i, j;
    for (i = 1; i < n; i++) {
        j = i;
        // Move elements of arr[0..i-1], that are greater than arr[i],
        while (j > 0 && arr[j] < arr[j - 1]) {
          num_insertionsort_comparisions++;
          Swap(arr, j, j - 1);
          j = j - 1;
        }
    }
}

// Function to measure time taken by Quicksort and print it
int show_time_quicksort(int* data, int num_elems) {
    struct timeval begin, end;
    gettimeofday(&begin, NULL);
    Quicksort(data, 0, num_elems - 1);
    gettimeofday(&end, NULL);
    int seconds = (end.tv_sec - begin.tv_sec);
    int micros = ((seconds * 1000000) + end.tv_usec) - (begin.tv_usec);
    // printf("Time elpased for quicksort is %ld micros\n", micros);
    return micros;
}

// Function to measure time taken by InsertionSort and print it
int show_time_insertionsort(int* data, int num_elems) {
  struct timeval begin, end;
  gettimeofday(&begin, NULL);
  InsertionSort(data, num_elems);
  gettimeofday(&end, NULL);
  int seconds = (end.tv_sec - begin.tv_sec);
  int micros = ((seconds * 1000000) + end.tv_usec) - (begin.tv_usec);
  // printf("Time elpased for insertionsort is %ld micros\n", micros);
  return micros;
}

void PrintArray(int* array, int num_elems) {
    printf("[");
    for (int i = 0; i < num_elems; i++) {
        printf("%d ", array[i]);
    }
    printf("]\n");
}

int CheckArray(int* array, int num_elems) {
    for (int i = 1; i < num_elems; i++) {
        if (array[i] < array[i - 1]) {
            printf("NOT SORTED!!!\n");
            return 0;
        }
    }
    printf("SORTED!!\n");
    return 1;
}

int main() {
    int threshold_values[] = {5, 6, 7, 8, 10, 50, 100, 200, 500};
    int num_thresholds = sizeof(threshold_values) / sizeof(threshold_values[0]);
    for (int i = 0; i < num_thresholds; i++) {
      int* integers = (int*)malloc(sizeof(int*) * threshold_values[i]);
      unsigned int seed = time(NULL);
      for (int j = 0; j < threshold_values[i]; j++) {
        // Generate random numbers between 10 and 99
        integers[j] = (rand_r(&seed) % 90) + 10;
      }
      printf("\nThreshold value: %d\n", threshold_values[i]);
      int time_insertionsort =
        show_time_insertionsort(integers, threshold_values[i]);
      int time_quicksort =
        show_time_quicksort(integers, threshold_values[i]);
      if (time_insertionsort < time_quicksort) {
        printf("Sort used: InsertionSort\n");
        printf("Time elpased for insertionsort is %ld micros\n",
          time_insertionsort);
        printf("Time elpased for quickSort is %ld micros\n",
          time_quicksort);
      } else {
        printf("Sort used: Quicksort\n");
        printf("Time elpased for quickSort is %ld micros\n", time_quicksort);
        printf("Time elpased for insertionsort is %ld micros\n",
          time_insertionsort);
      }
      printf("Num quick sort partition calls: %d\n",
        num_quicksort_partition_calls);
      printf("Num quick sort comparisons calls: %d\n",
        num_quicksort_comparisons);
      printf("Num insertion sort comparisons calls: %d\n",
        num_insertionsort_comparisions);
      num_quicksort_calls = 0;
      num_insertionsort_calls = 0;
      num_insertionsort_comparisions = 0;
      num_quicksort_comparisons = 0;
      num_quicksort_partition_calls = 0;
      free(integers);
    }
    return 0;
}

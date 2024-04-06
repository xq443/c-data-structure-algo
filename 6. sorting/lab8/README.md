### a8 Summary
1. About:

- Variation 1: Shuffle array and then sort
    - Modify Quicksort to shuffle the elements of the array before sorting.
- Variation 2: Median pivot
    - Modify Quicksort to use the median of the first, last, and middle elements as the pivot.
- Variation 3: Quicksort + Insertion
    - Modify Quicksort to use insertion sort if the array size is below a certain threshold.
    - Experiment to find an optimal threshold for switching to insertion sort.

2. Project file directory:

- `quicksort.c`: This file contains the implementation of the Quicksort algorithm and incorporating insertion sort for smaller arrays. It also includes functions to measure the time taken by Quicksort and Insertion Sort.
- `README.md`: This file typically contains documentation or instructions related to the project. 
- `show_time.c`: This file  contains utility functions or methods related to measuring time, such as show_time_quicksort() and show_time_insertionsort().

3. Building and Running the Code:
* compile the code
```bash
gcc quicksort.c
./a.out
```
```
Threshold value: 5
Sort used: InsertionSort
Time elpased for insertionsort is 0 micros
Time elpased for quickSort is 1 micros
Num quick sort partition calls: 8
Num quick sort comparisons calls: 10
Num insertion sort comparisons calls: 0

Threshold value: 6
Sort used: InsertionSort
Time elpased for insertionsort is 0 micros
Time elpased for quickSort is 1 micros
Num quick sort partition calls: 10
Num quick sort comparisons calls: 15
Num insertion sort comparisons calls: 4

Threshold value: 7
Sort used: InsertionSort
Time elpased for insertionsort is 0 micros
Time elpased for quickSort is 1 micros
Num quick sort partition calls: 12
Num quick sort comparisons calls: 21
Num insertion sort comparisons calls: 10

Threshold value: 8
Sort used: Quicksort
Time elpased for quickSort is 0 micros
Time elpased for insertionsort is 0 micros
Num quick sort partition calls: 14
Num quick sort comparisons calls: 28
Num insertion sort comparisons calls: 13

Threshold value: 10
Sort used: Quicksort
Time elpased for quickSort is 1 micros
Time elpased for insertionsort is 1 micros
Num quick sort partition calls: 18
Num quick sort comparisons calls: 45
Num insertion sort comparisons calls: 23

Threshold value: 50
Sort used: Quicksort
Time elpased for quickSort is 5 micros
Time elpased for insertionsort is 5 micros
Num quick sort partition calls: 98
Num quick sort comparisons calls: 1225
Num insertion sort comparisons calls: 590

Threshold value: 100
Sort used: Quicksort
Time elpased for quickSort is 15 micros
Time elpased for insertionsort is 17 micros
Num quick sort partition calls: 198
Num quick sort comparisons calls: 4950
Num insertion sort comparisons calls: 2421

Threshold value: 200
Sort used: Quicksort
Time elpased for quickSort is 55 micros
Time elpased for insertionsort is 67 micros
Num quick sort partition calls: 398
Num quick sort comparisons calls: 19900
Num insertion sort comparisons calls: 10207

Threshold value: 500
Sort used: Quicksort
Time elpased for quickSort is 366 micros
Time elpased for insertionsort is 456 micros
Num quick sort partition calls: 998
Num quick sort comparisons calls: 124750
Num insertion sort comparisons calls: 6377
```

* check memory leak error
```bash
valgrind --leak-check=full ./a.out
```
```
==2858739== 
==2858739== HEAP SUMMARY:
==2858739==     in use at exit: 0 bytes in 0 blocks
==2858739==   total heap usage: 10 allocs, 10 frees, 4,568 bytes allocated
==2858739== 
==2858739== All heap blocks were freed -- no leaks are possible
==2858739== 
==2858739== For lists of detected and suppressed errors, rerun with: -s
==2858739== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0i)7
```

* using clint.py to check code style
```bash
clint.py *.c
```
```
bash-4.4$ clint.py *.c
Done processing quicksort.c
Done processing show_time.c
Total errors found: 0
```

4. Summary:
- In practice, Quicksort tends to outperform Insertion Sort for larger datasets due to its better average-case time complexity. 
- However, Insertion Sort may be preferred for small datasets or nearly sorted arrays due to its lower overhead and better performance in these cases.
- The threshold for array length is appoximately around 7 8.
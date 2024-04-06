### a6 Summary
1. About:

- Implement a insertion sort, selection sort, and merge sort in a doubly-linked list designed before, with robust memory allocation with memory leak error check
- All integrated into a unit test development using the Google Test framework.
- Implement the integration test in Main.c

2. Project file directory:

- `Assert007.c`: This file contains the implementation of the Assert007 module.
- `Assert007.h`: It is the header file for the Assert007 module, defining its interface.
- `LinkedList_easy.h`: This header file provides an easy-to-use interface for the LinkedList module.
- `LinkedList.h`: It's the primary header file for the LinkedList module, specifying its interface.
- `Main.c`: This file serves as the main source file for the project.
- `Makefile`: The Makefile used for building the project.
- `README.md`: This Markdown file contains information and instructions about the project.
- `release-1.8.0.tar.gz`: It's a tarball archive containing the release of the Google Test framework.
- `test_linkedlist.cc`: Contains unit tests for the sorting implementation module, adding additional unit tests.

3. Building and Running the Code:

* compile the code and verify 3 unit tests
```bash
make test
./test_suite
```
```
[==========] Running 3 tests from 3 test cases.
[----------] Global test environment set-up.
[----------] 1 test from InsertionSort
[ RUN      ] InsertionSort.givenNoInputWhenCreatingListThenMergeSort
Before sorting:
1 12 3 100 
After sorting:
1 3 12 100 
[       OK ] InsertionSort.givenNoInputWhenCreatingListThenMergeSort (24 ms)
[----------] 1 test from InsertionSort (37 ms total)

[----------] 1 test from SelectionSort
[ RUN      ] SelectionSort.givenNoInputWhenCreatingListThenMergeSort
Before sorting:
1 5 8 2 4 
After sorting:
1 2 4 5 8 
[       OK ] SelectionSort.givenNoInputWhenCreatingListThenMergeSort (7 ms)
[----------] 1 test from SelectionSort (7 ms total)

[----------] 1 test from MergeSort
[ RUN      ] MergeSort.givenNoInputWhenCreatingListThenMergeSort
Before sorting:
100 3 12 1 
After sorting:
1 3 12 100 
[       OK ] MergeSort.givenNoInputWhenCreatingListThenMergeSort (9 ms)
[----------] 1 test from MergeSort (9 ms total)

[----------] Global test environment tear-down
[==========] 3 tests from 3 test cases ran. (118 ms total)
[  PASSED  ] 3 tests.
```

* check memory leak error
```bash
valgrind --leak-check=full ./test_suite
```
```
==2121587== HEAP SUMMARY:
==2121587==     in use at exit: 0 bytes in 0 blocks
==2121587==   total heap usage: 304 allocs, 304 frees, 5,896 bytes allocated
==2121587== 
==2121587== All heap blocks were freed -- no leaks are possible
==2121587== 
==2121587== For lists of detected and suppressed errors, rerun with: -s
==2121587== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

* using clint.py to check code style
```bash
clint.py *.cc *.c
```
```
Done processing test_linkedlist.cc
Done processing Assert007.c
Done processing LinkedList.c
Done processing Main.c
Done processing Sort.c
Total errors found: 0
```

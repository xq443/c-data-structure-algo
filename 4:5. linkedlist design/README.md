### a4 & a5 Summary
1. About:

- Design and implement a doubly-linked list, a linked list iterator, and robust memory allocation with memory leak error checking
- All integrated into a unit test development using the Google Test framework.


2. Project file directory:

- `Assert007.c`: This file contains the implementation of the Assert007 module.
- `Assert007.h`: It is the header file for the Assert007 module, defining its interface.
- `Assert007.o`: This object file is generated after compiling Assert007.c.
- `gtest-all.o`: An object file that contains the Google Test framework.
- `LinkedList.c`: Here lies the implementation of the LinkedList module.
- `LinkedList_easy.h`: This header file provides an easy-to-use interface for the LinkedList module.
- `LinkedList.h`: It's the primary header file for the LinkedList module, specifying its interface.
- `LinkedList.o`: After compiling LinkedList.c, this object file is generated.
- `Main.c`: This file serves as the main source file for the project.
- `Makefile`: The Makefile used for building the project.
- `README.md`: This Markdown file contains information and instructions about the project.
- `release-1.8.0.tar.gz`: It's a tarball archive containing the release of the Google Test framework.
- `test_linkedlist.cc`: Contains unit tests for the LinkedList module, adding additional unit tests.
- `test_linkedlist.o`: Object file generated after compiling test_linkedlist.cc.

3. Building and Running the Code:

* compile the code and verify 34 unit tests
```bash
make test
./test_suite
```
```
[----------] Global test environment tear-down
[==========] 34 tests from 15 test cases ran. (0 ms total)
[  PASSED  ] 34 tests.
```

* check memory leak error
```bash
valgrind --leak-check=full ./test_suite
```
```
==1026567== HEAP SUMMARY:
==1026567==     in use at exit: 0 bytes in 0 blocks
==1026567==   total heap usage: 901 allocs, 901 frees, 167,306 bytes allocated
==1026567== 
==1026567== All heap blocks were freed -- no leaks are possible
==1026567== 
==1026567== For lists of detected and suppressed errors, rerun with: -s
==1026567== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

* using clint.py to check code style
```bash
clint.py *.cc *.c
```

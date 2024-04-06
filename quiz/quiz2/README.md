### 1. About

Arraylist manipulation: add get remove

### 2. quiz2 directory 
- `arraylist.c` : Source code file containing the implementation of ArrayList functions
- `arraylist.h`: Header file declaring the interface of ArrayList functions- 
- `arraylist.o`: Object file generated after compiling arraylist.c
- `main.c`: Source code file containing the main function and program entry point
- `Makefile`: Makefile for compiling the program
- `README.md`: Markdown file containing information about the project

### 3. build and execute the codes
#### complile:
```
make all 
./list
```
#### memory leak check:
```
valgrind --leak-check=full ./list
```
```
==3026248== HEAP SUMMARY:
==3026248==     in use at exit: 0 bytes in 0 blocks
==3026248==   total heap usage: 9 allocs, 9 frees, 1,106 bytes allocated
==3026248== 
==3026248== All heap blocks were freed -- no leaks are possible
==3026248== 
==3026248== For lists of detected and suppressed errors, rerun with: -s
==3026248== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
#### clint style check
```
clint.py *.c
```
```
Done processing arraylist.c
Done processing main.c
Total errors found: 0
```

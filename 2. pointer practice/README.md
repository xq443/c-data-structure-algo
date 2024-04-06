### 1. Project Summary
- The assignment focuses on practical exercises involving structs, strings, header files, and functions in C programming. 
- It also involves exercise about the pointers with implementation of local and heap memory allocation and deallocation.

### 2. Building and Running the Code
#### Build Commands
```bash
gcc a2_test.c a2.c a2.h -o a2_executable
./a2_executable
```
or 
```bash
make run
```
### 3. Files in the Directory
- pointers.c: Practice file for working with pointers.
- a2_test.c: Test file.
- a2.c: Implementation file.
- a2.h: Header file.
- Makefile: Makefile for running tests.

### 4. Input and Output
- Big(Name *name): Prints the string <first> <middle> <last> or <first> <last> if the middle name is NULL.
- Last(Name *name):Prints the string <last>, <first>.
- Reg(Name *name): Prints the string <first> <last>.
- Mid(Name *name): Prints the string <first> <middle-initial>. <last> or <first> <last> if the middle name is NULL.
- Small(Name *name): Prints the string <first> only.
- FormatName(Name *name, char format): Given a format char, prints the name in the specified format. Mapping: 'B' -> 'big', 'L' -> 'last', 'R' -> 'reg', 'M' -> 'mid', 'S' -> 'small'.
- FillName(Name *name, char format, char *dest): Given a name, a format, and a destination array, puts the properly formatted name in the destination array without printing on the screen.

### 4. References
- Reading materials by Nick Parlante and Yale Notes.

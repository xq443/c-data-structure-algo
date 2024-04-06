### 1. Summary
1.  Design double linkedlist and implementation: 

- addLeft()/removeLeft()
- addRight()/removeRight()
- insertAt(int index)
- removeAt(int index)
- hasValue(int i)

2. Design deque on top of double linkedlist and implementation:

- pushLeft(int i)
- peekLeft() - fetches the next left node but does not remove it
- popLeft() - fetches and removes the left node
- pushRight(int i)
- peekRight() - fetches the next right node but does not remove it
- popRight() - fetches and removes the right node

### 2. File Directory:
- Design logic: node -> doublelinkedlist -> deque
- `Makefile`: Makefile for building the deque.
- `deque.c`: Implementation of deque functions.
- `deque.h`: Header file declaring deque functions.

- `doublelinkedlist.c`: Implementation of double-linked list functions.
- `doublelinkedlist.h`: Header file declaring double-linked list functions.

- `node.c`: Implementation of node functions.
- `node.h`: Header file declaring node functions.


- `testdeque.c`: Test file for deque functionality.
- `testdoubly.c`: Test file for double-linked list functionality.
- `README.md`: Documentation for the project.

### 3. Learning and Challenges:
- Memory Leaks and Invalid Memory Access:

In the freeAllMemory and freeListMemory functions, I need to make sure to update the pointers properly while deallocating memory to avoid memory leaks.

- Testing and Segmentation Faults:

Make sure to increment/decrement the size when push/pop the element.

- Separation Concerns:

Consider separating the interface (declarations) from the implementation (definitions) in three header files, including node.h, doublelinkedlist.h and deque.h. This improves code organization and modularity for function design and implementation.

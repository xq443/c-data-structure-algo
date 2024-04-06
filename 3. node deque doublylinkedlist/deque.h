#ifndef DEQUE_H
#define DEQUE_H
#include "doublelinkedlist.h"

typedef struct {
    DoubleLinkedList* list;
} Deque;

Deque* createDeque();
void pushLeft(Deque* deque, int value);
void pushRight(Deque* deque, int value);
int popLeft(Deque* deque);
int popRight(Deque* deque);
int peekLeft(Deque* deque);
int peekRight(Deque* deque);
void freeDequeMemory(Deque* deque);

#endif


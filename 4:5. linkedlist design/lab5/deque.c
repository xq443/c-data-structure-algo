#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "doublelinkedlist.h"
typedef struct Deque{
    DoubleLinkedList* list;
}Deque;

Deque* createDeque(){
    Deque* deque = (Deque*)malloc(sizeof(Deque));
    deque->list = createList();
    return deque;
}

void pushLeft(Deque* deque, int i){
    addLeft(deque->list, i);
}
void pushRight(Deque* deque, int i){
    addRight(deque->list, i);
}

//fetches the next left node but does not remove it
int peekLeft(Deque* deque) {
    if(deque->list->size <= 0){
        printf("no elements in the deque");
        exit(EXIT_FAILURE);
    }
    return deque->list->head->value;
}

//fetches the next right node but does not remove it
int peekRight(Deque* deque) {
    if(deque->list->size <= 0){
        printf("no elements in the deque");
        exit(EXIT_FAILURE);
    }
    return deque->list->tail->value;
}

//fetches and removes the left node
int popLeft(Deque* deque) {
    if(deque->list->size <= 0){
        printf("no elements in the deque");
        exit(EXIT_FAILURE);
    }
    int ret = deque->list->head->value;
    removeLeft(deque->list);
    return ret;  
}
//fetches and removes the right node
int popRight(Deque* deque) {
    if(deque->list->size <= 0){
        printf("no elements in the deque");
        exit(EXIT_FAILURE);
    }
    int ret = deque->list->tail->value;
    removeRight(deque->list);
    return ret;  
}

void freeDequeMemory(Deque* deque) {
    freeListMemory(deque->list);
    free(deque);
}

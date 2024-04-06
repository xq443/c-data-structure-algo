#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

typedef struct Node {
    int value;
    struct Node* next;
    struct Node* prev;
}Node;


typedef struct DoubleLinkedList{
    Node* head;
    Node* tail;
    int size;
}DoubleLinkedList;

Node* createNode(int value);
DoubleLinkedList* createList();
void addLeft(DoubleLinkedList* list, int val);
void removeLeft(DoubleLinkedList* list);
void addRight(DoubleLinkedList* list, int val);
void removeRight(DoubleLinkedList* list);
void insertAt(DoubleLinkedList* list, int index, int val);
void removeAt(DoubleLinkedList* list, int index);
bool hasValue(DoubleLinkedList* list, int i);
void printList(DoubleLinkedList* list);
void freeListMemory(DoubleLinkedList* list);


#endif

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "node.h"

typedef struct DoubleLinkedList{
    Node* head;
    Node* tail;
    int size;
}DoubleLinkedList;

DoubleLinkedList* createList(){
    DoubleLinkedList* doubleLinkedList = (DoubleLinkedList*)malloc(sizeof(DoubleLinkedList));
    doubleLinkedList->size = 0;
    doubleLinkedList->head = NULL;
    doubleLinkedList->tail = NULL;
    return doubleLinkedList;
}

void addLeft(DoubleLinkedList* list, int val){
    Node* node = createNode(val);
    if (list->size == 0) {
        list->head = node;
        list->tail = node;
    } else {
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
    }
    list->size++;
}
void removeLeft(DoubleLinkedList* list){
    if(list->size == 0){
        printf("trying to remove from an empty doublelinkedlist.");
        exit(EXIT_FAILURE);
    }else if(list->size == 1){
        list->size = 0;
        list->head = NULL;
        list->tail = NULL;
        free(list->head);
        free(list->tail);
        return;
    }
    //size>=2
    Node* head = list->head;
    list->head = head->next;
    list->head->prev = NULL;
    head->next = NULL;
    list->size--;
    free(head);
    return;
}
void addRight(DoubleLinkedList* list, int val){
    Node* node = createNode(val);
    if (list->size == 0) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        node->prev = list->tail;
        list->tail = node;
    }
    list->size++;
}
void removeRight(DoubleLinkedList* list){
    if(list->size == 0){
        printf("trying to remove from an emptry doublelinkedlist");
        exit(EXIT_FAILURE);
    }else if(list->size == 1){
        list->head = NULL;
        list->tail = NULL;
        free(list->tail);
        free(list->head);
        list->size = 0;

        return;
    }
    //size >= 2
    Node* tail = list->tail;
    list->tail = tail->prev;
    list->tail->next = NULL;
    list->size--;
    free(tail);
    return;
}

void insertAt(DoubleLinkedList* list, int index, int val) {
    if (index > list->size || index < 0) {
        printf("invalid index");
        exit(EXIT_FAILURE);
    }

    if (index == 0) {
        addLeft(list, val);
    } else if (index == list->size) {
        addRight(list, val);
    } else {
        // 0 < index < list->size
        // search from the left side
        Node* node = createNode(val);
        int currIdx = 0;
        Node* prev = NULL;
        Node* curr = list->head;

        while (currIdx != index) {
            prev = curr;
            curr = curr->next;
            currIdx++;
        }

        prev->next = node;
        node->prev = prev;
        node->next = curr;
        curr->prev = node;

        list->size++;
    }
}

/**
 * removeAt:
 * index ranges from 0 to list->size inclusively
 * we can insert at the beginning or at the very last
*/

void removeAt(DoubleLinkedList* list, int index){
    if(index> list->size || index < 0){
        printf("invalid index");
        exit(EXIT_FAILURE);
    }
    //remove the only element
    if(index == 0){
        removeLeft(list);
        return;
    }else if(index == list->size - 1){
        removeRight(list);
        return;
    }
    //0 < index < list->size - 1
    int currIdx = 0;
    Node* prev = NULL;
    Node* curr = list->head;
    while(currIdx != index){
        prev = curr;
        curr = curr->next;
        currIdx++;
    }
    prev->next = curr->next;
    curr->next->prev = prev;
    list->size--;
    free(curr);

    return; 
}

bool hasValue(DoubleLinkedList* list, int i){
    Node* curr = list->head;
    while(curr != NULL){
        if(curr->value == i){
            return true;
        }
        curr = curr->next;   
    }
    return false;
}
void printList(DoubleLinkedList* list){
    if(list->size == 0){
        printf("No elements in the list");
    }
    Node* head = list->head;
    while(head != NULL){
        printf("%d ", head->value);
        head = head->next;
    }
}

void freeAllMemory(DoubleLinkedList* list) {
    Node* current = list->head;
    Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

void freeListMemory(DoubleLinkedList* list) {
    Node* curr = list->head;
    while (curr != NULL) {
        Node* next = curr->next; 
        free(curr);
        curr = next;  
    }
    free(list);
}

#include<stdio.h>
#include<stdlib.h>
#include "node.h"

typedef struct L_List {
    L_Node* head;
    int size;
}L_List;

L_List* createList() {
    L_List* list = (L_List*)malloc(sizeof(L_List));
    list->size = 0;
    list->head = NULL;
    return list;
}

void addNode(L_List* list, L_Node* node){
    if(list->size == 0){//list is empty
        list->head = node;
        list->size = 1;
        return;
    }
    L_Node* curr = list->head;
    while(curr->next != NULL){
        curr = curr->next;
    }
    curr->next = node;
    list->size++;
    return;

}
void addVal(L_List* list, int value) {
    L_Node* node = createNode(value);
    addNode(list, node);
}

void removeNodeAt(L_List* list, int index) {
    if(list->size <= index){
        printf("trying to remove from null pointer location.\n");
        exit(EXIT_FAILURE);
    }
    L_Node* head = list->head;
    if(index == 0){
        list->head = head->next;
        free(head);
        list->size--;
        return;
    }
    L_Node* prev = head;
    L_Node* curr = head->next;
    int currIdx = 1;
    while(currIdx != index){
        if(currIdx > list->size){
            printf("the current index is invalid.\n");
            exit(EXIT_FAILURE);
        }
        prev = prev->next;
        curr = curr->next;
        currIdx++;
    }
    prev->next = curr->next;
    free(curr);
    list->size--;
    return;
}

void removeAllNodesWithValue(L_List* list, int value) {
    if(list->head == NULL){
        printf("trying to remove from an empty list.\n");
        exit(EXIT_FAILURE);
    }
    if(list->head->value == value){//if the first element is the value
        removeNodeAt(list, 0);
        return;
    }
    //check from the second element
    L_Node* prev = list->head;
    L_Node* curr = list->head->next;
    int currIdx = 1;

    while(curr != NULL){
        if(curr->value == value){
            removeNodeAt(list, currIdx);
            return;

        }else{
            prev = prev->next;
            curr = curr->next;
            currIdx++;
        }
    }
    return;
}

void printList(L_List* list){
    L_Node* current = list->head;

    while (current != NULL) {
        printf("%d\n", current->value);
        current = current->next;
    }
}

void freeAllMemory(L_List* list) {
    L_Node* current = list->head;
    L_Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    free(list);
}

int main() {

    L_List* l1 = createList();
    L_Node* n1 = createNode(1);
    addNode(l1, n1);
    addVal(l1, 2);
    addVal(l1, 3);
    printList(l1);

    removeNodeAt(l1, 0);
    printList(l1);
    removeAllNodesWithValue(l1, 3);
    printList(l1);

    removeNodeAt(l1, 0);
    printList(l1);
  
    freeAllMemory(l1);
    return 0;
}

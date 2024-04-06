#include "LinkedList_easy.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Function to create a new linked list node
LinkedListNode* CreateLinkedListNode(char* data) {
    LinkedListNode* node = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    if (node != NULL) {
        node->payload = data;
        node->next = NULL;
        node->prev = NULL;
    }
    return node;
}

// Function to destroy a linked list node
int DestroyLinkedListNode(LinkedListNode* node) {
    if (node == NULL)
        return 1;
    free(node->payload);
    free(node);
    return 0;  // Returns 0 if the destroy was successful
}

// Function to remove an element from the linked list
int RemoveLLElem(LinkedList list, LinkedListNodePtr ptr) {
    if (list == NULL || ptr == NULL || list->head == NULL)
        return 1;
    // the element to remove is in the head position
    if (ptr == list->head) {
        list->head = ptr->next;
        if (list->head != NULL)
            list->head->prev = NULL;
        else
            // Update the tail if the list becomes empty
            list->tail = NULL;
    // the element to remove is in the tail position
    } else if (ptr == list->tail) {
        list->tail = ptr->prev;
        if (list->tail != NULL)
            list->tail->next = NULL;
    } else {
        ptr->prev->next = ptr->next;
        ptr->next->prev = ptr->prev;
    }
    DestroyLinkedListNode(ptr);
    list->num_elements--;
    return 0;
}

// Function to create a new linked list
LinkedList CreateLinkedList() {
    LinkedList list = (LinkedList)malloc(sizeof(LinkedListHead));
    if (list != NULL) {
        list->num_elements = 0;
        list->head = NULL;
        list->tail = NULL;
    }
    return list;
}

// Function to destroy a linked list
int DestroyLinkedList(LinkedList list) {
    if (list == NULL)
        return 1;
    while (list->head != NULL) {
        LinkedListNode* nodeToRemove = list->head;
        list->head = nodeToRemove->next;
        DestroyLinkedListNode(nodeToRemove);
    }
    free(list);
    return 0;
}

// Function to get the number of elements in the linked list
unsigned int NumElementsInLinkedList(LinkedList list) {
    if (list != NULL)
        return list->num_elements;
    return 0;
}

// Function to insert an element into the linked list
int InsertLinkedList(LinkedList list, char* data) {
    if (list == NULL || data == NULL)
        return 1;
    LinkedListNode* node = CreateLinkedListNode(data);
    if (node == NULL)
        return 1;

    if (list->head != NULL) {
        // Adjust pointers to insert the new node at the head of the list
        list->head->prev = node;
        node->next = list->head;
    } else {
        // If the list is empty, set the new node as both head and tail
        list->tail = node;
    }

    list->head = node;
    list->num_elements++;
    return 0;
}

// Function to remove and return the element from the head of the linked list
int PopLinkedList(LinkedList list, char** dataPtr) {
    if (list == NULL || list->head == NULL || dataPtr == NULL)
        return 1;
    // Copy payload and dereference dataPtr to the value it points to
    *dataPtr = list->head->payload;
    // Check if memory allocation failed
    if (*dataPtr == NULL)
        return 1;
    // Remove the head node
    RemoveLLElem(list, list->head);
    return 0;
}

// Function to swap two elements in an array
void swap(char* arr[], int i, int j) {
    char* temp = arr[j];
    arr[j] = arr[i];
    arr[i] = temp;
}

// Function to partition an array in ascending order
int partitionInAsc(char* arr[], int low, int high) {
    char* pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (strcmp(arr[j], pivot) < 0) {
            i++;
            swap(arr, i, j);
        }
    }
    swap(arr, i + 1, high);
    return (i + 1);
}

// Function to partition an array in descending order
int partitionInDesc(char* arr[], int low, int high) {
    char* pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        // take pointers as args
        if (strcmp(arr[j], pivot) > 0) {
            i++;
            swap(arr, i, j);
        }
    }
    swap(arr, i + 1, high);
    return (i + 1);
}

// Function to perform quicksort on a string array
void quickSort(char* arr[], int low, int high, int ascending) {
    if (low < high) {
        int pivot;
        if (ascending)
            pivot = partitionInAsc(arr, low, high);
        else
            pivot = partitionInDesc(arr, low, high);
        quickSort(arr, low, pivot - 1, ascending);
        quickSort(arr, pivot + 1, high, ascending);
    }
}

// Function to sort a linked list
void SortLinkedList(LinkedList list, unsigned int ascending) {
    // corner case
    if (list == NULL || list->head == NULL || list->head->next == NULL)
        return;
    int n = list->num_elements;
    // convert the list into array pointer
    // a pointer to pointer of payload,  making it an array of strings
    char** arr = (char**)malloc(n * sizeof(char*));
    LinkedListNode* curr = list->head;
    // assign the value of array into linkedlist as its payload
    for (int i = 0; i < n; i++) {
        arr[i] = curr->payload;
        curr = curr->next;
    }
    quickSort(arr, 0, n - 1, ascending);

    curr = list->head;
    for (int i = 0; i < n; i++) {
        curr->payload = arr[i];
        curr = curr->next;
    }
    free(arr);
}

// Function to create a new linked list iterator
LLIter CreateLLIter(LinkedList list) {
    // corner case
    if (list == NULL)
        return NULL;
    // Allocate dynamic memory for the iterator
    LLIter iterator = (LLIter)malloc(sizeof(LLIterSt));
    if (iterator != NULL) {
        iterator->list = list;
        iterator->cur_node = list->head;
    }
    return iterator;
}

// Function to check if the linked list iterator has next element
int LLIterHasNext(LLIter iter) {
    if (iter->cur_node == NULL || iter->cur_node->next == NULL)
        return 0;
    return 1;
}

// Function to check if the linked list iterator has previous element
int LLIterHasPrev(LLIter iter) {
    if (iter->cur_node == NULL || iter->cur_node->prev == NULL)
        return 0;
    return 1;
}

// Function to move the linked list iterator to the next element
int LLIterNext(LLIter iter) {
    if (iter != NULL && LLIterHasNext(iter)) {
        if (iter->cur_node->next != NULL) {
            iter->cur_node = iter->cur_node->next;
            return 0;
        } else {
            iter->cur_node = NULL;
            return 1;
        }
    }
    return 1;
}

// Function to move the linked list iterator to the previous element
int LLIterPrev(LLIter iter) {
    if (iter != NULL && LLIterHasPrev(iter)) {
        if (iter->cur_node->prev != NULL) {
            iter->cur_node = iter->cur_node->prev;
            return 0;  // Successful move to previous node
        } else {
            iter->cur_node = NULL;
            return 1;
        }
    }
    return 1;
}

int LLIterGetPayload(LLIter iter, char** payload) {
    if (iter != NULL && iter->cur_node != NULL) {
        *payload = iter->cur_node->payload;
        return 0;
    }
    return 1;
}

int LLIterDelete(LLIter iter) {
    if (iter == NULL || iter->list == NULL || iter->cur_node == NULL) return 1;
    LinkedList list = iter->list;
    LinkedListNodePtr nodeToRemove = iter->cur_node;
    // Invalid and cannot be used (but must be freed)
    // if only one element in the list
    if (list->head == list->tail) {
        list->head = NULL;
        list->tail = NULL;
        DestroyLLIter(iter);
        return 1;  // The deletion succeeded, but the list is now empty
    }

    // Delete the head node
    if (nodeToRemove == list->head) {
        list->head = nodeToRemove->next;
        if (list->head != NULL) list->head->prev = NULL;
    } else if (nodeToRemove == list->tail) {  // Delete the tail node
        list->tail = nodeToRemove->prev;
        if (list->tail != NULL) list->tail->next = NULL;
    } else {  // Delete the node in the middle
        LinkedListNodePtr prev = nodeToRemove->prev;
        LinkedListNodePtr next = nodeToRemove->next;
        prev->next = next;
        next->prev = prev;
    }
    iter->cur_node = nodeToRemove->next;  // Move iterator to the next node
    DestroyLinkedListNode(nodeToRemove);  // Free memory for the node
    list->num_elements--;

    // Free memory for the list if it becomes empty
    if (list->head == NULL) {
        free(list);
    }
    return 0;
}

int LLIterInsertBefore(LLIter iter, char* payload) {
    if (!iter || !iter->list || !iter->cur_node || !payload) return 1;
    LinkedList list = iter->list;
    LinkedListNodePtr curr = iter->cur_node;

    // Create new node
    LinkedListNodePtr newNode = CreateLinkedListNode(payload);
    if (!newNode) return 1;  // Out of memory

    // Adjust pointers
    newNode->next = curr;
    newNode->prev = curr->prev;
    curr->prev = newNode;

    // If newNode is not the head node
    if (newNode->prev != NULL) {
        newNode->prev->next = newNode;
    } else {
        list->head = newNode;  // If newNode is the head node
    }
    list->num_elements++;
    return 0;
}

int DestroyLLIter(LLIter iter) {
    if (iter == NULL) return 1;  // Check for NULL pointer
    if (iter->list != NULL) DestroyLinkedList(iter->list);
    free(iter);
    return 0;
}
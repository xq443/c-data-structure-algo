#include<stdio.h>
#include<stdlib.h>
#include"arraylist.h"

/**
 * Retrieves the value at the specified index in the ArrayList.
 *
 * @param list Pointer to the ArrayList
 * @param index Index of the element to retrieve
 * @return Value at the specified index, or NULL if index is out of bounds
 */
char* get(ArrayList* list, int index) {
    // edge case : index out of bouind
    if (index < 0 || index >= list->size) {
        printf("Get the index out of bound\n");
        return NULL;
    };
    return list->nodes[index]->value;
}

/**
 * Removes the element at the specified index from the ArrayList.
 *
 * @param list Pointer to the ArrayList
 * @param index Index of the element to remove
 */
void removeAt(ArrayList* list, int index) {
    // edge case: index out of bound
    if (index < 0 || index >= list->size) {
        printf("Remove at the index out of bound\n");
        EXIT_FAILURE;
    }

    // Free the memory allocated for the node removed
    free(list->nodes[index]->value);  // Free the value stored in the node
    free(list->nodes[index]);  // Free the node itself

    // Shift elements to the left
    for (int i = index; i < list->size - 1; i++) {
        list->nodes[i] = list->nodes[i + 1];
    }

    // Decrement the size
    list->size--;
}

/**
 * Creates a new ArrayList with the specified initial size.
 *
 * @param size Initial size of the ArrayList
 * @return Pointer to the newly created ArrayList
 */
ArrayList* create(int size) {
    ArrayList* list = (ArrayList*)malloc(sizeof(ArrayList));
    Node** nodes = (Node**)malloc(sizeof(Node*) * size);
    list->nodes = nodes;
    list->size = 0;
    return list;
}

/**
 * Adds a new element with the specified value to the end of the ArrayList.
 *
 * @param list Pointer to the ArrayList
 * @param value Value to add to the ArrayList
 * @return Pointer to the ArrayList after adding the element
 */
ArrayList* add(ArrayList* list, char* value) {
    // Allocate the dynamic memory for the new inserted node
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;

    // Add the new node to the end of the arrayList
    list->nodes[list->size] = newNode;

    // Increment the size
    list->size++;
    return list;
}

/**
 * Destroys the ArrayList and frees up memory.
 *
 * @param list Pointer to the ArrayList to be destroyed
 */
void destroyList(ArrayList* list) {
    int i;
    for (i = 0; i < list->size; i++) {
       free(list->nodes[i]->value);
       destroyNode(list->nodes[i]);
    }
    free(list->nodes);
    free(list);
}

/**
 * Destroys a single node and frees up memory.
 *
 * @param node Pointer to the node to be destroyed
 */
void destroyNode(Node* node) {
    free(node);
    return;
}

/**
 * Returns the current size of the ArrayList.
 *
 * @param list Pointer to the ArrayList
 * @return Current size of the ArrayList
 */
int size(ArrayList* list) {
    return list->size;
}

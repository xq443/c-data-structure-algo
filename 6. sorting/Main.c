#include <stdio.h>
#include "Sort.h"
#include "LinkedList_easy.h"
#include <time.h>
#include <stdlib.h>
#include <inttypes.h>

#define NUM_RANDOM_NUMBERS 50

// Generate and insert 50 random numbers into the linked list
LinkedList GenerateRanList() {
    LinkedList list = CreateLinkedList();

    // Set the upper and lower bounds for random numbers
    uint64_t upper_bound = 1000;
    uint64_t lower_bound = 100;
    // Generate a seed based on current time
    unsigned int seed = (unsigned int)time(NULL);
    for (int i = 0; i < NUM_RANDOM_NUMBERS; i++) {
        uint64_t* value = (uint64_t*)malloc(sizeof(uint64_t));
        *value = (uint64_t)rand_r(&seed) % (upper_bound
            - lower_bound + 1) + lower_bound;

        // Insert the value into the list
        InsertLinkedList(list, value);
    }
    return list;
}


void DestroyRanList(LinkedList list) {
    if (list == NULL)
        return;
    while (list->head != NULL) {
        LinkedListNode* nodeToRemove = list->head;
        list->head = nodeToRemove->next;
        // DestroyLinkedListNode(nodeToRemove);
        free(nodeToRemove->payload);
        free(nodeToRemove);
    }
    free(list);
}

int main() {
    srand(time(NULL));

    // insertion sort
    LinkedList list1 = GenerateRanList();
    printf("Given list1 is: ");
    PrintLinkedList(list1);
    SortInsertion(&list1);
    printf("\nSelection Sorted list1 is: ");
    PrintLinkedList(list1);
    printf("%lu\n", *(uint64_t*)(list1->tail->payload));
    printf("\n");
    DestroyRanList(list1);

    // selection sort
    LinkedList list2 = GenerateRanList();
    printf("Given list2 is: ");
    PrintLinkedList(list2);
    SortMerge(&list2);
    printf("\nSelection Sorted list2 is: ");
    PrintLinkedList(list2);
    printf("%lu\n", *(uint64_t*)(list2->tail->payload));
    printf("\n");
    DestroyRanList(list2);

    // merge sort
    LinkedList list3 = GenerateRanList();
    printf("Given list3 is: ");
    PrintLinkedList(list3);
    SortMerge(&list3);
    printf("\nMerge Sorted list3 is: ");
    PrintLinkedList(list3);
    printf("%lu\n", *(uint64_t*)(list3->tail->payload));
    DestroyRanList(list3);

    return 0;
}

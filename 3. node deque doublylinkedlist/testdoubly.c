#include <stdio.h>
#include <stdbool.h>
#include "doublelinkedlist.h"

int main() {
    DoubleLinkedList* l1 = createList();

    // Add elements to the list -> 3 1 2
    addLeft(l1, 1);
    addRight(l1, 2);
    addLeft(l1, 3);


    printf("Original List: ");
    printList(l1);
    printf("\n");

    //manipulate the list -> 1 5 2 4
    removeLeft(l1);
    addRight(l1, 4);
    insertAt(l1, 1, 5);

    printf("Updated List: ");
    printList(l1);
    printf("\n");

    // Check if a value exists in the list
    int searchvalue = 4;
    if (hasValue(l1, searchvalue)) {
        printf("%d exists in the list.\n", searchvalue);
    } else {
        printf("%d does not exist in the list.\n", searchvalue);
    }

    // Free the memory allocated for the list
    freeListMemory(l1);

    return 0;
}


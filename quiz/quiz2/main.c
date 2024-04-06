#include<stdio.h>
#include <string.h>
#include<stdlib.h>
#include"arraylist.h"

int main() {
    //  Create a new ArrayList
    ArrayList* list = create(3);

    //  Add elements to the list
    char* data1 = strdup("test1");
    char* data2 = strdup("test2");
    char* data3 = strdup("test3");
    add(list, data1);
    add(list, data2);
    add(list, data3);

    // print the elements of the list
    printf("Elements of the List are:\n");
    for (int i = 0; i < list->size; i++) {
        printf("%s\n", get(list, i));
    }

    // Remove an element from the ArrayList
    removeAt(list, 1);  // 1 3
    removeAt(list, 1);  // 1

    // Display the elements of the ArrayList after removal
    printf("\nElements of the List after removal:\n");
    for (int i = 0; i < list->size; i++) {
        printf("%s\n", get(list, i));
    }

    //  Destroy the ArrayList
    destroyList(list);
    return 0;
}

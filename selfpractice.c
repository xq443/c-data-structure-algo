// #include<stdio.h>

// /**
//  Function start 
//  **/

// // implement your function here
// int calculateSum(int nums[], int size) {
//     int sum = 0;
//     for (int i = 0; i < size; i++) {
//         sum += nums[i];
//     }
//     return sum;
// }

// /**
//  Function end 
//  **/

// int main() {
//     int nums[] = {1, 2, 3, 4, 5}; // Sample array, you can change this
//     int size = sizeof(nums) / sizeof(nums[0]); // Calculate the size of the array
//     int sum = calculateSum(nums, size); // Call the function to calculate sum
//     printf("Sum: %d\n", sum); // Print the sum
//     return 0;
// }

/**
 Structs start 
 **/

// typedef struct LinkedListNode {
//     int data;
//     struct LinkedListNode* next;
// } LinkedListNode;

// typedef struct LinkedList {
//     LinkedListNode head;
//     int size;
// } LinkedList;

// /**
//  Structs end
//  **/

// /**
//  Function start 
//  **/

// void printList( LinkedList* list) {
//      LinkedListNode* current = &(list->head); // Start from the head of the list
//     while (current != NULL) {
//         printf("%d ", current->data); // Print the data of the current node
//         current = current->next; // Move to the next node
//     }
//     printf("\n");
// }

// /**
//  Function end 
//  **/

// int main() {
//     LinkedListNode node = {1, NULL};
//     LinkedListNode node2 = {10, &node};
//     LinkedListNode node3 = {30, &node2};
//     int size = 3;

//     LinkedList list = {node3, size};

//     printList(&list);
//     return 0;
// }
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct KeyValue {
    char* key;
    int value;
} KeyValue;

typedef struct KeyValueNode {
    KeyValue* data;
    struct KeyValueNode* next;
} KeyValueNode;

typedef struct Map {
    KeyValueNode** keyValues;
    int size; // num of values in map
    int capacity; // total size of outer array
} Map;

int hash(char* key) {
    int hashValue = 0;
    int i = 0;
    while (key[i] != '\0') {
        hashValue += key[i];
        i++;
    }
    return hashValue;
}

Map* createMap(int capacity) {
    Map* map = (Map*)malloc(sizeof(Map));
    map->keyValues = (KeyValueNode**)malloc(capacity * sizeof(KeyValueNode*));
    map->size = 0;
    map->capacity = capacity;
    for (int i = 0; i < capacity; i++) {
        map->keyValues[i] = NULL;
    }
    return map;
}

bool containsKey(char* key, Map* map) {
    int index = hash(key) % map->capacity;
    KeyValueNode* node = map->keyValues[index];
    while (node != NULL) {
        if (strcmp(node->data->key, key) == 0) {
            return true;
        }
        node = node->next;
    }
    return false;
}

void insertKeyValue(Map* map, KeyValue* keyValue) {
    if (containsKey(keyValue->key, map)) {
        printf("Key %s already exists.\n", keyValue->key);
        return;
    }
    int index = hash(keyValue->key) % map->capacity;
    KeyValueNode* newNode = (KeyValueNode*)malloc(sizeof(KeyValueNode));
    newNode->data = keyValue;
    newNode->next = map->keyValues[index];
    map->keyValues[index] = newNode;
    map->size++;
}

int* flatten(Map* map) {
    int* res = (int*)malloc(map->size * sizeof(int));

    int index = 0;
    for (int i = 0; i < map->capacity; i++) {
        KeyValueNode* nodeAtIndex = map->keyValues[i];
        while (nodeAtIndex != NULL) {
            res[index++] = nodeAtIndex->data->value;
            nodeAtIndex = nodeAtIndex->next;
        }
    }
    return res;
}

void printArray(int arr[], int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main() {
    Map* map = createMap(10);

    KeyValue kv1 = {strdup("a"), 1};
    KeyValue kv2 = {strdup("b"), 2};
    KeyValue kv3 = {strdup("c"), 3};

    insertKeyValue(map, &kv1);
    insertKeyValue(map, &kv2);
    insertKeyValue(map, &kv3);

    int* flattened = flatten(map);
    printArray(flattened, map->size);
    free(flattened);

    // Free allocated memory
    for (int i = 0; i < map->capacity; i++) {
        KeyValueNode* node = map->keyValues[i];
        while (node != NULL) {
            KeyValueNode* temp = node;
            node = node->next;
            free(temp->data->key);
            //free(temp->data);
            free(temp);
        }
    }
    free(map->keyValues);
    free(map);

    return 0;
}

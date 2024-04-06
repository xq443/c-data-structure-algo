#include<stdio.h>
#include<stdlib.h>
#include "node.h"

Node* createNode(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->value = value;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

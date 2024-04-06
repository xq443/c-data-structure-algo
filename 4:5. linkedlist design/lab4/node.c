#include<stdio.h>
#include<stdlib.h>
#include "node.h"

L_Node* createNode(int value) {
    L_Node* node = (L_Node*)malloc(sizeof(L_Node));
    node->value = value;
    node->next = NULL;
    return node;
}

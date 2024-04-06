#ifndef NODE_H
#define NODE_H

typedef struct Node {
    int value;
    struct Node* next;
    struct Node* prev;
}Node;

Node* createNode(int value);

#endif

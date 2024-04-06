#ifndef header_file
#define header_file

typedef struct L_Node {
    int value;
    struct L_Node* next;
}L_Node;

L_Node* createNode(int value);

#endif

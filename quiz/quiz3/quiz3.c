//A Binary Search Tree is a tree where given a node `N`, `N.left` is less than N
//and N.right is greater than N.
//    3
//   / \
//  1   5
//    /   \
//   4     6
// the above is a valid bst.
// the below is not.
//    3
//   / \
//  1   2
//    /   \
//   4     6

//You're given a simple implementation of a BinaryTree. Write code that does the following:

//Q1. Implement the function `isBST(tree) => boolean`. `isBst` takes as argument a tree
//and returns true if it is a BST, false otherwise.
//Q2. Implement the function `findNumsBelow(bst, num) => int[]`. FindNum traverses a BST and returns
//all values less than num in an array.

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <limits.h>

typedef struct Node {
  int value;
  struct Node* left;
  struct Node* right;
}Node;

typedef struct Tree {
  Node* root;
  int size;
}Tree;

bool isBstDfs(Node* node, int min, int max) {
  // base case
  if(node == NULL) return true;
  // if left < node < right not satisfy, return false
  if(node->value < min || node->value > max) return false;

  // recursively check left and right subtrees and their subtrees.
  return isBstDfs(node->left, min, node->value) && 
  isBstDfs(node->right, node->value, max);
}

bool isBst(Tree* t) {
  // take min as INT_MIN, max as INT_MAX
  return isBstDfs(t->root, INT_MIN, INT_MAX);
}

void findNumsBelowHelper(Node* node, int num, int** ret, int* idx, int* size) {
  // base case
  if (node == NULL) return;
  // if node value < num : node should be on the left subtree
  if (node->value < num) {
    if(*idx == *size) {
      *size *= 2; // resize as double if reaching its capacity 
      int* temp = realloc(*ret, *size * sizeof(int));
      if(temp == NULL) exit(EXIT_FAILURE);
      *ret = temp; 
    }
    (*ret)[(*idx)++] = node->value; // add the node value to ret
    // recursively find the node left and right subtree
    // because right and left subtree both possibly have values smaller
    findNumsBelowHelper(node->left, num, ret, idx, size);
    findNumsBelowHelper(node->right, num, ret, idx, size);
  } else {
    // if node value is greater, then only check node's left subtree
    // node rightsubtree must be greater than num, so ignoret the case
    findNumsBelowHelper(node->left, num, ret, idx, size);
  }
}

int* findNumsBelow(Tree* t, int num, int* finalSize) {
  if(!isBst(t)) {
    printf("error: tree given is not a bst");
    return NULL;
  }
  // allocate the memory with initial size : t->size
  int* ret = (int*)malloc(t->size * sizeof(int));
  int index = 0, size = t->size;
  // call the helper function
  findNumsBelowHelper(t->root, num, &ret, &index, &size);
  // if we found some nums smaller then resize the ret array
  ret = (int*)realloc(ret, index * sizeof(int));
  // store the actual size
  *finalSize = index;
  return ret;
}

void printNodeRecursive(Node* n) {
  if(n == NULL) return;
  printf("%d\n", n->value);
  printNodeRecursive(n->left);
  printNodeRecursive(n->right);
}

void printTree(Tree* t) {
  printNodeRecursive(t->root);
}

void freeTree(Node* node) {
    if (node == NULL) return;
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

Node* createNode(int value) {
  Node* n1 = (Node*)malloc(sizeof(Node));
  n1->value = value;
  n1->left = NULL;
  n1->right = NULL;
}

Tree* createTree(Node* root) {
  Tree* t = (Tree*)malloc(sizeof(Tree));
  t->root = root;
  t->size = 1;
  return t;
}

Tree* getTestBst() {
  Node* n1 = createNode(10);
  Node* n2 = createNode(6);
  Node* n3 = createNode(13);
  Node* n4 = createNode(7);
  Node* n5 = createNode(5);

  n1->left = n2;
  n1->right = n3;
  n2->right = n4;
  n2->left = n5;

  Tree* t = createTree(n1);
  return t;
}

int main() {
  // testing isBST
  Node* n1 = createNode(10);
  n1->left = createNode(1);
  n1->right = createNode(11);
  Tree* t = createTree(n1);

  printTree(t);
  printf("Tree is BST: %s\n", isBst(t) ? "true" : "false");

  // testing findNumsBelow
  int num = 1; 
  int finalSize;
  int* result = findNumsBelow(t, num, &finalSize);
  if (result != NULL) {
    printf("Numbers below %d: ", num);
    for (int i = 0; i < finalSize; i++) {
      printf("%d ", result[i]);
    }
    printf("\n");
    free(result);
  } else {
    printf("No elements are founds smaller than %d\n", num);
  }
  // free memory
  freeTree(t->root);
  free(t);
  return 0;
}

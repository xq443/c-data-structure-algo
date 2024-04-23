#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>

// Structure for the node of the binary tree
typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
} Node;

// Structure for the binary tree
typedef struct Tree {
    Node* root;
    int size;
} Tree;

// Function to check if the tree is a valid binary search tree
bool isBstDfs(Node* node, int min, int max) {
    if(node == NULL) return true;
    if(node->value < min || node->value > max) return false;
    return isBstDfs(node->left, min, node->value) && 
           isBstDfs(node->right, node->value, max);
}

bool isBst(Tree* t) {
    return isBstDfs(t->root, INT_MIN, INT_MAX);
}

// Function to find all numbers below a certain value in a binary search tree
void findNumsBelowHelper(Node* node, int num, int** ret, int* idx, int* size) {
    if (node == NULL) return;
    if (node->value < num) {
        if(*idx == *size) {
            *size *= 2; // resize as double if reaching its capacity 
            int* temp = realloc(*ret, *size * sizeof(int));
            if(temp == NULL) exit(EXIT_FAILURE);
            *ret = temp; 
        }
        (*ret)[(*idx)++] = node->value;
        findNumsBelowHelper(node->left, num, ret, idx, size);
        findNumsBelowHelper(node->right, num, ret, idx, size);
    } else {
        findNumsBelowHelper(node->left, num, ret, idx, size);
    }
}

int* findNumsBelow(Tree* t, int num, int* finalSize) {
    if(!isBst(t)) {
        printf("error: tree given is not a bst");
        return NULL;
    }
    int* ret = (int*)malloc(t->size * sizeof(int));
    int index = 0, size = t->size;
    findNumsBelowHelper(t->root, num, &ret, &index, &size);
    ret = (int*)realloc(ret, index * sizeof(int));
    *finalSize = index;
    return ret;
}

// Function to print the tree nodes in pre-order
void printNodeRecursive(Node* n) {
    if(n == NULL) return;
    printf("%d\n", n->value);
    printNodeRecursive(n->left);
    printNodeRecursive(n->right);
}

// Function to print the entire tree in pre-order
void printTree(Tree* t) {
    printNodeRecursive(t->root);
}

// Function to free the memory allocated for the tree nodes
void freeTree(Node* node) {
    if (node == NULL) return;
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

// Function to create a new node with a given value
Node* createNode(int value) {
    Node* n1 = (Node*)malloc(sizeof(Node));
    n1->value = value;
    n1->left = NULL;
    n1->right = NULL;
    return n1;
}

// Function to insert a value into the binary search tree
void insert(Node** root, int value) {
    if (*root == NULL) {
        *root = createNode(value);
    } else {
        if (value < (*root)->value)
            insert(&((*root)->left), value);
        else
            insert(&((*root)->right), value);
    }
}

// Function to find the minimum value in a binary search tree
Node* findMin(Node* node) {
    while (node->left != NULL)
        node = node->left;
    return node;
}

// Function to delete a value from the binary search tree
Node* deleteNode(Node* root, int value) {
    if (root == NULL) return root;
    if (value < root->value)
        root->left = deleteNode(root->left, value);
    else if (value > root->value)
        root->right = deleteNode(root->right, value);
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        Node* temp = findMin(root->right);
        root->value = temp->value;
        root->right = deleteNode(root->right, temp->value);
    }
    return root;
}

// Function to search for a value in the binary search tree
bool search(Node* root, int value) {
    if (root == NULL) return false;
    if (root->value == value) return true;
    if (value < root->value)
        return search(root->left, value);
    else
        return search(root->right, value);
}

// Function to perform an in-order traversal of the binary search tree
void inOrderTraversal(Node* root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("%d ", root->value);
        inOrderTraversal(root->right);
    }
}

// Function to perform a pre-order traversal of the binary search tree
void preOrderTraversal(Node* root) {
    if (root != NULL) {
        printf("%d ", root->value);
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}

// Function to perform a post-order traversal of the binary search tree
void postOrderTraversal(Node* root) {
    if (root != NULL) {
        postOrderTraversal(root->left);
        postOrderTraversal(root->right);
        printf("%d ", root->value);
    }
}

// Function to create a new binary search tree
Tree* createTree() {
    Tree* t = (Tree*)malloc(sizeof(Tree));
    t->root = NULL;
    t->size = 0;
    return t;
}

// Function to create a sample binary search tree for testing
Tree* getTestBst() {
    Tree* t = createTree();
    insert(&(t->root), 10);
    insert(&(t->root), 6);
    insert(&(t->root), 13);
    insert(&(t->root), 7);
    insert(&(t->root), 5);
    return t;
}

int main() {
    // Testing binary search tree functionality
    Tree* t = getTestBst();

    printf("Tree is BST: %s\n", isBst(t) ? "true" : "false");

    int num = 10; 
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
        printf("No elements are found smaller than %d\n", num);
    }

    printf("In-order traversal: ");
    inOrderTraversal(t->root);
    printf("\n");

    printf("Pre-order traversal: ");
    preOrderTraversal(t->root);
    printf("\n");

    printf("Post-order traversal: ");
    postOrderTraversal(t->root);
    printf("\n");

    // Freeing memory
    freeTree(t->root);
    free(t);

    return 0;
}

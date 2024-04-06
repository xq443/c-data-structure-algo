#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//Local memory
void B(int* worthRef) { // reference parameter
    *worthRef = *worthRef + 1; // use * to get at value of interest // T2
    // B() uses a reference parameter -- a pointer to the value ofinterest. 
    // B() uses a dereference (*) on the reference parameter to get at the value of interest.
}
void A() {
    int netWorth;
    netWorth = 55; // T1 -- the value of interest is local to A()
    B(&netWorth);  // Pass a pointer to the value of interest.
               // In this case using &.
    // T3 -- B() has used its pointer to change the value of interest
}

//Pass by reference
void Swap(int* a, int* b) {
   int temp;
   temp = *a;
   *a = *b;
   *b = temp;
}
// Swap() Caller
// To call Swap(), the caller must pass pointers to the values of interest.
void SwapCaller() {
    int x = 1;
    int y = 2;
    Swap(&x, &y);  // Use & to pass pointers to the int values of interest (x and y).
}
void SwapCaller1(){
    int scores[10];
    scores[0] = 1;
    scores[9] = 10;
    Swap(&scores[0], &scores[9]);
}

//Heap memory
void Heap1(){
    int* intPtr;// Allocates local pointer local variable (but not its pointee)

    intPtr = malloc(sizeof(int));// Allocates heap block and stores its pointer in local variable.
    *intPtr = 42;// Dereferences the pointer to set the pointee to 42.

    free(intPtr);// Deallocates heap block making the pointer bad.
   // The programmer must remember not to use the pointer after the pointee has been deallocated.
}

// Define a struct for a Fraction
typedef struct Fraction {
    int numerator;
    int denominator;
}Fraction;

void HeapArray() {
   struct Fraction* fracts;
   int i;
   // allocate the array
   fracts = malloc(sizeof(struct Fraction) * 100);
   // use it like an array -- in this case set them all to 22/7
   for (i=0; i<99; i++) {
      fracts[i].numerator = 22;
      fracts[i].denominator = 7;
}
   // Deallocate the whole array
   free(fracts);
}

/*
 Given a C string, return a heap allocated copy of the string.
 Allocate a block in the heap of the appropriate size,
 copies the string into the block, and returns a pointer to the block.
 The caller takes over ownership of the block and is responsible
 for freeing it.
*/
char* StringCopy(const char* string) {
    char* newString;
    int len;
    len = strlen(string) + 1;
    newString = malloc(sizeof(char)*len);  // elem-size * number-of-elements
    assert(newString != NULL); // simplistic error check (a good habit)
    strcpy(newString, string); // copy the passed in string to the block
    return(newString);   // return a ptr to the block
}


int main() {
    // Test PointerTest
    // allocate three integers and two pointers
    int a = 1;
    int b = 2;
    int c = 3;
    int* p;
    int* q;

    p = &a; // set p to refer to a
    q = &b; // set q to refer to b

    c = *p;  // retrieve p's pointee value (1) and put it in c
    p = q;   // change p to share with q (p's pointee is now b)
    *p = 13;
    printf("Pointer p is: %p\n", p);
    printf("Pointer q is: %p\n", q);
    printf("a is: %d\n", a);
    printf("b is: %d\n", b);
    printf("c is: %d\n", c);

    // Test StringCopy
    const char* originalString = "Hello, World!";
    char* copiedString = StringCopy(originalString);

    printf("Original String: %s\n", originalString);
    printf("Copied String: %s\n", copiedString);

    // free the memory allocated by StringCopy
    free(copiedString);

    return 0;
}


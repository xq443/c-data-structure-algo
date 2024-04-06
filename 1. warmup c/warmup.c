#include <stdio.h>

int main() {
    // Approach 1: Three printf statements
    printf("VICTORY!\n");//if omitting a closing double quote, missing terminating character error message will occur
    printf("VICTORY!\n");
    printf("VICTORY!\n");

    // Approach 2: Using a for loop
    for (int i = 0; i < 3; i++) {
        printf("VICTORY!\n");
    }

    return 0;
}


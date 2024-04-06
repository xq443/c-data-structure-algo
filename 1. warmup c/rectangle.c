#include <stdio.h>

void PrintRectangle(int width, int height) {
    // Print top line
    for (int i = 0; i < width; i++) {
        printf("-");
    }
    printf("\n");

    // Print sides
    for (int i = 0; i < height - 2; i++) {
        printf("-");
        for (int j = 0; j < width - 2; j++) {
            printf(" ");
        }
        printf("-\n");
    }

    // Print bottom line
    for (int i = 0; i < width; i++) {
        printf("-");
    }
    printf("\n");
}

int main() {
    // Test the PrintRectangle function
    PrintRectangle(5, 4);

    return 0;
}


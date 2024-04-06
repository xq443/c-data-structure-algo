#include <stdio.h>

void PrintFancyRectangle(int width, int height, char symbol, int fill) {
    // Print top line
    for (int i = 0; i < width; i++) {
        printf("%c",symbol);
    }
    printf("\n");

    // Print left and right sides
    for (int i = 0; i < height - 2; i++) {
        printf("%c", symbol);
        if (fill) {
            for (int j = 0; j < width - 2; j++) {
                printf("%c", symbol);
            }
        } else {
            for (int j = 0; j < width - 2; j++) {
                printf(" ");
            }
        }
        printf("%c\n", symbol);
    }

    // Print bottom line
    for (int i = 0; i < width; i++) {
        printf("%c", symbol);
    }
    printf("\n");
}

int main() {
    // Test the PrintFancyRectangle function
    PrintFancyRectangle(5, 4, '+', 0);
    printf("\n");
    PrintFancyRectangle(5, 4, '*', 1);

    return 0;
}


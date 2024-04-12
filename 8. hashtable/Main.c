#include <stdio.h>
#include <stdlib.h>
int main() {
    
    // Open the file for reading
    FILE *file = fopen("words.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Read and print each line of the file
    char line[256]; // Buffer to store each line
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    // Close the file
    fclose(file);

    return EXIT_SUCCESS;
}

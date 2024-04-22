#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdint.h>
#include <stdlib.h>
#include <string.h>
#include "Hashtable_easy.h"

#define MAX_BUFFER 1024

int main() {
    
    // Open the file for reading
    FILE *file = fopen("words.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Read and print each line of the file
    char line[MAX_BUFFER]; // Buffer to store each line
    Hashtable ht = CreateHashtable(100);

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        char *word = strdup(line);
        PutInHashtable(ht, word);
    }

    // Close the file and generate anagrams
    fclose(file);
    GenerateAnagrams(ht);
    DestroyHashtable(ht);
    return EXIT_SUCCESS;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void parse(char *buffer) {
    char* rest = buffer;
    char* token;
    int first_token = 1;

    token = strtok_r(rest, " \n\"", &rest);

    if(strcmp(token, "exit") == 0){
        exit(0);  // terminate
    }

    // tokenize the input string
    while (token != NULL) {
        if (first_token) {
            first_token = 0;
            token = strtok_r(NULL, " \n\"", &rest); // Skip the first token
            continue;
        }

        int len = strlen(token);

        if (token[0] == '"') {
            printf("%.*s ", len - 1, token + 1);
        } else if (token[strlen(token) - 1] == '"') {
            printf("%.*s\n", len - 1, token);
        } else {
            printf("%s\n", token);
        }
        token = strtok_r(NULL, " \n\"", &rest); // iterate to next token
    }
}

int main(int argc, char** argv) {
    const int BUFFER_SIZE = 100;
    char buffer[BUFFER_SIZE];
    int complete = 1;

    while (complete) {
        printf("Enter your command: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        parse(buffer);
    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdbool.h>

#define MAXLINE 999

void PrintBlue(char* str) {
    printf("\033[1;94mCLIENT RECEIVED:\033[0m %s \n", str);
}

void PrintYellow(char* str) {
    printf("\033[1;93mCLIENT SENDING:\033[0m %s \n", str);
}

char* Fgets(char *ptr, int n, FILE *stream) {
    char *rptr;
    if (((rptr = fgets(ptr, n, stream)) == NULL) && ferror(stream)) {
        fprintf(stderr, "%s\n", "fgets error");
        exit(0);
    }
    return rptr;
}

void send_message(char *message, int sock_fd) {
    PrintYellow(message);
    write(sock_fd, message, strlen(message));
}

void read_response(int sock_fd) {
    char resp[MAXLINE];
    int len = read(sock_fd, resp, MAXLINE);
    resp[len] = '\0';  // Null-terminate the received data
    if (len == -1) {
        perror("read");
        return;
    }
    PrintBlue(resp);
}

int main() {
    struct addrinfo hints, *result;

    // Allows "global"
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET; /* IPv4 only */
    hints.ai_socktype = SOCK_STREAM; /* TCP */
    int s;
    s = getaddrinfo("localhost",  // 127.0.0.1
                    "1234",  // port
                    &hints,
                    &result);
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    connect(sock_fd, result->ai_addr, result->ai_addrlen);
    while (1) {
        char buffer[MAXLINE];
        printf("Enter your message: ");
        // Read input from user
        Fgets(buffer, MAXLINE, stdin);
        send_message(buffer, sock_fd);
        if (buffer[0] == 'x' && strlen(buffer) == 2 && buffer[1] == '\n') {
            printf("BREAKING CONNECTION AND TERMINATING\n");
            break;  // Terminate
        }
        read_response(sock_fd);
        char repeat_count[MAXLINE];

        // Read input from user and validation
        bool valid_input = false;
        while (!valid_input) {
            printf("Enter your choice of repeating: ");
            Fgets(repeat_count, MAXLINE, stdin);
            repeat_count[strcspn(repeat_count, "\n")] = '\0';
            char* endptr;
            strtol(repeat_count, &endptr, 10);  // Convert input to integer
            if (*endptr == '\0') {
                valid_input = true;  // Input is a valid integer
            } else {
                printf("Invalid input. Please enter an integer.\n");
            }
        }
        send_message(repeat_count, sock_fd);
        read_response(sock_fd);
    }
    close(sock_fd);
    return 0;
}

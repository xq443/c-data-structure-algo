#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>

// Function prototypes
void receive_message(int client_fd) {
    char buffer[1000];
    int len = read(client_fd, buffer, sizeof(buffer) - 1);
    buffer[len] = '\0';
    printf("\033[1;93mSERVER RECEIVED:\033[0m %s \n", buffer);
}

void send_message(char *msg, int sock_fd) {
    printf("\033[1;94mSERVER SENDING: \033[0m%s", msg);
    printf("===\n");
    write(sock_fd, msg, strlen(msg));
}

int server_socket;  // Global variable to store server socket descriptor

void handle_sigint(int sig) {
    printf("Received SIGINT. Closing server...\n");
    close(server_socket);  // Close the server socket
    exit(0);  // Exit the program
}

int do_open() {
    int s;

    // Step 1: Get Address stuff
    struct addrinfo hints, *result;

    // Setting up the hints struct...
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    s = getaddrinfo("localhost", "7533", &hints, &result);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(1);
    }

    // Step 2: Create the socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Set socket option to reuse address
    int yes = 1;
    if (setsockopt(server_socket, SOL_SOCKET,
    SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
        perror("setsockopt");
        exit(1);
    }

    // Step 3: Bind the socket
    if (bind(server_socket, result->ai_addr, result->ai_addrlen) != 0) {
        perror("bind()");
        exit(1);
    }

    // Step 4: Listen
    if (listen(server_socket, 10) != 0) {
        perror("listen()");
        exit(1);
    }

    struct sockaddr_in *result_addr = (struct sockaddr_in *) result->ai_addr;
    printf("Listening on file descriptor %d, port %d\n",
    server_socket, ntohs(result_addr->sin_port));

    // Infinite loop to keep the server listening for multiple clients
    while (1) {
        // Step 5: Accept a connection
        printf("Waiting for connection...\n");
        int client_fd = accept(server_socket, NULL, NULL);
        printf("Connection made: client_fd=%d\n", client_fd);

        // Read and write with the client
        receive_message(client_fd);

        // Send a response to the client
        send_message("Type in the number you wanna repeat", client_fd);
        sleep(1);
        char repeat_count[10];
        int len = read(client_fd, repeat_count, sizeof(repeat_count) - 1);
        if (len == -1) {
            perror("read");
            exit(2);
        }
        repeat_count[len] = '\0';
        int repeat = atoi(repeat_count);  // Convert received string to integer

        // repeat
        for (int i = 0; i < repeat; i++) {
                send_message("Who's there?", client_fd);
                sleep(1);
                receive_message(client_fd);
                send_message("Doris who? ", client_fd);
                sleep(1);
                receive_message(client_fd);
                printf("haha. not funny. \n");
        }

        // Close the client connection
        close(client_fd);
    }
    close(server_socket);
    return 0;
}

int main(int argc, char **argv) {
    // Set up signal handler for SIGINT
    signal(SIGINT, handle_sigint);
    do_open();  // Call the server function to start listening
    return 0;
}

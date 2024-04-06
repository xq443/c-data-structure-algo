#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#define MAXLINE 999

void read_response(int client_fd, char* buffer) {
    int len = read(client_fd, buffer, sizeof(buffer) - 1);
    buffer[len] = '\0';
    printf("\033[1;93mSERVER RECEIVED:\033[0m %s \n", buffer);
}

void send_message(char *msg, int sock_fd, char *buffer) {
    printf("\033[1;94mSERVER SENDING: \033[0m %s \n", msg);
    write(sock_fd, msg, strlen(msg));
}

int main(int argc, char **argv) {
    int s;

    // Step 1: Get address stuff
    struct addrinfo hints, *result;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    s = getaddrinfo(NULL, "1234", &hints, &result);
    if (s != 0) {
      fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
      exit(1);
    }

    // Step 2: Open socket
    int yes = 1;
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    // lose the pesky "Address already in use" error message
    if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) == -1) {
      perror("setsockopt");
      exit(1);
    }
    // Step 3: Bind socket
    if (bind(sock_fd, result->ai_addr, result->ai_addrlen) != 0) {
      perror("bind()");
      exit(1);
    }

    // Step 4: Listen on the socket
    if (listen(sock_fd, 10) != 0) {
      perror("listen()");
      exit(1);
    }
    struct sockaddr_in *result_addr = (struct sockaddr_in *) result->ai_addr;
    printf("Listening on file descriptor %d, port %d\n",
    sock_fd, ntohs(result_addr->sin_port));

    // Step 5: Accept connection
    printf("Waiting for connection...\n");
    while (1) {
      int client_fd = accept(sock_fd, NULL, NULL);
      printf("Connection made: client_fd=%d\n", client_fd);

      while (1) {
      // Step 6: Read, then write if you want
      char buffer[MAXLINE];

      read_response(client_fd, buffer);
      if (buffer[0] == 'x' && strlen(buffer) == 2 && buffer[1] == '\n') {
        printf("Closing connection.\n");
        close(client_fd);
        goto end;  // end the connection loop
      }
      char question[MAXLINE];
      char repeat_count[MAXLINE];
      send_message("Type in the number you wanna repeat",
      client_fd, question);
      sleep(1);
      read_response(client_fd, repeat_count);
      int times = atoi(repeat_count);  // to integer

      // return the new string with string repeating number of time
      char ret[sizeof(buffer)] = {0};  // initialize with zeros
      size_t ret_len = 0;  // track the current length of ret
      for (int i = 0; i <= times; i++) {
        // Concatenate up to 'len' characters from 'buffer' into 'ret'
        strncat(ret, buffer, sizeof(buffer) - ret_len - 1);
        // Update the length of 'ret'
        ret_len = strlen(ret);
      }
      // send the ret to the client
      write(client_fd, ret, strlen(ret));
    }
    printf("Got terminating signal from client...Closing connection.\n");

    // Step 7: Close
    close(client_fd);
  }

  // Step 8: Close server socket
  end:
  freeaddrinfo(result);
  close(sock_fd);
  return 0;
}

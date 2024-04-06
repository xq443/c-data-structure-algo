# client-server programs work and define protocols
- Build and Run the Server and Client
- Changing Ports 
```
int yes=1;
// lose the pesky "Address already in use" error message
if (setsockopt(sock_fd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof yes) == -1) {
    perror("setsockopt");
    exit(1);
} 
```
- Have the Server keep listening for more clients ()
```
make run_kk_server
gcc kk_server.c -o kk_server
./kk_server
Listening on file descriptor 3, port 7533
Waiting for connection...
Connection made: client_fd=4
SERVER RECEIVED: Knock knock 
SERVER SENDING: Type in the number you wanna repeat===
SERVER SENDING: Who's there?===
SERVER RECEIVED: doris. 
SERVER SENDING: Doris who? ===
SERVER RECEIVED: door is closed. That's why I knocked! 
haha. not funny. 
SERVER SENDING: Who's there?===
SERVER RECEIVED: doris. 
SERVER SENDING: Doris who? ===
SERVER RECEIVED: door is closed. That's why I knocked! 
haha. not funny. 
Waiting for connection...
Connection made: client_fd=4
SERVER RECEIVED: Knock knock 
SERVER SENDING: Type in the number you wanna repeat===
SERVER SENDING: Who's there?===
SERVER RECEIVED: doris. 
SERVER SENDING: Doris who? ===
SERVER RECEIVED: door is closed. That's why I knocked! 
haha. not funny. 
SERVER SENDING: Who's there?===
SERVER RECEIVED: doris. 
SERVER SENDING: Doris who? ===
SERVER RECEIVED: door is closed. That's why I knocked! 
haha. not funny. 
SERVER SENDING: Who's there?===
SERVER RECEIVED: doris. 
SERVER SENDING: Doris who? ===
SERVER RECEIVED: door is closed. That's why I knocked! 
haha. not funny. 
Waiting for connection...
^CReceived SIGINT. Closing server...
```
```
[cathyqin@login-students lab9]$ make run_kk_client
./kk_client
Connection is good!
socket fd (client): 3
SENDING:  Knock knock===
RECEIVED:  Type in the number you wanna repeat
Enter the number of times to repeat: 3
SENDING:  3===
RECEIVED:  Who's there?
SENDING:  doris.===
RECEIVED:  Doris who? 
SENDING:  door is closed. That's why I knocked!===
RECEIVED:  Who's there?
SENDING:  doris.===
RECEIVED:  Doris who? 
SENDING:  door is closed. That's why I knocked!===
RECEIVED:  Who's there?
SENDING:  doris.===
RECEIVED:  Doris who? 
SENDING:  door is closed. That's why I knocked!===
```
- Complicate the Protocol
    - change our client and server so that instead of just echoing back the message, the server is going to echo back the message a specified number of times. Have the server sleep(1) after every send of the message. 

    - Here's what the communication should look like: 

    ```
    [after client connects to server]: 
    Client send message to server
    Server asks client how many times to repeat. 
    Client sends a number
    Server repeats the message back to the client the specified number of times. 
    [and repeat]
    ```
```
make run_echo_server
gcc echo_server.c -o echo_server
./echo_server
Listening on file descriptor 3, port 1234
Waiting for connection...
Connection made: client_fd=4
SERVER RECEIVED: we
 
SERVER SENDING:  Type in the number you wanna repeat 
SERVER RECEIVED: 1 
SERVER RECEIVED: 22
 
SERVER SENDING:  Type in the number you wanna repeat 
SERVER RECEIVED: 2 
SERVER RECEIVED: er
 
SERVER SENDING:  Type in the number you wanna repeat 
SERVER RECEIVED: 2 
SERVER RECEIVED: 3
 
SERVER SENDING:  Type in the number you wanna repeat 
SERVER RECEIVED: 3 
SERVER RECEIVED: x
 
Closing connection.
```
```
make run_echo_client
gcc echo_client.c -o echo_client
./echo_client
Enter your message: we
CLIENT SENDING: we
 
CLIENT RECEIVED: Type in the number you wanna repeat 
Enter your choice of repeating: 1
CLIENT SENDING: 1 
CLIENT RECEIVED: we
we
 
Enter your message: 22
CLIENT SENDING: 22
 
CLIENT RECEIVED: Type in the number you wanna repeat 
Enter your choice of repeating: 2
CLIENT SENDING: 2 
CLIENT RECEIVED: 22
22
22
 
Enter your message: er
CLIENT SENDING: er
 
CLIENT RECEIVED: Type in the number you wanna repeat 
Enter your choice of repeating: 2
CLIENT SENDING: 2 
CLIENT RECEIVED: er
er
er
 
Enter your message: 3
CLIENT SENDING: 3
 
CLIENT RECEIVED: Type in the number you wanna repeat 
Enter your choice of repeating: 3
CLIENT SENDING: 3 
CLIENT RECEIVED: 3
3
3
3
 
Enter your message: x
CLIENT SENDING: x
 
BREAKING CONNECTION AND TERMINATING
```
- check memory leak
```
==2140099== HEAP SUMMARY:
==2140099==     in use at exit: 0 bytes in 0 blocks
==2140099==   total heap usage: 2 allocs, 2 frees, 1,088 bytes allocated
==2140099== 
==2140099== All heap blocks were freed -- no leaks are possible
==2140099== 
==2140099== For lists of detected and suppressed errors, rerun with: -s
==2140099== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
```
==2140108== HEAP SUMMARY:
==2140108==     in use at exit: 7,186 bytes in 55 blocks
==2140108==   total heap usage: 71 allocs, 16 frees, 26,426 bytes allocated
==2140108== 
==2140108== LEAK SUMMARY:
==2140108==    definitely lost: 0 bytes in 0 blocks
==2140108==    indirectly lost: 0 bytes in 0 blocks
==2140108==      possibly lost: 0 bytes in 0 blocks
==2140108==    still reachable: 7,186 bytes in 55 blocks
==2140108==         suppressed: 0 bytes in 0 blocks
==2140108== Reachable blocks (those to which a pointer was found) are not shown.
==2140108== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==2140108== 
==2140108== For lists of detected and suppressed errors, rerun with: -s
==2140108== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
- check clint code style
```
bash-4.4$ clint.py *.c
Done processing echo_client.c
Done processing echo_server.c
Done processing kk_client.c
Done processing kk_server.c
Total errors found: 0
```
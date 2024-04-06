#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <time.h>  // Added for the game
#include <sys/types.h>  // Add this header for pid_t type
#include <sys/wait.h>
#define MAXARGS 5
#define MAXLINE 8192
#define BUFFERSIZE 80  // BUFFER CHARACTER SIZE LIMIT
#define COMMANDNUM 4  // NUM OF COMMANDS

// list command names
char* commands[COMMANDNUM] = {"cd", "help", "exit", "game"};

// parse the token
void parse(char* line, char** argv) {
    char* token;
    const char* delimiters = " \n";  // define delimiters : space and newline
    int idx = 0;
    char* saveptr;  // Declare a pointer variable to be used by strtok_r

    // initialize the internal state for tokenization.
    token = strtok_r(line, delimiters, &saveptr);
    while (token != NULL) {
        argv[idx++] = token;  // Store token in argv array
        // continue tokenizing the input line.
        token = strtok_r(NULL, delimiters, &saveptr);
    }
    argv[idx] = NULL;  // Terminate argv with NULL
}

void* cd(void* input) {
    char* s = (char*)input;  // cast the input to a character pointer
    if (s == NULL || strcmp(s, "") == 0) {
    //  if no path input default to the home dir
        s = getenv("HOME");  // retrieve the value of the HOME env variable
        if (s == NULL) {
            // error if the HOME environment variable is not set
            fprintf(stderr, "cd: Failed to get the home directory.\n");
            return NULL;
        }
    }

    // Implement cd
    // change the current working dir to the specified path
    if (chdir(s) < 0) {  // if the dir change fails
        perror("cd");  // pint an error message if chdir fails
        return NULL;
    }
    // print the current dir after routing
    // retrieves the current working dir and stores it in the cwd
    char* cwd = getcwd(NULL, 0);
    printf("Current directory: %s\n", cwd);
    free(cwd);  // Free the allocated memory for cwd
    return NULL;
}

// take an argument and print out funny sentence
void* helper(void* input) {
    printf("All commands are: \n");
    printf("cd: change directory\n");
    printf("help: display help instructions\n");
    printf("exit: exit the foreground\n");
    printf("game: Play a random game\n");
    return NULL;
}

void* quit(void* input) {
    exit(0);
    return NULL;
}

void* game(void* input) {
    const char* games[] = {
        "Why did the programmer quit his job? Because he didn't get arrays.",
        "Why did the developer go broke? Because he used up all his cache.",
        "Why did the function break up with the method? It returned null.",
    };
    int game_num = sizeof(games) / sizeof(games[0]);

    unsigned int seed = time(NULL);  // Get a seed value based on current time
    unsigned int random_seed;
    rand_r(&seed);  // the random number generator
    random_seed = rand_r(&seed);  // generate a new seed value

    // a random index between 0 and the total number of games - 1
    int random_index = random_seed % game_num;

    // Print the random joke
    printf("%s\n", games[random_index]);
    return NULL;
}

// list the command function pointers
void* (*command_functions[COMMANDNUM])(void* arg) = {cd, helper, quit, game};


/***
 **  Wrapper of fork(). Checks for fork errors, quits on error. 
 **/
pid_t Fork(void) {
    pid_t pid;
    if ((pid = fork()) < 0) {
        fprintf(stderr, "%s: %s\n", "fork error", strerror(errno));
        exit(0);
    }
    return pid;
}

/***
 **  Wrapper of fgets. Checks and quits on Unix error. 
 **/
char* Fgets(char *ptr, int n, FILE *stream) {
    char *rptr;
    if (((rptr = fgets(ptr, n, stream)) == NULL) && ferror(stream)) {
        fprintf(stderr, "%s\n", "fgets error");
        exit(0);
    }
    return rptr;
}

// implement the command
// input : char* arg[] = {"cd", "home/cathyqin"};
int builtin_command(char** arg) {
    int i;
    for (i = 0; i < COMMANDNUM; i++) {
        if (strcmp(commands[i], arg[0]) == 0) {
            // call the correspoinding command function.
            (command_functions[i])(arg[1]);
            return 1;  // successful
        }
    }
    return 0;  // failure
}

void eval(char *cmdline) {
    char *argv[MAXARGS]; /* Argument list execve() */
    char buf[MAXLINE]; /* Holds modified command line */
    pid_t pid; /* Process id */

    // copy the cmdline into a buffer.
    snprintf(buf, sizeof(buf), "%s", cmdline);

    // Split buf into args
    parse(buf, argv);
    if (argv[0] == NULL)
        return; /* Ignore empty lines */
    if (!builtin_command(argv)) {
        // Create a child process
        pid_t pid = Fork();
        if (pid == 0) {  // Child process created successfully
            // execute the program of which path is specified in argv[0]
            // passing it the arguments provided in the argv array.
            int res = execvp(argv[0], argv);
            if (res < 0) {
                // print error message
                printf("%s: Command not found--Did you mean something else?\n"
                , argv[0]);
                exit(1);  // failure
            }
        } else {
            // parent process waits for the child to finish executing
            waitpid(pid, NULL, 0);
        }
    }
    return;
}

int main() {
    char cmdline[MAXLINE];  // command line buffer
    while (1) {
        // prompt
        printf("k-sea-shell> ");
        // read input from user
        Fgets(cmdline, MAXLINE, stdin);
        // no more characters to be read from the input stream
        if (feof(stdin))
            exit(0);  // successfully exit
        // evaluate the input and execute the command function
        eval(cmdline);
    }
}

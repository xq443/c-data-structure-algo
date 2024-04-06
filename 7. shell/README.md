### a7 Summary
1. About:

- Implement the K-SEA Shell program which is designed to read user commands, execute child processes in the foreground, 
- and provide built-in functionalities like 'exit', 'cd', 'help', and a custom 'game' command for interactive tasks such as funny sentence generation.

2. Project file directory:

- `shell.c`: This file contains the core implementation of the K-SEA Shell, featuring functionalities such as reading user commands, executing child processes, implementing built-in commands like 'exit', 'cd', 'help', and the custom 'game' command.
- `run_ls.c`: It is a supplementary file that provides an example of executing the 'ls' command within the shell environment.
- `README.md`: This Markdown file contains information and instructions about the project.

3. Command Description:

- cd (Change Directory):
  - Synopsis: The "cd" command allows users to change the current working directory.
  - Description: When invoked with a directory path as an argument, "cd" changes the shell's current directory to the specified location. If no argument is provided, it defaults to the user's home directory.
  - Implementation: The "cd" function handles both cases: changing to the specified directory or defaulting to the home directory if no argument is provided. It utilizes the chdir() system call to change the directory and prints the updated directory path.

- help (Help Instructions):

  - Synopsis: The "help" command displays instructions and information about available commands.
  - Description: Upon invocation, "help" presents users with a list of available commands along with brief descriptions of each command's functionality.
  - Implementation: The "helper" function prints out a list of commands supported by the shell along with their descriptions. It utilizes printf statements to display this information.

- exit (Exit the Shell):
  - Synopsis: The "exit" command terminates the shell session.
  - Description: Upon execution, "exit" gracefully terminates the shell, closing the session and returning control to the parent environment.
  - Implementation: The "quit" function invokes the exit() system call with a status code of 0 to indicate successful termination. This ensures that the shell exits cleanly without any errors.

- game:
  - Synopsis: It introduces an element of entertainment by allowing users to play a random joke or funny sentence from a predefined list.
  - Description: The "game" command offered a brief moment of amusement. When invoked, it randomly selects a joke or funny sentence from a predefined array and displays it on the console.
  - Implementation: To integrate the "game" command, I followed a similar pattern to the existing built-in commands like "cd", "help", and "exit". I declared a function to handle the "game" command, which selects a random joke or funny sentence from an array of strings. The random selection process is facilitated by using a seed generated from the current time, and is printed to the console.

4. Building and Running the Code:

* compile the code
```bash
gcc shell.c
./a.out
```
```
k-sea-shell> cd
Current directory: /home/cathyqin
k-sea-shell> ls
bin  course_resources  data_strctures  id_rsa  id_rsa.pub  lib  src
k-sea-shell> cd data_strctures
Current directory: /home/cathyqin/data_strctures
k-sea-shell> ls
a1  a2  a3  a4  a6  a7  lab1  lab2  lab3  lab4  lab5  lab6  lab7  quiz  README.md
k-sea-shell> exit
bash-4.4$ gcc shell.c
bash-4.4$ ./a.out
k-sea-shell> game
Why did the function break up with the method? It returned null.
k-sea-shell> help
All commands are: 
cd: change directory
help: display help instructions
exit: exit the foreground
game: Play a random game
k-sea-shell> exit
```

* check memory leak error
```bash
valgrind --leak-check=full ./a.out
```
```
==255813== HEAP SUMMARY:
==255813==     in use at exit: 0 bytes in 0 blocks
==255813==   total heap usage: 6 allocs, 6 frees, 10,285 bytes allocated
==255813== 
==255813== All heap blocks were freed -- no leaks are possible
==255813== 
==255813== For lists of detected and suppressed errors, rerun with: -s
==255813== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

* using clint.py to check code style
```bash
clint.py *.c
```
```
[cathyqin@login-students a7]$ clint.py *.c
Done processing run_ls.c
Done processing shell.c
Total errors found: 0
```

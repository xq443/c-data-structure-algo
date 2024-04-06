/* Program to demonstrate time taken by function fun() */
#include <stdio.h>
#include <time.h>
#include <unistd.h>   // for sleep()
#include <sys/time.h>  // for gettimeofday()

// A function that terminates when enter key is pressed
void fun() {
    printf("fun() starts \n");
    printf("Press enter to stop fun \n");
    while (1) {
        if (getchar())
            break;
    }
    printf("fun() ends \n");
}
// The main program calls fun() and measures time taken by fun()
int main() {
    struct timeval begin, end;
    gettimeofday(&begin, NULL);
    // do some stuff here
    fun();
    gettimeofday(&end, NULL);
    int seconds = (end.tv_sec - begin.tv_sec);
    int micros = ((seconds * 1000000) + end.tv_usec) - (begin.tv_usec);
    printf("Time elpased is %ld seconds and %ld micros\n", seconds, micros);
    return 0;
}

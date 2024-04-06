#include <stdio.h>
#include <stdlib.h>  

int main()
{
    float *p, sum = 0;
    int i, n;

    printf("Enter the number of students: ");
    scanf("%d", &n); //provide the address of the variable where you want to store the input.

    // allocate memory to store n variables of type float
    p = (float*)malloc(n*sizeof(float)); //p points to the start (or the first element) of the dynamically allocated float array.

    // if dynamic allocation failed exit the program
    if(p==NULL)
    {
        printf("Memory allocation failed");
        exit(1); // exit the program
    }

    // ask the student to enter marks
    for(i = 0; i < n; i++)
    {
        printf("Enter marks for %d student: ", i+1);
        scanf("%f", p+i); //p + i  calculates the memory location for the i-th element in the block of memory pointed to by p. 
        //Move i positions ahead in memory from where p is pointing.
    }

    // calculate sum
    for(i = 0; i < n; i++)
    {
        sum += *(p+i);//dereference
    }

    printf("\nAverage marks = %.2f\n", sum/n);

    free(p); //free our memory of p

    // signal to operating system program ran fine
    return 0;
}


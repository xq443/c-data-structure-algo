#include "stdio.h"
#include "stdbool.h"
#include <ctype.h>

/**
 * Write a function that replaces all numbers greater
 * than ceiling in arr with ceiling.
 *
 * Precondition(s):
 * - len > 0 (i.e. arrays MUST have at least one element)
 *
 * Example(s):
 * - crop_hi([1, 2, 3, 4], 4, 2) :: [1, 2, 2, 2]
 * - crop_hi([-3, 17,  7, -12, 10], 5, 8) :: [-3, 8, 7, -12, 8]
 *
 * @param arr     array of integers
 * @param len     length of arr
 * @param ceiling upper limit for ints in array
 */

void printArr(int* arr, int length){
    int i;
    for(i = 0; i < length; i++){
        printf("%d", arr[i]);
    }
}
void crop_hi(int* arr, int len, int ceiling){
    int i;
    for(i = 0; i < len; i++){
        if(arr[i] > ceiling) {
            arr[i] = ceiling;
        }
    }
}


/**
 * Swaps the the last int in arr with the middle element in arr.
 *
 * Precondition(s):
 * - len > 0 (i.e. arrays MUST have at least one element)
 *
 * Example(s):
 * - swap_mid_back([1, 2, 3], 3) :: [1, 3, 2]
 * - swap_mid_back([-4, 3, 0, 1], 4) :: [-4, 1, 0, 3]
 *
 * @param arr array of integers
 * @param len length of arr
 */

void swap(int* arr, int i, int j){
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}
void swap_mid_back(int* arr, int len){
    int mid;
    if(len % 2 == 0) mid = len/2 - 1;
    else mid = len/2;

    swap(arr, mid, len - 1);
}

/**
 * Replaces all digits in a string with a '*'. 
 *
 *
 * Example(s):
 * - redact("The part failed 58% of the time") ::
 *          "The part failed **% of the time"
 * - redact("There were 13 As in the class") :: "There were ** As in the class"
 *
 * @param  str      host string for old_char
 */
void redact(char* str){
    while(*str != '\0'){ //use '\0' to represent the null character (end of string) rather than NULL(used to represent pointer)
        if(isdigit(*str)){
            *str = '*';
        }
        str++;
    }
}


/**
 * Compares two integer arrays and tests for equality
 */
bool equalArrays(int* arr1, int size1, int* arr2, int size2) {
    if(size1 != size2) return 0;
    bool res = true;

    int i;
    for(i=0; i <size1; i++) {
        res = res && arr1[i] == arr2[i];
    }
    return res;
}

void testEqualArrays() {
    int arr1[] = {1,2,3,4};
    int arr2[] = {1,2,3,4};
    int arr3[] = {4,3,2,1};
    printf("test1: %d\n", equalArrays(arr1, 4, arr2, 4));
    printf("test2: %d\n", equalArrays(arr1, 3, arr2, 4));
    printf("test3: %d\n", equalArrays(arr1, 4, arr3, 4));
}


int main() {
    testEqualArrays();

    int arr1[]= {1,2,3,4};
    crop_hi(arr1, 4, 2);
    printArr(arr1, 4);
    printf("\n");

    int arr2[] = {1,2,3,4,5,6};
    swap_mid_back(arr2, 6);
    printArr(arr2, 6);

    printf("\n");

    char example_str[] = "The part failed 58% of the time";
    redact(example_str);
    printf("%s\n", example_str); 

}


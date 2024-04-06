#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "a2.h"


// YOUR CODE GOES HERE

// Print the string <first> <middle> <last>
//  e.g. if first = "Ben", middle = "Ivan",
//  and last = "Bitdiddle, then print:
//  "Ben Ivan Bitdiddle".
//
//  If the middle name is NULL, then print:
//  "Ben Bitdiddle"
//
//  name: a pointer to a Name
void Big(Name *name) {
    if(name->middle == NULL){
        printf("%s %s\n", name->first, name->last);
    }else{
        printf("%s %s %s\n", name->first, name-> middle, name->last);
    }
}

// Print the string <last>, <first>
//  e.g. if first = "Ben", middle = "Ivan",
//  and last = "Bitdiddle, then print:
//  "Bitdiddle, Ben".
//
// name: a pointer to a Name
void Last(Name *name) {
    printf("%s, %s\n", name->last, name->first);
}

// Print the string <first> <last>
//  e.g. if first = "Ben", middle = "Ivan",
//  and last = "Bitdiddle, then print:
//  "Ben Bitdiddle".
//
// name: a pointer to a Name
void Reg(Name *name) {
    printf("%s %s\n", name->first, name->last);
}

// Print the string <first> <middle-initial>. <last>
//  e.g. if first = "Ben", middle = "Ivan",
//  and last = "Bitdiddle, then print:
//  "Ben I. Bitdiddle".
//
// If middle name is NULL, print:
// "Ben Bitdiddle"
//
// name: a pointer to a Name
void Mid(Name *name) {
    if(name->middle == NULL){
        printf("%s %s\n", name->first, name->last);
    }else{
        printf("%s %c. %s\n", name->first, name->middle[0], name->last);
    }
}

// Print the first name only.
//  e.g. if first = "Ben", middle = "Ivan",
//  and last = "Bitdiddle, then print:
//  "Ben".
//
// name: a pointer to a Name
void Small(Name *name){
    printf("%s\n", name->first);
}

// Given a format char, print the given
// name in the format specified by char.
// The mapping is shown below:
// B -> 'big' format
// L -> 'last' format
// R -> 'reg' format
// M -> 'mid' format
// S -> 'small' format
//
// name: a pointer to a Name
// format: a char indicating the format to use (case doesn't matter)
void FormatName(Name *name, char format) {
    if (format == 'B' || format == 'b') {
        Big(name);
    } else if (format == 'L' || format == 'l') {
        Last(name);
    } else if (format == 'R' || format == 'r') {
        Reg(name);
    } else if (format == 'M' || format == 'm') {
        Mid(name);
    } else if (format == 'S' || format == 's') {
        Small(name);
    } else {
        printf("Invalid format specified.\n");
    }
}

// Given a name, a format and a destination array,
// put the properly formatted name in the destination
// array, not printing anything on the screen.
//
// The mapping is shown below:
// B -> 'big' format
// L -> 'last' format
// R -> 'reg' format
// M -> 'mid' format
// S -> 'small' format
//
// name: a pointer to a Name
// format: a char indicating the format to use (case doesn't matter)
// dest: a pointer to an array that is guaranteed to be big enough
// to hold the formatted name
void FillName(Name *name, char format, char *dest) {
    if (format == 'B' || format == 'b') {
        sprintf(dest, "%s %s %s", name->first, name->middle, name->last);
    } else if (format == 'L' || format == 'l') {
        sprintf(dest, "%s, %s", name->last, name->first);
    } else if (format == 'R' || format == 'r') {
        sprintf(dest, "%s %s", name->first, name->last);
    } else if (format == 'M' || format == 'm') {
        if (name->middle == NULL) {
            sprintf(dest, "%s %s", name->first, name->last);
        } else {
            sprintf(dest, "%s %c. %s", name->first, name->middle[0], name->last);
        }
    } else if (format == 'S' || format == 's') {
        sprintf(dest, "%s", name->first);
    } else {
        sprintf(dest, "Invalid format specified.");
    }
}

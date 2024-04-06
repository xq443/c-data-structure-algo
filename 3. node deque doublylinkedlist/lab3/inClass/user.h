#include <stdio.h>
#ifndef USER_H 

#define USER_H 
typedef struct User {
    char* firstName;
    char* lastName;
    int age;
}User;
void StandardGreeting(User* user);
void FormalGreeting(User* user);
void InformalGoodbye(User* user);
void FormalGoodbye(User* user);

#endif

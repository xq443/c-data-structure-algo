#include <stdio.h>
#include "user.h"

//only goodbye
void InformalGoodbye(User* user) {
    printf("Goodbye, %s\n", user->firstName);
}

void FormalGoodbye(User* user) {
    printf("Formal goodbye, %s\n", user->lastName);
}


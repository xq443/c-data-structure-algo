#include <stdio.h>
#include "user.h"
//only greetings
void StandardGreeting(User* user) {
    printf("First name is %s\n", user->firstName);
}

void FormalGreeting(User* user) {
    printf("Last name is  %s\n", user->lastName);
}

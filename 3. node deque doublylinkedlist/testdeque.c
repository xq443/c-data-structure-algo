#include <stdio.h>
#include <stdbool.h>
#include "deque.h"

int main(){
    Deque* d1 = createDeque();
    pushLeft(d1, 1);
    pushRight(d1, 2);
    pushLeft(d1, 3);
    pushRight(d1, 4);

    printList(d1->list);
    printf("\n");

    printf("peek left: %d\n", peekLeft(d1));
    printf("peek right: %d\n", peekRight(d1));
    printf("popleft: %d\n", popLeft(d1));
    printf("popright: %d\n", popRight(d1));

    freeDequeMemory(d1);
    return 0;
}



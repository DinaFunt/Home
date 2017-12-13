#include "LIST.h"

typedef void (*Action)(LinkedList *);

int main() {
    int i, n, b, f = 0;
    LinkedList *list = NULL;

    while(1)
    {
        printf("1) Create list\n");
        printf("2) Push node to the begining of list\n");
        printf("3) Push node to the ending of list\n");
        printf("4) Push node after some element\n");
        printf("5) Delete node by value\n");
        printf("6) Print list\n");
        printf("7) Clean list\n");
        printf("8) Check of the list for a round\n");
        printf("9) Make a round\n");
        printf("10) Change the order of nodes\n");
        printf("11) Exit\n");

        printf("Choose the number of function\n");

        Action fun[] = {push, pushBack, pushAfter, deleteNode, printLinkedList, CleanList, circleCheck, makeRound, orderChange, ExitDelete};

        scanf("%d", &n);

        if ((n < 0) && (n > 10))
        {
            printf("input is incorrect, repeat again\n");
            continue;
        }

        if ((n == 11) && (f == 0))
        {
            exit(0);
        }

        if (n == 1)
        {
            if (f == 0)
            {
                printf("input a number of elements in your list\n");
                scanf("%d", &b);
                list = CreateList(b);
                f = 1;
                continue;
            }
            else
            {
                printf("list has already created");
                continue;
            }
        }
        if (f == 1)
        {
             fun[n - 2](list);
        }
        else
        {
            printf("You might create list for begining\n");
        }
    }
}

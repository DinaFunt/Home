#include "Header.h"
#define Created 1
#define NotCreated 0

typedef struct Action {
        char * descr;
        void (*doAction)(LinkedList *);
    } Action;

int main() {
    int i, n, b, f = NotCreated;
    LinkedList *list = NULL;

    while(1)
    {
        const Action fn[] = {
            {"Push node to the begining of list", &push},
            {"Push node to the ending of list", &pushBack},
            {"Push node after some element", &pushAfter},
            {"Delete node by value", &deleteNode},
            {"Print list", &printLinkedList},
            {"Clean list", &CleanList},
            {"Check of the list for a round", &circleCheck},
            {"Make a round", &makeRound},
            {"Change the order of nodes", &orderChange},
            {"Exit", &ExitDelete},
        };

        const size_t count = sizeof(fn) / sizeof(Action);

        printf("1) Create list\n");
        for (i = 0; i < count; i++)
        {
            printf("%d) %s\n", i + 2, fn[i].descr);
        }

        printf("Choose the number of function\n");
        printf("%d\n", count);

        scanf("%d", &n);

        if ((n <= 0) || (n > count + 1))
        {
            printf("input is incorrect, repeat again\n");
            continue;
        }

        if ((n == 11) && (f == NotCreated))
        {
            exit(0);
        }

        if (n == 1)
        {
            if (f == NotCreated)
            {
                printf("input a number of elements in your list\n");
                scanf("%d", &b);
                list = CreateList(b);
                f = Created;
                continue;
            }
            else
            {
                printf("list has already created");
                continue;
            }
        }
        if (f == Created)
        {
             (*fn[n - 2].doAction)(list);
        }
        else
        {
            printf("You might create list for begining\n");
        }
    }
}

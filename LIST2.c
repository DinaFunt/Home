#include "LIST.h"

Node *CreateNode(int val)
{
    Node *newNode = (Node *)calloc(1, sizeof(Node));

    if (newNode == NULL)
    {
        printf("Can't callocate memory");
        exit(0);
    }

    newNode->value = val;
    newNode->next = NULL;

    return newNode;
}

void push(LinkedList *list) {
    Node *node;
    int val;
    printf("Input a value\n");
    scanf("%d", &val);
    node = CreateNode(val);

    node->next = list->head;
    list->head = node;
    list->length += 1;
}

LinkedList *CreateList(int n) {

    LinkedList *list = (LinkedList *)calloc(1,  sizeof(LinkedList));
    if (list == NULL)
    {
        printf("can't callocate memory");
        exit(-1);
    }
    Node *node = NULL;
    int val, i = 0;
    list->length = n;
    list->head = NULL;

    if (n > 0)
    {
        printf("input value\n");
        scanf("%d", &val);
        node = CreateNode(val);
        list->head = node;
        i++;
        while (i != n)
        {
            push(list);
            i++;
        }
    }
    return list;
}

Node *getLast(LinkedList *list) {
    if (list->head == NULL) {
        return NULL;
    }
    while ((list->head)->next) {
        list->head = (list->head)->next;
    }
    return (list->head);
}

void pushBack(LinkedList *list) {
    Node *last = getLast(list);
    Node *tmp;
    int val;
    printf("input a value\n");
    scanf("%d", &val);
    tmp = CreateNode(val);
    last->next = tmp;
    list->length += 1;
}

void pushAfter(LinkedList *list) {
    Node *tmp = list->head;
    int val;
    printf("input a value of the node\n");
    scanf("%d", &val);
    Node *aft = CreateNode(val);
    int data;
    printf("input a value after which you want to push your element\n");
    scanf("%d", &data);
    while (tmp)
    {
        if (tmp->value == data)
        {
            aft->next = tmp->next;
            tmp->next = aft;
            list->length += 1;
            return;
        }
        tmp = tmp->next;

    };
    printf("There is no node with this value\n");
}

void printLinkedList(LinkedList *list) {
    while (list->head) {
        printf("%d ", (list->head)->value);
        (list->head) = (list->head)->next;
    }
    printf("\n");
}

void CleanList(LinkedList *list) {
    Node *tmp = list->head;
    Node *tmp2;

    while (tmp)
    {
        tmp2 = tmp->next;
        free(tmp);
        tmp = tmp2;
    }

    list->head = NULL;
    list->length = 0;
}

void deleteNode(LinkedList *list) {
    Node *tmp = (list->head)->next;
    Node *tmp2 = list->head;
    Node *aft;
    int val;
    printf("Input value which you want to delete\n");
    scanf("%d", &val);

    if (tmp2->value == val)
    {
        list->head = tmp;
        free(tmp2);
        list->length -= 1;
    }

    while (tmp->next)
    {
        if (tmp->value == val)
        {
            aft = tmp;
            tmp2->next = tmp->next;
            free(aft);
            list->length -= 1;
        }
        tmp2 = tmp;
        tmp = tmp->next;
    }

    if (tmp->value == val)
    {
        aft = tmp->next;
        tmp->next = (tmp->next)->next;
        free(aft);
        list->length -= 1;
    }
}

void orderChange(LinkedList *list) {
    Node *ptr1;
    Node *ptr2;
    Node *ptr3;

    ptr1 = list->head;
    ptr2 = ptr1->next;
    ptr3 = (ptr2->next == NULL) ? NULL : ptr2->next;
    ptr1->next = NULL;
    ptr2->next = ptr1;

    while (ptr3)
    {
        ptr1 = ptr2;
        ptr2 = ptr3;
        ptr3 = (ptr2->next == NULL) ? NULL : ptr2->next;
        ptr2->next = ptr1;
    }

    list->head = ptr2;
}

void makeRound(LinkedList *list) {
    Node *tmp;
    Node *tmp2;
    int n;
    printf("input a number of element on which will point the latest element\n");
    scanf("%d", &n);
    tmp = getLast(list);
    tmp2 = list->head;
    while (n)
    {
        tmp2 = tmp2->next;
        n--;
    }
    tmp->next = tmp2;
}

void circleCheck(LinkedList *list) {
    Node *ptr1;
    Node *ptr2;

    if ((list->head)->next != NULL)
    {
        ptr1 = list->head;
        if ((ptr1)->next != NULL)
        {
            ptr2 = ptr1->next;
        }
        else
        {
            printf("no round\n");
            return;
        }
    }
    else
    {
        printf("no round\n");
        return;
    }

    while ((ptr1 != ptr2) && (ptr2 != NULL))
    {
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
        if (ptr2 != NULL)
        {
            ptr2 = ptr2->next;
        }
        else
        {
            printf("no round\n");
            return;
        }
    }

    if (ptr2 == NULL)
    {
        printf("no round\n");
        return;
    }
    else
    {
        printf("List is rounded\n");
        return;
    }
}

void ExitDelete(LinkedList *list) {
    CleanList(list);
    free(list);
    exit(0);
}

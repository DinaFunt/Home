#include <stdio.h>
#include <string.h>
#define MaxSize 20

void number(int n, char* a, unsigned long long *num) {
    unsigned long long t = 1;
    while (n >= 0)
    {
        *num = *num + ((unsigned long long)(a[n] - '0') * t);
        t = t * 2;
        n--;
    }
    return;
}

int main() {
    char a[MaxSize], b[MaxSize];
    int i = 0, n1, n2;
    unsigned long long fir = 0, sec = 0;
    for (i = 0; i < MaxSize; i++)
    {
        a[i] = '0';
        b[i] = '0';
    }
    printf("Two sequence of 1 and 0, lenght <= 20 \n");
    printf("(The elder digits are in the elements with the least indexes)\n");
    scanf("%s %s", a, b);
    n1 = strlen(a) - 1;
    n2 = strlen(b) - 1;
    //printf("%d %d\n", n1 + 1, n2 + 1);
    number(n1, a, &fir);
    number(n2, b, &sec);
    //printf("%d ", fir);
    //printf("%d\n", sec);
    if (fir > sec)
    {
        printf("first > second\n");
        return 0;
    }
    else if (fir < sec)
    {
        printf("first < second\n");
        return 0;
    }
    printf("first = second\n");
    return 0;
}


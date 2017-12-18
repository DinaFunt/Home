#include <stdio.h>
#include <string.h>

int main() {
    char a[50], b[50];
    int i = 0, n1, n2, fir = 0, sec = 0, t = 1;
    for (i = 0; i < 50; i++)
    {
        a[i] = '0';
        b[i] = '0';
    }
    printf("Two sequence of 1 and 0\n");
    printf("(The elder digits are in the elements with the least indexes)\n");
    scanf("%s %s", a, b);
    n1 = strlen(a) - 1;
    n2 = strlen(b) - 1;
    printf("%d %d\n", n1 + 1, n2 + 1);
    i = 0;
    while (n1 >= 0)
    {
        fir = fir + ((a[n1] - '0') * t);
        t = t * 2;
        n1--;
    }
    t = 1;
    while (n2 >= 0)
    {
        sec = sec + ((b[n2] - '0') * t);
        t = t * 2;
        n2--;
    }
    printf("%d %d\n", fir, sec);
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


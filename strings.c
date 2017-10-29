#include <stdio.h>

int strlen(char* str)
{
    int len = 0;
    for (; *str++; len++);
    return len;
}

char* strcpy(char* dst, char* src)
{
    char* dst1 = dst;
    while (*dst++ = *src++);
    return dst1;
}

char* strcat(char* dst, char* src)
{
    char* dst1 = dst;
    while (*dst++);
    dst--;
    while (*dst++ = *src++);
    return dst1;
}

int strcmp(char* s1, char* s2)
{
    for (; *s1 & *s2; s1++, s2++) {
        if (*s1 > *s2)
            return 1;
        if (*s1 < *s2)
            return (-1);
    }
    if (!(*s1) & *s2)
        return (-1);
    if (!(*s2) & *s1)
        return 1;
    return 0;
}

int main() {
    char str[10], src[34], dst[100], s2[34], s1[34];

    printf("1) Input line for strlen\n");
    scanf_s("%s", str, 9);
    printf("%d\n", strlen(str));
    
    printf("2) Input line for strcpy\n");
    scanf_s("%s", src, 33);
    printf("%s\n", strcpy(dst, src));

    printf("3) Input lines for strcat\n");
    scanf_s("%s", dst, 33);
    scanf_s("%s", src, 33);
    printf("%s\n", strcat(dst, src));

    printf("4) Input lines for strcmp\n");
    scanf_s("%s", s1, 33);
    scanf_s("%s", s2, 33);
    if (strcmp(s1, s2) == 1)
        printf(">0");
    if (strcmp(s1, s2) == -1)
        printf("<0");
    if (strcmp(s1, s2) == 0)
        printf("0");

    return 0;
}
#include <stdio.h>

#define Mantiss 23 

void First(float res, int *s, int *ex, int *man) {
    union union_type 
    {
        int x;
        float y;
    } myUni;
    myUni.y = res;
    *s = (myUni.x >> 31) & (1);
    *man = myUni.x & 0x7FFFFF;
    *ex = ((myUni.x >> 23) & 0xFF) - 127;
}

void Second(float res, int *s, int *ex, int *man) {
    union union_type 
    {
        struct struct_type 
        {
            unsigned m : 23;
            unsigned e : 8;
            unsigned z : 1;
        } myStrct;
        float y;
        int u;
    } myUni;
    myUni.y = res;
    *s = myUni.myStrct.z;
    *man = myUni.myStrct.m & 0x7FFFFF;
    *ex = (myUni.myStrct.e) - 127;
}

void Third(float res, int *s, int *ex, int *man) {
    int b;
    b = *(int *)(&res);
    printf("third res=%x\n", b);
    *s = (b >> 31) & (1);
    *man = (b & (0x7FFFFF));
    *ex = ((b >> 23) & 0xFF) - 127;
}

char BinTransMan(int *man) {
    char a[Mantiss];
    int m = *man;
    int i;
    for (i = Mantiss - 1; i >= 0; i--) {
    a[i] = m % 2 + '0';
    m = m / 2;
    };
    return (a[Mantiss]);
}

void Print(int *s, int *ex, int *man, float res) {
    char FirstLine[32], SecondLine[32], *fp=FirstLine, *sp=SecondLine;
    int i, j, msk=1, msk_man=1<<22;

    for (i = 0; i < 32; FirstLine[i] = 0, SecondLine[i++] = 0);

    if (res == 0)
    {
        printf("0.0\n");
    }
    else if (*(int *)&res == 0xFFC00000)
        {
            printf("NaN\n");
        }
    else if ((*s == 1) && (*ex == 0x80) && (*man == 0))
        {
            printf("-inf\n");
        }
    else if ((*s == 0) && (*ex == 0x80) && (*man == 0))
        {
            printf("+inf\n");
        }
    else
    {
        if (*s == 1) 
        {
            *fp++ = ' '; *fp++ = ' '; *fp++ = ' '; *fp++ = ' '; *fp++ = ' ';
            *sp++ = '('; *sp++ = '-'; *sp++ = '1'; *sp++ = ')'; *sp++ = '*';
        }
        *fp++ = ' '; sprintf_s(fp, 4, "%d", *ex);
        *sp++ = '2'; *sp++ = ' '; *sp++ = '*'; *sp++ = ' '; *sp++ = '1'; *sp++ = '.';
        if ( *man != 0)
        {
            i = 23;
            while (!(*man & msk)) 
            {
                msk <<= 1; i--;
            }
            for (j = 0; j < i; j++) 
            {
                *sp++ = !!(*man & msk_man) + (char)'0';
                msk_man >>= 1;
            }
            }
        printf("%s\n", FirstLine);
        printf("%s\n", SecondLine);
    };
}

struct myStruct {
    char *description;
    void(*doAction)(float, int*, int*, int*);
};

const struct myStruct mystruct[] = {
    { " union with int and bit operations", &First },
    { " union with struct with bit fields", &Second },
    { " taking an address and dereferencing a pointer\n    to a different type and bit operations", &Third },
};

int ToChoose() {
    int i;
    for (i = 0; i < 3; i++) 
    {
        printf("%d) %s\n", i + 1, mystruct[i].description);
    }
    printf("\nInput Your Choice (1..3): ");
    scanf_s("%d", &i);
    return i;
}

int main() {
    int w, s, ex, man;
    float  fir, sec, res;

    printf("Input two floats: ");
    scanf_s("%f %f", &fir, &sec);
    res = fir / sec;

    w = ToChoose() - 1;
    if (w < 0 || w > 2)
    {
        printf("Wrong Choice\n");
        return 0;
    }

    (*mystruct[w].doAction)(res, &s, &ex, &man);

    Print(&s, &ex, &man, res);
}
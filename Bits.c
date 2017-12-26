#include <stdio.h>

int bitAnd(int x, int y)
{
    return ~(~x | ~y);
}

int bitXor(int x, int y)
{
    return ~((~(~x & y)) & (~(x & ~y)));
}

int thirdBit(void)
{
    return 044 << 24 | 0111 << 17 | 0111 << 8 | 044;
}

int conditional(int x, int y, int z)
{
    return ((-!!x) & y) | ((-!x & z));
}

int logicalShift(int x, int n)
{
    int mask;
    mask = ~((1 << 31) >> (n + (-1)));
    return (x >> n) & mask;
}

int sign(int x)
{
    return ((x & (1 << 31)) >> 31) | (!x ^ 1);
}

int bang(int x)
{
    int mask = 1 << 31;
    return (((x & mask) | ((~x + 1) & mask)) >> 31) + 1;
}

int isPower2(int x)
{
    return !(x & (1 << 31)) & !!x & !(x ^ (x & (~x + 1)));
}

int fitBits(int x, int n)
{
    int mask;
    mask = (1 << 31) >> (31 + (~n + 2));
    return !!((1 << 31) & x) & !(~x & mask);
}

int addOK(int x, int y)
{
    int mask, mask1 = 0xFF;
    int u, v;
    mask = (mask1 << 8) | mask1;
    u = ((x & mask) + (y & mask)) >> 16;
    v = ((x >> 16) & mask) + ((y >> 16) & mask);
    return !((u + v) >> 16);
}

int getByte(int x, int n)
{
    int mask = 0xFF;
    char shift[4] = { 24, 16, 8, 0 };
    return ((x & (mask << shift[n])) >> shift[n]) & mask;
}

int main()
{
    int x, n, y, z;
    printf("Input x and y for bitAnd ");
    scanf_s("%d %d", &x, &y);
    printf("%d\n", bitAnd(x, y));

    printf("Input x and y for bitXor ");
    scanf_s("%d %d", &x, &y);
    printf("%d\n", bitXor(x, y));

    printf("thirdBit = %d\n", thirdBit());

    printf("Input x, y and z for conditional ");
    scanf_s("%d %d %d", &x, &y, &z);
    printf("%d\n", conditional(x, y, z));

    printf("Input x and n for logicalShift ");
    scanf_s("%d %d", &x, &n);
    printf("%d\n", logicalShift(x, n));

    printf("Input x for sign ");
    scanf_s("%d", &x);
    printf("%d\n", sign(x));

    printf("Input x for bang ");
    scanf_s("%d", &x);
    printf("%d\n", bang(x));

    printf("Input x for isPower2 ");
    scanf_s("%d", &x);
    printf("%d\n", isPower2(x));

    printf("Input x and n for fitBits ");
    scanf_s("%d %d", &x, &n);
    printf("%d\n", fitBits(x, n));

    printf("Input x and y for addOK ");
    scanf_s("%d %d", &x, &y);
    printf("%d\n", addOK(x, y));

    printf("Input x and n for getByte ");
    scanf_s("%d %d", &x, &n);
    printf("%d\n", getByte(x, n));
    return 0;
}
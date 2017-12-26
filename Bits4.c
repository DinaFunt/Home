#include <stdio.h>

int bitAnd(int x, int y)
{
    return ~(~x | ~y);
}

int bitXor(int x, int y)
{
    return ~((~(~x & y)) & (~(x & ~y)));
}

int thirdBits(void)
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
    mask = ~(((1 << 31) >> n) << 1);
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

int fitsBits(int x, int n)
{
    int mask, mask_m, mask_s;
    mask_s = 1 << 31;
    mask = mask_s >> (31 + (~n + 2));
    return !(mask_s & x) & !(x & mask) | (!!(mask_s & x) & !(~x & mask));
}

int addOK(int x, int y){
    int sum = x + y;
    int signx = x >> 31;
    int signy = y >> 31;
    int signsum = sum >> 31;
    return !((signx ^ signsum) & (signy ^ signsum));
}

int getByte(int x, int n)
{
    int mask = 0xFF;
    char shift[4] = { 0, 8, 16, 24};
    return ((x & (mask << shift[n])) >> shift[n]) & mask;
}

int main()
{
    int x, n, y, z;
    printf("Input x and y for bitAnd (%%x %%x) ");
    scanf("%x %x", &x, &y);
    printf("%d\n", bitAnd(x, y));

    printf("Input x and y for bitXor (%%x %%x) ");
    scanf("%x %x", &x, &y);
    printf("%d\n", bitXor(x, y));

    printf("thirdBits = %d\n", thirdBits());

    printf("Input x, y and z for conditional (%%d %%d %%d) ");
    scanf("%d %d %d", &x, &y, &z);
    printf("%d\n", conditional(x, y, z));

    printf("Input x and n for logicalShift (%%x %%d) ");
    scanf("%x %d", &x, &n);
    printf("%x\n", logicalShift(x, n));

    printf("Input x for sign ");
    scanf("%d", &x);
    printf("%d\n", sign(x));

    printf("Input x for bang ");
    scanf("%d", &x);
    printf("%d\n", bang(x));

    printf("Input x for isPower2 ");
    scanf("%d", &x);
    printf("%d\n", isPower2(x));

    printf("Input x and n for fitsBits (%%x %%d) ");
    scanf("%x %d", &x, &n);
    printf("%d\n", fitsBits(x, n));

    printf("Input x and y for addOK (%%x %%x) ");
    scanf("%x %x", &x, &y);
    printf("%d\n", addOK(x, y));

    printf("Input x and n for getByte (%%x %%d) ");
    scanf("%x %d", &x, &n);
    printf("%x\n", getByte(x, n));
    return 0;
}

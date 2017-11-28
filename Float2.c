#include <stdio.h>

 #define Mantiss 23
 #define Exponenta 8
 #define Sign 1

 void First(float res, int *s, int *ex, int *man) {
     union union_type
     {
         int x;
         float y;
     } myUni;
     myUni.y = res;
     *s = (myUni.x >> (Mantiss + Exponenta)) & (1);
     *man = myUni.x & 0x7FFFFF;
     *ex = ((myUni.x >> Mantiss) & 0xFF) - 127;
 }

 void Second(float res, int *s, int *ex, int *man) {
     union union_type
     {
         struct struct_type
         {
             unsigned m : Mantiss;
             unsigned e : Exponenta;
             unsigned z : Sign;
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
     *s = (b >> (Mantiss + Exponenta)) & (1);
     *man = (b & (0x7FFFFF));
     *ex = ((b >> Mantiss) & 0xFF) - 127;
 }

 void Print(int *s, int *ex, int *man, float res) {

     char FirstLine[32], SecondLine[32], *fp = FirstLine, *sp = SecondLine;
     int i, j, msk = 1, msk_man = 1 << 22;

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
          *fp++ = ' '; sprintf(fp, "%d", *ex);
          *sp++ = '2'; *sp++ = ' '; *sp++ = '*'; *sp++ = ' '; *sp++ = '1'; *sp++ = '.';
          if ( *man != 0)
          {
               i = Mantiss;
               while (!(*man & msk))
               {
                    msk <<= 1;
                    i--;
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

 const size_t methodsCount = sizeof(mystruct) / sizeof(struct myStruct);

 int ToChoose() {
     int i;
     for (i = 0; i < methodsCount; i++)
     {
         printf("%d) %s\n", i + 1, mystruct[i].description);
     }
     printf("\nInput Your Choice (1..%d): ", methodsCount);
     scanf("%d", &i);
     return i;
 }

 int main() {
     int w, s, ex, man;
     float  fir, sec, res;

     printf("Input two floats: ");
     scanf("%f %f", &fir, &sec);
     res = fir / sec;

     w = ToChoose() - 1;
     if (w < 0 || w > (methodsCount - 1))
     {
         printf("Wrong Choice\n");
         return 0;
     }

     (*mystruct[w].doAction)(res, &s, &ex, &man);

     Print(&s, &ex, &man, res);
     return 0;
 }

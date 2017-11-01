#include <stdio.h>

int main()
{
	char c, d;
	char str[100];
	int i = 0;
	printf("Input one symbol\n");
	scanf_s("%c", &c, 1);
	printf("Input your string\n");
	scanf_s("%s", str, 100);
	while (d = str[i++])
	{
	    if (d != c)
	    {
			printf("%c", d);
		}
	}
	printf("\n");
	return 0;
}
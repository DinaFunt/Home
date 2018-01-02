#include <stdio.h>
#include <string.h>


int main()
{
	FILE *in = fopen("input.txt", "r");

	int i = 0, j = 0;
	char a[50];
	
	while (fgets(a, 50, in)) 
	{
		for (i = 0; strlen(a)-1; i++)
		{
			if ((a[i] == '/') && (a[i + 1] == '/')) 
			{
				j = i;
				while (a[j] != '\n') 
				{
					printf("%s", a[i]);
					j++;
				}
				printf("\n");
				break;
			}
		}
		continue;
	}
	fclose(in);
	return 0;
}
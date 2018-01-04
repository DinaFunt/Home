#include <stdio.h>
#include <string.h>

int main()
{
	FILE *mf = fopen("input.txt", "r");
	char a[50];
	char b[100];
	int i = 0, k = 0, j = 0, l;
	while (fgets(a, 50, mf))
	{
		b[i] = a[strlen(a)];
		k = i;
		i++;
		continue;
	}
	for (j = 0; j <= k; j++){
		for (l = j; l <= k; l++) {
			if (b[i] == b[j]) {
				b[i] = ' ';
				b[j] = ' ';
			}
		}
	}
	for (j = 0; j <= k; j++){
		if (b[j] != ' ') {
			i = j;
		}
	}
	j = 0;
	while (fgets(a, 50, mf))
	{
		if (j == i){
			printf("%s\n", *a);
			break;
		}
		else
		{
			j++;
		}
		continue;
	}
	fclose(mf);
}
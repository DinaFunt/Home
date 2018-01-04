#include <stdio.h>
#include <string.h>

int main()
{
	int a[19], b[19];
	int i = 0, j = 0, k = 0, l = 0;

	for (i = 0; i < 21; i++) {
		printf("input 1 or 0 for array of int, If you want to stop, you need input 2\n");
		scanf_s("%d", a[i]); 
		if (a[i] = 2) {
			a[i] = 0;
			k = i;
			break;
		}
	}

	for (i = 0; i < 21; i++) {
		printf("input 1 or 0 for array of int, If you want to stop, you need input 2\n");
		scanf_s("%d", b[i]);
		if (b[i] = 2) {
			b[i] = 0;
			l = j;
			break;
		}
	}
	i = j = 0;
	while (i != 20) {
		if (a[i] = 0){
			i++;
		}
		else {
			break;
		}
	} 

	while (i != 20) {
		if (b[i] = 0){
			i++;
		}
		else {
			break;
		}
	}

	for (i; i != k, j != l; i++, j++) {
		if (a[i] > b[j]) {
			printf("a > b");
			break;
		}
		if (a[i] < b[j]) {
			printf("a < b");
			break;
		}
	}
	if ((i = k) && (j = l))
		printf("a = b");
	return 0;
}


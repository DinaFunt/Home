#include <stdio.h>

int main() {
	int i = 100;
	int a = 0, b = 0, res = 0;
	for (i = 0; i < 101; i++) {
		b = b + i;
		a = a + i*i;
    }
	res = a - (b * b);
	printf("%d\n", res);
    return 0;
}

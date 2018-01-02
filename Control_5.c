#include <stdio.h>

int main() {
    FILE *f = fopen("File.txt", "r");
    char a[50], r[50];
    int i;
    if (f == 0)
    {
        printf("we can't open a file\n");
        return 0;
    }
    for (i = 0; i < 50; i++)
    {
        r[i] = 0;
    }
    while(!feof(f))
    {
        fgets(a, 50, f);
        for (i = 0; i < 50; i++)
        {
            r[i] = r[i] ^ a[i];
        }
    }
    printf("%s", &r[0]);
    fclose(f);
}

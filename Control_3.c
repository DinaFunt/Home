#include <stdio.h>
#include <string.h>

int main() {
    FILE *f = fopen("myFile.txt", "r");
    char a[100];
    int i;

    while (!feof(f))
    {
        fgets(a, 100, f);
        for (i = 0; i < strlen(a) - 1; i++)
        {
            if ((a[i] == '/') && (a[i + 1] == '/'))
            {
                printf("%s", &a[i]);
                break;
            }
        }
    }
    fclose(f);
}

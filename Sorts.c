#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int a[], int i, int j) {
    int tmp;

    tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

void bubbleSort(int a[], int n) {
    int i, j, tmp;
    int b[n];
     for(i = 0 ; i < n - 1; i++)
        {
       for(j = 0 ; j < n - i - 1 ; j++)
       {
           if(a[j] > a[j+1])
           {
               swap(a, j, j+1);
           }
        }
    }
}

void quickSort(int a[], int first, int last)
{
    if (first < last)
    {
        int left = first, right = last, middle = a[(left + right) / 2];
        do
        {
            while (a[left] < middle) left++;
            while (a[right] > middle) right--;
            if (left <= right)
            {
                swap(a, left, right);
                left++;
                right--;
            }
        } while (left <= right);
        quickSort(a, first, right);
        quickSort(a, left, last);
    }
}

void calcSort(int a[], int n)
{
    int min, max, i, j, t = 0;
    int * count;

    if (a[0] > a[1])
    {
        min = a[1];
        max = a[0];
    }
    else
    {
        min = a[0];
        max = a[1];
    }

    for (i = 2; i < n; i ++)
    {
        if (a[i] > max)
        {
             max = a[i];
        }
        if (a[i] < min)
        {
             min = a[i];
        }
    }

    count = (int *)calloc(max - min, sizeof(int));

    for (i = 0; i < n; i++)
    {
        count[a[i] - min]++;
    }

    for (i = min; i <= max; i++)
    {
        for (j = 0; j < count[i - min]; j++)
        {
            a[t] = i;
            t++;
        }
    }

    free(count);
}

void input(int *a, int *n) {
    int i;
    for (i = 0; i < *n; i++)
    {
       a[i] = rand();
       // scanf("%d", a+i);
     }
}

int main() {
    int w, n, i;
    clock_t tm;
    FILE *f = fopen("Mass.txt", "w");
    srand(time(NULL));

    if (f == NULL)
    {
        printf("File wasn't open\n");
        return 0;
    }

    printf("input a number of elements\n" );
    scanf("%d", &n);

    if (n <= 1)
    {
        printf("incorrect input");
        exit(0);
    }

    int *a;

    a = (int *)malloc(n * sizeof(int));

    if (a == NULL)
    {
        printf("Error (massive)\n");
        return 0;
    }

    printf("Choose the way of sorting:\n 1) Bubble sort\n 2) Quick sort\n 3) Calculating sort\n Input a number 1, 2 or 3\n");
    scanf("%d", &w);

    switch(w) {
        case 1 :
        {
            input(a, &n);
            for (i = 0; i < n; i++)
            {
                fprintf(f, "%d ", a[i]);
            }
            fprintf(f, "\n");
            tm = clock();

            bubbleSort(a, n);

            tm = clock() - tm;
            printf("%f\n",(double) tm / CLOCKS_PER_SEC);
            break;
        }
        case 2 :
        {
            input(a, &n);
            for (i = 0; i < n; i++)
            {
                fprintf(f, "%d ", a[i]);
            }
            fprintf(f, "\n");
            tm = clock();

            quickSort(a, 0, n-1);

            tm = clock() - tm;

            printf("%f\n",(double) tm / CLOCKS_PER_SEC);
            break;
        }
        case 3 :
        {
            input(a, &n);
            for (i = 0; i < n; i++)
            {
                fprintf(f, "%d ", a[i]);
            }
            fprintf(f, "\n");
            tm = clock();
            calcSort(a, n);
            tm = clock() - tm;
            printf("%f\n",(double) tm / CLOCKS_PER_SEC);
            break;
        }
        default :
        {
            printf("Input is incorrect");
            free(a);
            int fclose(FILE *f);
            return 0;
        }
    }
    
    fprintf(f, "\n");
    for(i = 0; i < n; i++)
    {
        fprintf(f,"%d ", a[i]);
    }
    
    int fclose(FILE *f);
    free(a);
    return 0;
}

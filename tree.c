#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>

// This algorithm was taken from "Introduction to Algorithms, Third Edition" by Thomas H. Cormen, Charles E. Leiserson, Ronald L.Rivest, Clifford Stein

void swap(int a[], int i, int j) {
    int tmp;
    tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

void quickSort(int a[], int b[], int first, int last) // a - keys, b - probabilities
{
    if (first < last)
    {
        int left = first, right = last, middle = a[(left + right) / 2];
        do
        {
            while (a[left] < middle)
            {
                left++;
            }
            while (a[right] > middle)
            {
                right--;
            }
            if (left <= right)
            {
                swap(a, left, right);
                swap(b, left, right);
                left++;
                right--;
            }
        }
        while (left <= right);
        quickSort(a, b, first, right);
        quickSort(a, b, left, last);
    }
}

typedef struct node {
    struct node *left;
    struct node *right;
    int num;
} Node;

typedef struct tree {
    Node *head;
} Tree;

void searchTree(int n, int p[], int **e, int **w, int **root) {
    int i, j, l, r, t;

    for (i = 0; i < n; i++)
    {
        e[i][i] = p[i];
        w[i][i] = p[i];
        root[i][i] = i;
    }

    for (l = 2; l <= n; l++)
    {
        for (i = 0; i <= n - l; i++)
        {
            j = i + l - 1;
            e[i][j] = INT_MAX;
            w[i][j] = w[i][j - 1] + p[j];

            for (r = i; r < j + 1; r++)
            {
                if (r - 1 < i)
                {
                    t = e[r + 1][j];
               }
                else if (r + 1 > j)
                {
                    t = e[i][r - 1];
                }
                else
                {
                    t = e[i][r - 1] + e[r + 1][j];
                }
                t += w[i][j];
                if (t < e[i][j])
                {
                    e[i][j] = t;
                    root[i][j] = r;
                }
           }
        }
    }
}

Node* CreateNode(int val)
{
    Node* newNode = (Node *)calloc(1, sizeof(Node));

    if (newNode == NULL)
    {
        printf("Can't callocate memory");
        exit(0);
    }

    newNode->num = val;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

Node *buildTree(int **root, int *k, int begin, int end) {
    int end1, begin1, r;

    r = root[begin][end];
    Node *node = CreateNode(k[r]);

    end1 = end;
    begin1 = r + 1;
    end = r - 1;

    if (end - begin >= 0)
    {
        node->left = buildTree(root, k, begin, end);
    }
    if (end1 - begin1 >= 0)
    {
        node->right = buildTree(root, k, begin1, end1);
    }
    return (node);
}

void printTree(Node *tree, FILE *out)
{
    if (tree->left)
    {
        fprintf(out, "%d -> %d;\n", tree->num, tree->left->num);
    }
    else
    {
        fprintf(out, "%d -> NL_%dl\n", tree->num, tree->num);
    }
    if (tree->left)
    {
        printTree(tree->left, out);
    }
    if (tree->right)
    {
        fprintf(out, "%d -> %d;\n", tree->num, tree->right->num);
    }
    else
    {
        fprintf(out, "%d -> NL_%dr\n", tree->num, tree->num);
    }
    if (tree->right)
    {
        printTree(tree->right, out);
    }

}

void deleteTree(Node *tree) {
    if (tree->left)
    {
        deleteTree(tree->left);
    }
    if (tree->right)
    {
        deleteTree(tree->right);
    }
    free(tree);
}

int **dynamic_array_alloc(int N, int M)
{
    int i;
    int **A = (int **)calloc(N, sizeof(int *));
    for(i = 0; i < N; i++)
    {
        A[i] = (int *)calloc(M, sizeof(int));
    }
    return A;
}

void dynamic_array_free(int **A, int N)
{
    int i;
    for(i = 0; i < N; i++) {
        free(A[i]);
    }
    free(A);
}

int main() {
    FILE *f = fopen("array.txt", "r");
    if (f == NULL)
    {
        printf("cannot open your file\n");
        exit(0);
    }

    FILE *out = fopen("doc.gv", "w");
    if (out == NULL)
    {
        printf("cannot open your file\n");
        exit(0);
    }

    int n = 0, i;
    fscanf(f, "%d", &n);
    int *k = (int *)calloc(n, sizeof(int));
    int *p = (int *)calloc(n, sizeof(int));
    if ((k == NULL) || (p == NULL))
    {
        printf("Cannot allocate memory\n");
        exit(0);
    }
    int **e = dynamic_array_alloc(n, n); // cost of subtrees
    int **w = dynamic_array_alloc(n, n); //sum of probabilities of this combination
    int **root = dynamic_array_alloc(n, n); //the index of head element of this combination

    Tree *tree = calloc(1, sizeof(Tree));
    if (tree == NULL)
    {
        printf("Cannot allocate memory\n");
        exit(0);
    }

    for (i = 0; i < n; i++)
    {
        fscanf(f, "%d %d", &k[i], &p[i]);
    }
    quickSort(k, p, 0, n - 1);
    searchTree(n, p, e, w, root);

    tree->head = buildTree(root, k, 0, n - 1);

    fprintf(out, "digraph G{\n");
    printTree(tree->head, out);
    fprintf(out, "\n}");

    deleteTree(tree->head);

    free(k);
    free(p);
    dynamic_array_free(e, n);
    dynamic_array_free(w, n);
    dynamic_array_free(root, n);
    close(out);
    close(f);
    return 0;
}








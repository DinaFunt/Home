#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define MEM_SIZE 262144
#define STACK_SIZE 1000
#define STRING_SIZE 512
#define LEX_SIZE 8

typedef struct code_string code;
typedef struct label label;

struct code_string {
    int command;
    int value;
    char label_name[LEX_SIZE];
};

struct label {
    int IP_to;
    char label_name[LEX_SIZE];
};

int get_type(char *s)
{
    char *com[10] = {"ld", "st", "ldc", "add", "sub", "cmp",  "jmp", "br", "ret"};
    int i;
    for (i = 0; i < 9; i++)
    {
        if (strcmp(com[i], s) == 0)
        {
            return (i + 1);
        }
    }
    printf("Error: invalid command\n");
    return 0;
}

void Parsing(code *a, FILE *f, label *b, int *IP, int *IP_lab) {
    unsigned char s[STRING_SIZE];
    unsigned char word[LEX_SIZE];
    int i, j, k, flag = 0, length, part;

    *IP = 0;
    *IP_lab = 0;
    for (i = 0; i < STACK_SIZE; i++)
    {
        *a[i].label_name = 0;
    }

    while (fgets(s, STRING_SIZE, f))
    {
        part = 0;
        j = 0;
        flag = 0;

        if (s[0] == ';')
        {
            continue;
        }
        else
        {
            length = strlen(s);
            s[length++] = ' ';
            for (i = 0; i < length; i++)
            {
                if ((s[i] != ' ') && (s[i] != ':') && (s[i] != ';') && (s[i] != '\n'))
                {
                    word[j++] = s[i];
                }
                else
                {
                    if (j != 0)
                    {
                        word[j] = 0;
                        j = 0;
                        if (s[i] == ':')
                        {
                            strcpy(b[*IP_lab].label_name, word);
                            b[*IP_lab].IP_to = *IP;
                            (*IP_lab)++;
                        }
                        else
                        {
                            if (part == 0)
                            {
                                a[*IP].command = get_type(word);
                                if ( (a[*IP].command == 7) || (a[*IP].command == 8))
                                {
                                    flag = 1;
                                }
                                (*IP)++;
                                part++;
                            }
                            else
                            {
                                if (flag == 0)
                                {
                                    a[*IP - 1].value = atoi(word);
                                }
                                else
                                {
                                    strcpy(a[*IP - 1].label_name, word);
                                }
                            }
                        }
                    }
                }
                if (s[i] == ';')
                {
                    break;
                }
            }
        }
    }
}

void LD(int *stack, int *top, int a, int *mem) {
    stack[*top] = mem[a];
    (*top)++;
}

void ST(int addr, int *stack, int *top, int *mem) {
    mem[addr] = stack[*top - 1];
}

void LDC(int *stack, int *top, int a) {
    stack[*top] = a;
    (*top)++;
}

void ADD(int *stack, int *top) {
    stack[*top] = stack[*top - 2] + stack[*top - 1];
    (*top)++;
}

void SUB(int *stack, int *top) {
    stack[*top] = stack[*top - 1] - stack[*top - 2];
    (*top)++;
}

void CMP(int *stack, int *top) {
    if (stack[*top - 1] > stack[*top - 2])
    {
        stack[*top] = 1;
        (*top)++;
    }
    else
    {
        if (stack[*top - 1] < stack[*top - 2])
        {
            stack[*top] = -1;
            (*top)++;
        }
        else
        {
            stack[*top] = 0;
            (*top)++;
        }
    }
}

void JUMP(label *b, char *lab, int IP_lab, int *IP) {
    int i;
    for (i = 0; i < IP_lab; i++)
    {
        if (strcmp(lab, b[i].label_name) == 0)
        {
            *IP = b[i].IP_to - 1;
            return;
        }
    }
    printf("Something goes wrong, we can't find this label!\n");
}

void BR(int *stack, int *top, int IP_lab, int *IP, label *b, char *lab) {
    int i;
    if (stack[*top - 1] != 0)
    {
        for (i = 0; i < IP_lab; i++)
        {
            if (strcmp(lab, b[i].label_name) == 0)
            {
                *IP = b[i].IP_to - 1;
                return;
            }
        }
    }
}

int RET(int *stack, int *top) {
    return stack[*top - 1];
}

int Execution(code *a, label *b, int *c, int IP, int IP_lab) {
    int i = 0;
    int res;
    int top = 0;

    int *stack = (int *)malloc(sizeof(int) * STACK_SIZE);
    if (stack == NULL)
    {
        printf("Error: Cannot allocate memory.\n");
        free(stack);
        return -1;
    }

    for (i = 0; i < IP; i++)
    {
        switch (a[i].command)
        {
            case 1:
                LD(stack, &top, a[i].value, c);
                break;
            case 2:
                ST(a[i].value, stack, &top, c);
                break;
            case 3:
                LDC(stack, &top, a[i].value);
                break;
            case 4:
                ADD(stack, &top);
                break;
            case 5:
                SUB(stack, &top);
                break;
            case 6:
                CMP(stack, &top);
                break;
            case 7:
                JUMP(b, a[i].label_name, IP_lab, &i);
                break;
            case 8:
                BR(stack, &top, IP_lab, &i, b, a[i].label_name);
                break;
            case 9:
                res = RET(stack, &top);
                free(stack);
                return res;
            default:
                printf("Error: code is incorrect\n");
                free(stack);
                return -1;
        }
    }
}

int main() {
    char *filename;
    filename = "GCD.txt";
    FILE *f = fopen(filename, "r");
    int IP, IP_lab;
    int res;
    if (f == NULL)
    {
        printf("Error: cannot open file or incorrect filename\n");
        exit(1);
    }

    code *a = (code *)malloc(STACK_SIZE * sizeof(code));
    if (a == NULL)
    {
        printf("Error: cannot allocate memory for massive of code strings\n");
        exit(1);
    }

    label *b = (label *)malloc((STACK_SIZE / 2) * sizeof(label));
    if (b == NULL)
    {
        printf("Error: cannot allocate memory for massive of label strings\n");
        exit(1);
    }

    int *c = (int *)malloc(MEM_SIZE * sizeof(int));
    if (c == NULL)
    {
        printf("Error: cannot allocate memory for memory\n");
        exit(1);
    }

    Parsing(a, f, b, &IP, &IP_lab);
    res = Execution(a, b, c, IP, IP_lab);

    printf("%d = gcd(%d, %d)\n", res, a[0].value, a[2].value);

    free(a);
    free(b);
    free(c);
    fclose(f);
    return 0;
}

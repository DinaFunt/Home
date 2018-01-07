#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define UpperBound 360
#define COEFF 31

typedef struct hsh_entry hsh_entry;

struct hsh_entry {
    char name[30];
    int  value;
    hsh_entry *next;
};

typedef unsigned int hash_val(unsigned char *str);

hsh_entry *HashTab[UpperBound];
char *TabNames[UpperBound];
hash_val *hash_func;

int stat_arr[UpperBound];
int MaxValue, MaxChain, Words;
char MaxName[30];

unsigned int hsh_val(unsigned char *str)
{
    unsigned int h;
    unsigned char *p;

    h = 0;
    for (p = (unsigned char *)str; *p != 0; p++)
    {
        h = COEFF * h + *p;
    }
    return h % UpperBound;
};

hsh_entry *find_add(unsigned char name[])
{
    int h, l;
    hsh_entry *entry;

    h = (*hash_func)(name);

    for (entry = HashTab[h]; entry != NULL; entry = entry->next)
    {
        if (strcmp((char *)name, entry->name) == 0)
        {
            (entry->value)++;
            return entry;
        }
    }
    entry = (hsh_entry *)malloc(sizeof(hsh_entry));
    if (entry == NULL)
    {
        printf("Error. Can't allocate memory\n");
        exit(0);
    }
    entry->value = 1;
    entry->next = HashTab[h];
    l = strlen((char *)name);
    strcpy(entry->name, (char *)name);
    HashTab[h] = entry;

    return entry;
}

void clear_hash(void) {
    int i;
    hsh_entry *entry, *entry_intr;

    for (i = 1; i < UpperBound; i++)
    {
        entry = HashTab[i];
        while (entry != NULL)
        {
            entry_intr = entry;
            entry = entry->next;
            free(entry_intr);
        }
        HashTab[i] = NULL;
    }
}

void book_processing(void)
{
    FILE *sf;
    unsigned char line[120], word[120], space = 0x20;
    unsigned char dot = (unsigned char)'.', semicolon = (unsigned char)';', colon = (unsigned char)':';
    unsigned char exclamation_point = (unsigned char)'!', question_mark = (unsigned char)'?', comma = (unsigned char)',';
    unsigned char quotation_mark=0x22, dot2 = 0x2e, comma2=0x2c;
    char *book = { "Dzherald_Darrel.Gonchie_Bafuta.txt" };
    int i, j, l;

    hash_func = &hsh_val;
    if ((sf = fopen(book, "r")) == NULL)
    {
        printf("Error when open\n");
        return;
    }
    while (fgets((char *)line, 120, sf))
    {
        l = strlen((char *)line);
        line[l++] = space;
        j = -1;
        for (i = 0; i < l; i++)
        {
            if ((line[i] == 0xa) ||
                (line[i] == dot) ||
                (line[i] == dot2) ||
                (line[i] == comma) ||
                (line[i] == comma2) ||
                (line[i] == semicolon) ||
                (line[i] == colon) ||
                (line[i] == exclamation_point) ||
                (line[i] == quotation_mark) ||
                (line[i] == question_mark) )
            {
                continue;
            }
            if (line[i] != space)
            {
                word[++j] = line[i];
            }
            else
            {
                if (j != -1)
                {
                    word[++j] = 0;
                    find_add(word);
                    j = -1;
                };
            }
        }
    }

    fclose(sf);
}

void get_stat(void) {
    int i;
    hsh_entry *entry, *entry_intr;
    char ss[11];

    MaxValue = 0;
    MaxChain = 0;
    Words = 0;
    for (i = 1; i < UpperBound; i++)
    {
        stat_arr[i] = 0;
        entry = HashTab[i];
        while (entry != NULL)
        {
            stat_arr[i]++;
            Words++;
            if (entry->value > MaxValue)
            {
                MaxValue = entry->value;
                strcpy(MaxName, entry->name);
            }
            if (MaxChain < stat_arr[i])
            {
                MaxChain = stat_arr[i];
            }
        entry = entry->next;
        }
    }
	printf("Words=%d MaxChain=%d MaxValue=%d MaxName=%s\n", Words,  MaxChain, MaxValue, MaxName);
}

int main() {
    int i;

    for (i = 0; i < UpperBound; i++)
    {
        HashTab[i] = NULL;
    }
    book_processing();
    get_stat();
    clear_hash();
    return 0;
}

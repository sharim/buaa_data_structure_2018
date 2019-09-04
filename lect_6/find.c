/*
作业次数：第六次作业
文件名：find.c
题目：单词查找（查找-基本题）
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define NHASH 3001
#define MULT 37

int count = 0, length;
char dict[3500][50];
int ptr[26][2];
typedef struct hash_dict
{
    char *word;
    struct hash_dict *next;
    struct hash_dict *tail;
} hd;
hd h_dict[3001];
unsigned int hash(char *s)
{
    unsigned int h = 0;
    char *p;
    for (p = s; *p != '\0'; p++)
        h = MULT * h + *p;
    return h % NHASH;
}
void find_1(char *s)
{
    int i, out = 1;
    for (i = 0; i < length; i++)
    {
        if (strcmp(dict[i], s) >= 0)
            break;
    }
    if (i == length)
    {
        out = 0;
        i--;
    }
    else if (strcmp(dict[i], s) > 0)
        out = 0;
    printf("%d %d", out, i + 1);
}
void find_2(char *s, int low, int high)
{
    if (low > high)
    {
        printf("0 %d", count);
        return;
    }
    count++;
    int mid = (low + high) / 2;
    if (strcmp(dict[mid], s) == 0)
    {
        printf("1 %d", count);
        return;
    }
    if (strcmp(dict[mid], s) < 0)
        find_2(s, mid + 1, high);
    else if (strcmp(dict[mid], s) > 0)
        find_2(s, low, mid - 1);
}
void find_3(char *s)
{
    int h = hash(s);
    int v = 0, w = 0;
    hd *p = &h_dict[h];
    if (p->word == NULL)
        printf("0 1");
    else
    {
        while (p)
        {
            v++;
            if (strcmp(p->word, s) == 0)
            {
                w = 1;
                break;
            }
            else if (strcmp(p->word, s) > 0)
                break;
            p = p->next;
        }
        printf("%d %d", w, v);
    }
}
int main()
{
    int mode, i = 0, j, h;
    char word[50];
    FILE *in = fopen("dictionary3000.txt", "r");
    for (j = 0; j < 3000; j++)
    {
        h_dict[j].word = NULL;
        h_dict[j].next = NULL;
        h_dict[j].tail = &h_dict[j];
    }
    while (!feof(in))
    {
        fscanf(in, "%s", dict[i]);
        if (dict[i - 1][0] == 'z' && dict[i][0] != 'z')
            break;
        if (i == 0 || (i && dict[i][0] != dict[i - 1][0]))
            ptr[dict[i][0] - 'a'][0] = i;
        ptr[dict[i][0] - 'a'][1] += 1;
        h = hash(dict[i]);
        if (h_dict[h].word == NULL)
            h_dict[h].word = dict[i];
        else
        {
            hd *p = (hd *)malloc(sizeof(hd));
            p->word = dict[i];
            p->next = NULL;
            p->tail = NULL;
            h_dict[h].tail->next = p;
            h_dict[h].tail = p;
        }
        i++;
    }
    length = i;
    scanf("%s %d", word, &mode);
    switch (mode)
    {
    case 1:
        find_1(word);
        break;
    case 2:
        find_2(word, 0, length - 1);
        break;
    case 3:
        find_2(word, ptr[word[0] - 'a'][0], ptr[word[0] - 'a'][0] + ptr[word[0] - 'a'][1] - 1);
        break;
    case 4:
        find_3(word);
        break;
    default:
        puts("error");
        break;
    }
    system("pause");
    return 0;
}

/*
作业次数：第五次作业
文件名：statistics.c
题目：词频统计（树实现）
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 26
char s[100000], tmp[100];
int count = 0;
typedef struct Trie
{
    int sign;
    struct Trie *next[MAX];
} trie;
struct note
{
    char word[100];
    int num;
} note[1000];
trie *root;
void insert(char *word)
{
    int i;
    for (i = 0; i < strlen(word); i++)
    {
        if (word[i] >= 'A' && word[i] <= 'Z')
            word[i] += 'a' - 'A';
        else if (word[i] < 'a' || word[i] > 'z')
            return;
    }
    trie *p = root;
    while (*word != '\0')
    {
        if (p->next[*word - 'a'] == NULL)
        {
            trie *q = (trie *)malloc(sizeof(trie));
            for (i = 0; i < MAX; i++)
            {
                q->next[i] = NULL;
            }
            q->sign = 0;
            p->next[*word - 'a'] = q;
            p = p->next[*word - 'a'];
        }
        else
        {
            p = p->next[*word - 'a'];
        }
        word++;
    }
    p->sign = 1;
}
int search(char *word)
{
    int i;
    for (i = 0; i < strlen(word); i++)
    {
        if (word[i] >= 'A' && word[i] <= 'Z')
            word[i] += 'a' - 'A';
        else if (word[i] < 'a' || word[i] > 'z')
            return -1;
    }
    trie *p = root;
    while (p != NULL && *word != '\0')
    {
        p = p->next[*word - 'a'];
        word++;
    }
    return (p != NULL && p->sign == 1);
}
int cmp(const void *a, const void *b)
{
    return strcmp((char *)a, (char *)b);
}
int main()
{
    int i, j;
    root = (trie *)malloc(sizeof(trie));
    for (i = 0; i < MAX; i++)
    {
        root->next[i] = NULL;
    }
    root->sign = 0;
    FILE *in = fopen("article.txt", "rb+");
    fseek(in, 0, SEEK_END);
    int num = ftell(in);
    rewind(in);
    fread(&s[1], sizeof(char), num, in);
    s[0]=' ';
    s[strlen(s)]=' ';
    for (i = 0; i < strlen(s); i++)
    {
        memset(tmp, '\0', sizeof(tmp));
        if (s[i] < 'A' || (s[i] > 'Z' && s[i] < 'a') || s[i] > 'z')
        {
            for (i = i + 1, j = 0; !(s[i] < 'A' || (s[i] > 'Z' && s[i] < 'a') || s[i] > 'z'); i++, j++)
                tmp[j] = s[i];
        }
        i--;
        if (tmp[0] == '\0')
            continue;
        if (search(tmp))
        {
            for (j = 0; j < count; j++)
            {
                if (strcmp(note[j].word, tmp) == 0)
                {
                    note[j].num++;
                    break;
                }
            }
        }
        else
        {
            insert(tmp);
            strcpy(note[count].word, tmp);
            note[count].num = 1;
            count++;
        }
    }
    printf("%s", note[0].word);
    for (i = 0; i < count; i++)
    {
        if (strcmp(note[0].word, note[i].word)<0)
        {
            printf(" %s",note[i].word);
            break;
        }
    }
    for(j=i+1;j<count;j++)
    {
        if (strcmp(note[i].word, note[j].word)<0)
        {
            printf(" %s",note[j].word);
            break;
        }
    }
    printf("\n");
    qsort(note, count, sizeof(note[0]), cmp);
    for (i = 0; i < count; i++)
        printf("%s %d\n", note[i].word, note[i].num);
    system("pause");
    return 0;
}

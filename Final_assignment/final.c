#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 26

int length_1, length_2, out_count = 0;
char *in, *tmp = NULL;
FILE *Dict, *article, *out;
typedef struct Trie
{
    int sign;
    struct Trie *next[MAX];
} trie;
trie *root;
struct note
{
    char *p;
    int count;
    int pos[2001];
} n[250000];

void Init()
{
    int i;
    Dict = fopen("dictionary.txt", "rb");
    article = fopen("article.txt", "rb");
    out = fopen("misspelling.txt", "wb");
    fseek(Dict, 0, SEEK_END);
    fseek(article, 0, SEEK_END);
    length_1 = ftell(Dict);
    length_2 = ftell(article);
    rewind(Dict);
    rewind(article);

    root = (trie *)malloc(sizeof(trie));
    for (i = 0; i < MAX; i++)
        root->next[i] = NULL;
    root->sign = 0;
}
void FileClose()
{
    free(in);
    fclose(Dict);
    fclose(article);
    fclose(out);
}
void Insert(char *word)
{
    int i;
    trie *p = root;
    while (*word >= 'a' && *word <= 'z')
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
            p = p->next[*word - 'a'];
        word++;
    }
    p->sign = 1;
}
int Search(char *word)
{
    trie *p = root;
    while (p != NULL && (*word >= 'a' && *word <= 'z'))
    {
        p = p->next[*word - 'a'];
        word++;
    }
    return (p != NULL && p->sign == 1);
}
void Add(char *word,int length,int pos)
{
    if (Search(word)==0)
    {
        int i;
        for (i = 0; i < out_count; i++)
            if (strncmp(word, n[i].p, length) == 0)
                break;
        if (i == out_count)
        {
            out_count++;
            n[i].p = word;
            n[i].count = 1;
            n[i].pos[0] = pos;
        }
        else
        {
            n[i].count++;
            n[i].pos[n[i].count - 1] = pos;
        }
    }
}
void Segment(int mode, char *s, int length)
{
    int i,j,k=0;
    for (i = 0,j=0; i <= length; i++,j++)
    {
        if ((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z'))
        {
            if (s[i] >= 'A' && s[i] <= 'Z')
                s[i] = s[i] - 'A' + 'a';
            if (tmp == NULL)
                tmp = &s[i];
        }
        else
        {
            if(s[i]=='\r')
                k++;
            if (tmp != NULL)
            {
                if (mode == 1)
                    Insert(tmp);
                else
                    Add(tmp,j,tmp-in-k);
                tmp = NULL;
            }
            j = -1;
        }
    }
}
void ReadDict()
{
    in = (char *)malloc(sizeof(char) * (length_1 + 1));
    fread(in, sizeof(char), length_1, Dict);
    in[length_1] = ' ';
    Segment(1, in, length_1);
}
void ReadArticle()
{
    in = (char *)realloc(in, sizeof(char) * (length_2 + 1));
    fread(in, sizeof(char), length_2, article);
    in[length_2] = ' ';
    Segment(2, in, length_2);
}
void WriteStr(char *s)
{
    while (*s >= 'a' && *s <= 'z')
    {
        fwrite(s, sizeof(char), 1, out);
        s++;
    }
}
void WriteNum(int num)
{
    if (num > 9)
        WriteNum(num / 10);
    char temp = num % 10 + '0';
    fwrite(&temp, sizeof(char), 1, out);
}
int cmp(const void *a, const void *b)
{
    struct note *c = (struct note *)a;
    struct note *d = (struct note *)b;
    if (c->count == d->count)
    {
        char *e = c->p;
        char *f = d->p;
        while (*e >= 'a' && *e <= 'z' && *f >= 'a' && *f <= 'z')
        {
            int judge = *e - *f;
            if (judge != 0)
                return judge;
            else
            {
                e++;
                f++;
            }
        }
        if (*e < 'a' || *e >= 'z')
            return -1;
        else if (*f < 'a' || *f > 'z')
            return 1;
        else
        {
            puts("error");
            return 0;
        }
    }
    else
        return (d->count - c->count);
}

int main()
{
    int i,j;
    Init();
    ReadDict();
    ReadArticle();
    qsort(n, out_count, sizeof(n[0]), cmp);
    for (i = 0; i < out_count; i++)
    {
        WriteStr(n[i].p);
        fputc(' ', out);
        WriteNum(n[i].count);
        fputc(' ', out);
        for (j = 0; j < n[i].count-1;j++)
        {
            WriteNum(n[i].pos[j]);
            fputc(' ', out);
        }
        WriteNum(n[i].pos[j]);
        fputc('\n', out);
    }
    FileClose();
    return 0;
}

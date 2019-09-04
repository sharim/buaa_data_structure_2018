#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 26
#define empty 0
#define length_3 250000

int length_1, length_2, length_4, out_count = 0, side = length_3, pp = 1, last = 0;
char *in,*output;
FILE *Dict, *article, *out;
typedef struct Trie
{
    int sign;
    struct Trie *next[MAX];
} trie;
trie *root;
typedef struct Note
{
    char *p;
    int count;
    int *pos;
    int CrashNum;
    int *crash;
} n;
n *note;

int Hash(char *s)
{
    unsigned long hash = 5381;
    int c;
    while (*s >= 'a' && *s <= 'z')
    {
        c = *s;
        hash = ((hash << 5) + hash) + c;
        s++;
    }
    return hash % length_3;
}
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
    length_4 = length_2/2;
    rewind(Dict);
    rewind(article);

    root = (trie *)malloc(sizeof(trie));
    for (i = 0; i < MAX; i++)
        root->next[i] = NULL;
    root->sign = 0;

    note = (n *)malloc(sizeof(n) * length_3);
    for (i = 0; i < side; i++)
        note[i].count = 0;
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
                q->next[i] = NULL;
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
void Add(char *word, int length, int position)
{
    if (Search(word) == 0)
    {
        int index = Hash(word);
        if (note[index].count == 0)
        {
            out_count++;
            note[index].p = word;
            note[index].count++;
            note[index].pos = (int *)malloc(sizeof(int));
            note[index].pos[0] = position;
            note[index].CrashNum = 1;
            note[index].crash = (int *)malloc(sizeof(int));
            note[index].crash[0] = index;
        }
        else
        {
            int i, j;
            for (i = 0; i < note[index].CrashNum; i++)
            {
                j = note[index].crash[i];
                if (strncmp(word, note[j].p, length) == 0)
                {
                    note[j].pos = (int *)realloc(note[j].pos, sizeof(int) * (note[j].count + 1));
                    note[j].pos[note[j].count] = position;
                    note[j].count++;
                    break;
                }
            }
            if (i == note[index].CrashNum)
            {
                out_count++;
                note[index].CrashNum++;
                note[index].crash = (int *)realloc(note[index].crash, sizeof(int) * note[index].CrashNum);
                note[index].crash[note[index].CrashNum - 1] = side;
                note = (n *)realloc(note, sizeof(n) * (side + 1));
                note[side].p = word;
                note[side].count = 1;
                note[side].pos = (int *)malloc(sizeof(int));
                note[side].pos[0] = position;
                note[side].CrashNum = 1;
                note[side].crash = (int *)malloc(sizeof(int));
                note[side].crash[0] = side;
                side++;
            }
        }
    }
}
void Segment(int mode, char *s, int length)
{
    int i = 0, j = 0, k = 0;
    char *tmp = NULL;
    while (s[i] != '\0')
    {
        if (s[i] == '\r')
        {
            i++;
            continue;
        }
        j++;
        if ((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z'))
        {
            k++;
            if (s[i] >= 'A' && s[i] <= 'Z')
                s[i] = s[i] - 'A' + 'a';
            if (tmp == NULL)
                tmp = &s[i];
        }
        else
        {
            if (s[i] != '\n' && mode == 1)
            {
                int v;
                for (v = i; s[v] != '\n'; v++)
                    ;
                i = v + 1;
                continue;
            }
            if (tmp != NULL)
            {
                if (mode == 1)
                    Insert(tmp);
                else
                    Add(tmp, k, j - k - 1);
                tmp = NULL;
            }
            k = 0;
        }
        i++;
    }
}
void ReadDict()
{
    in = (char *)malloc(sizeof(char) * (length_1 + 2));
    fread(in, sizeof(char), length_1, Dict);
    in[length_1] = '\n';
    in[length_1 + 1] = '\0';
    Segment(1, in, length_1);
}
void ReadArticle()
{
    in = (char *)realloc(in, sizeof(char) * (length_2 + 2));
    fread(in, sizeof(char), length_2, article);
    in[length_2] = ' ';
    in[length_2 + 1] = '\0';
    Segment(2, in, length_2);
}
void IsOverFlow()
{
    if (last == length_4)
    {
        length_4 += 1000;
        output = (char *)realloc(output,sizeof(char) * length_4);
    }
}
void WriteStr(char *s)
{
    while (*s >= 'a' && *s <= 'z')
    {
        IsOverFlow();
        output[last] = *s;
        last++;
        s++;
    }
}
void WriteNum(int num)
{
    if (num > 9)
        WriteNum(num / 10);
    IsOverFlow();
    output[last] = num % 10 + '0';
    last++;
}
int Cmp(const void *a, const void *b)
{
    n *c = (n *)a;
    n *d = (n *)b;
    if (c->count == 0)
    {
        c->count = empty - pp;
        pp++;
    }
    if (d->count == 0)
    {
        d->count = empty - pp;
        pp++;
    }
    if (c->count != d->count)
        return (d->count - c->count);
    else
    {
        char *e = c->p;
        char *f = d->p;
        while (*e >= 'a' && *e <= 'z' && *f >= 'a' && *f <= 'z')
        {
            int judge = *e - *f;
            if (judge != 0)
                return judge;
            e++;
            f++;
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
    puts("error");
    return 0;
}
void Conversion()
{
    int i, j;
    output = (char *)malloc(sizeof(char) * length_4);
    for (i = 0; i < out_count; i++)
    {
        WriteStr(note[i].p);
        IsOverFlow();
        output[last] = ' ';
        last++;
        WriteNum(note[i].count);
        IsOverFlow();
        output[last] = ' ';
        last++;
        for (j = 0; j < note[i].count - 1; j++)
        {
            WriteNum(note[i].pos[j]);
            IsOverFlow();
            output[last] = ' ';
            last++;
        }
        WriteNum(note[i].pos[j]);
        IsOverFlow();
        output[last] = '\n';
        last++;
    }
}

int main()
{
    Init();
    ReadDict();
    ReadArticle();
    qsort(note, side, sizeof(n), Cmp);
    Conversion();
    fwrite(output, sizeof(char), last, out);
    FileClose();
    return 0;
}

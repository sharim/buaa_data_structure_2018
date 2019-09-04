#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define in_max 425
#define MAX 26

int length_1, length_2, out_count = 0;
long t1,t2;
char in[in_max + 1], real[in_max + 1], temp[100], tmp[100], o[150000], n[10];
FILE *Dict, *article, *out;
typedef struct Trie
{
    int sign;
    struct Trie *next[MAX];
} trie;
typedef struct note
{
    char word[100];
    int *position;
    int times;
    struct note *front, *next;
} note;
trie *root;
note *head;

void Init();
void reverse(char *s);
void File_close();
void segment(int mode, char *s, int num, int sum);
void insert(char *word);
void Read(FILE *from, int length, int mode);
int search(char *word);
void Add(char *word, int pos, int judge);

int main()
{
    t1=clock();
    Init();
    Read(Dict, length_1, 1);
    Read(article, length_2, 2);
    note *get = head;
    t2=clock();
    while(t2-t1<=5000)
        t2=clock();
    while (get)
    {
        int v;
        fprintf(out, "%s %d ", get->word, get->times);
        for (v = 0; v < get->times - 1; v++)
            fprintf(out, "%d ", get->position[v]);
        fprintf(out, "%d\n", get->position[v]);
        get = get->next;
    }
    File_close();
    system("pause");
    return 0;
}

void Init()
{
    int i;
    Dict = fopen("dictionary.txt", "rb+");
    article = fopen("article.txt", "rb+");
    out = fopen("misspelling.txt", "wb");
    fseek(Dict, 0, SEEK_END);
    fseek(article, 0, SEEK_END);
    fprintf(Dict, "\r\n");
    fprintf(article, "\r\n");
    length_1 = ftell(Dict);
    length_2 = ftell(article);
    rewind(Dict);
    rewind(article);

    root = (trie *)malloc(sizeof(trie));
    for (i = 0; i < MAX; i++)
    {
        root->next[i] = NULL;
    }
    root->sign = 0;

    head = (note *)malloc(sizeof(note));
    head->times = 0;
    head->word[0] = '\0';
    head->position = NULL;
    head->front = NULL;
    head->next = NULL;
}
void reverse(char *s)
{
    int t, i, j;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
    {
        t = s[i];
        s[i] = s[j];
        s[j] = t;
    }
}
void File_close()
{
    fclose(Dict);
    fclose(article);
    fclose(out);
}
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
void segment(int mode, char *s, int num, int sum)
{
    int p = 0;
    if (mode == 1)
    {
        if (strchr(s, '\n') == s)
        {
            insert(temp);
            memset(temp, '\0', strlen(temp));
            p++;
        }
        else
        {
            p = strchr(s, '\n') - s + 1;
            strncat(temp, s, p - 1);
            insert(temp);
            memset(temp, '\0', strlen(temp));
        }
        if (s[num - 1] != '\n')
        {
            int flag = strrchr(s, '\n') - s + 1;
            strcpy(temp, &s[flag]);
            s[flag] = '\0';
        }
        while (strchr(&s[p], '\n') != NULL)
        {
            int len = strchr(&s[p], '\n') - &s[p];
            strncpy(tmp, &s[p], len);
            insert(tmp);
            memset(tmp, '\0', strlen(tmp));
            p += len + 1;
        }
    }
    else
    {
        while (strchr(s, '\n') != NULL)
        {
            p = strchr(s, '\n') - s;
            s[p] = ' ';
        }
        p = 0;
        if (strchr(s, ' ') == s)
        {
            Add(temp, sum - strlen(temp), 1);
            memset(temp, '\0', strlen(temp));
            p++;
        }
        else
        {
            int y = strlen(temp);
            p = strchr(s, ' ') - s + 1;
            strncat(temp, s, p - 1);
            Add(temp, sum - y, 1);
            memset(temp, '\0', strlen(temp));
        }
        if (s[num - 1] != ' ' && strrchr(s, ' ') != NULL)
        {
            int flag = strrchr(s, ' ') - s + 1;
            strcpy(temp, &s[flag]);
            s[flag] = '\0';
        }
        while (strchr(&s[p], ' ') != NULL)
        {
            int len = strchr(&s[p], ' ') - &s[p];
            strncpy(tmp, &s[p], len);
            Add(tmp, sum + p, 1);
            memset(tmp, '\0', strlen(tmp));
            p += len + 1;
        }
    }
}
void Read(FILE *from, int length, int mode)
{
    int count = 0, sum = 0;
    while (count != length)
    {
        int in_num = length - count;
        if (count + in_max < length)
        {
            count += in_max;
            in_num = in_max;
        }
        else
        {
            count = length;
        }
        fread(in, sizeof(char), in_num, from);
        in[in_num] = '\0';

        int p = 0, cut = 0;
        while (strchr(&in[p], '\r') != NULL)
        {
            int len = strchr(&in[p], '\r') - &in[p];
            strncat(real, &in[p], len);
            p += len + 1;
            cut++;
        }
        strcat(real, &in[p]);
        segment(mode, real, in_num - cut, sum);
        sum += in_num - cut;
        memset(real, '\0', strlen(real));
    }
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
void Add(char *word, int pos, int judge)
{
    if (*word == '\0')
        return;
    if (judge == 1)
    {
        int i;
        for (i = 0; i < strlen(word); i++)
        {
            if (word[i] >= 'A' && word[i] <= 'Z')
                word[i] += 'a' - 'A';
            else if ((word[i] < 'a' || word[i] > 'z'))
                word[i] = ' ';
        }
        word[strlen(word)] = ' ';
        word[strlen(word)] = '\0';
        int d = 0;
        char Temp[100];
        memset(Temp, '\0', sizeof(Temp));
        while (strchr(&word[d], ' ') != NULL)
        {
            int len = strchr(&word[d], ' ') - &word[d];
            strncpy(Temp, &word[d], len);
            Add(Temp, pos + d, 0);
            memset(Temp, '\0', strlen(Temp));
            d += len + 1;
        }
        return;
    }
    if (search(word) == 0)
    {
        note *now = head;
        while (now)
        {
            if (strcmp(now->word, word) == 0 || now->times == 0)
            {
                if (now->times == 0)
                {
                    now->times = 1;
                    strcpy(now->word, word);
                    now->position = (int *)malloc(sizeof(int));
                    now->position[0] = pos;
                    break;
                }
                now->times++;
                if (now->position == NULL)
                    now->position = (int *)malloc(sizeof(int));
                else
                    now->position = (int *)realloc(now->position, now->times * sizeof(int));
                now->position[now->times - 1] = pos;
                while (now->front != NULL && (now->times > now->front->times || (now->times == now->front->times && strcmp(now->word, now->front->word) < 0)))
                {
                    if (now->front->front != NULL)
                    {
                        now->front->front->next = now;
                    }
                    if (now->next != NULL)
                    {
                        now->next->front = now->front;
                    }
                    note *f = now->front;
                    now->front = f->front;
                    f->next = now->next;
                    now->next = f;
                    f->front = now;
                    if (f == head)
                    {
                        head = now;
                    }
                }
                break;
            }
            else
            {
                if (now == head && head->times == 1 && strcmp(word, head->word) < 0)
                {
                    note *new_head = (note *)malloc(sizeof(note));
                    strcpy(new_head->word, word);
                    new_head->times = 1;
                    new_head->position = (int *)malloc(sizeof(int));
                    new_head->position[0] = pos;
                    new_head->front = head->front;
                    new_head->next = head;
                    head->front = new_head;
                    head = new_head;
                    break;
                }
                else if (now->next == NULL && (now->times > 1 || strcmp(word, now->word) > 0))
                {
                    note *new_tail = (note *)malloc(sizeof(note));
                    strcpy(new_tail->word, word);
                    new_tail->times = 1;
                    new_tail->position = (int *)malloc(sizeof(int));
                    new_tail->position[0] = pos;
                    new_tail->next = now->next;
                    new_tail->front = now;
                    now->next = new_tail;
                    break;
                }
                else if (now->front != NULL && (now->front->times > 1 || strcmp(word, now->front->word) > 0) && (now->times == 1 && strcmp(word, now->word) < 0))
                {
                    note *new_body = (note *)malloc(sizeof(note));
                    strcpy(new_body->word, word);
                    new_body->times = 1;
                    new_body->position = (int *)malloc(sizeof(int));
                    new_body->position[0] = pos;
                    new_body->front = now->front;
                    new_body->next = now;
                    now->front->next = new_body;
                    now->front = new_body;
                    break;
                }
            }
            now = now->next;
        }
    }
}

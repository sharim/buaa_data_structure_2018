/*
作业次数：第五次作业
文件名：compress.c
题目：Huffman编码文件压缩
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
    char out[200],
    tmp[100];
struct key
{
    char chr[2];
    char code[100];
} key[96];
typedef struct note
{
    char chr[2];
    char code[100];
    int num;
    struct note *link;
    struct note *lchild;
    struct note *rchild;
} nt;
nt note[96], *head;
int cmp(const void *a, const void *b)
{
    nt *p = (nt *)a;
    nt *q = (nt *)b;
    if (p->num == q->num)
        return (strcmp(p->chr, q->chr));
    else
        return (p->num - q->num);
}
void visit(nt *(*p), char s[])
{
    if (*p)
    {
        strcat((*p)->code, s);
        if ((*p)->lchild)
        {
            strcpy((*p)->lchild->code, (*p)->code);
            strcpy((*p)->rchild->code, (*p)->code);
        }
        visit(&((*p)->lchild), "0");
        visit(&((*p)->rchild), "1");
    }
}
int comp(const void *a, const void *b)
{
    struct key *p = (struct key *)a;
    struct key *q = (struct key *)b;
    return (strcmp(p->chr, q->chr));
}
int main()
{
    int i, j;
    char *get;
    for (i = 0; i < 96; i++)
    {
        if (i)
        {
            note[i].chr[0] = ' ' + i - 1;
            note[i].num = 0;
        }
        else
        {
            note[i].chr[0] = '\0';
            note[i].num = 1;
        }
        memset(note[i].code, '\0', sizeof(note[i].code));
        note[i].chr[1] = '\0';
        note[i].link = NULL;
        note[i].lchild = NULL;
        note[i].rchild = NULL;
        memset(key[i].chr, '\0', sizeof(key[i].chr));
        memset(key[i].code, '\0', sizeof(key[i].code));
    }
    FILE *in = fopen("input.txt", "rb");
    FILE *output = fopen("output.txt", "w");
    fseek(in, 0, SEEK_END);
    int length = ftell(in);
    rewind(in);
    get = (char *)malloc(sizeof(char) * (length + 1));
    fread(get, sizeof(char), length, in);
    get[length] = '\0';
    for (i = 0; i < length; i++)
    {
        if (get[i] == '\n' || get[i] == '\r')
            continue;
        note[get[i] - ' ' + 1].num++;
    }
    qsort(note, 96, sizeof(note[0]), cmp);
    for (i = 0; note[i].chr[0] != '\0'; i++);
    head = &note[i];
    for (j = i; j < 95; j++)
        note[j].link = &note[j + 1];
    for (; i < 95; i++)
    {
        nt *v = head->link;
        nt *p = (nt *)malloc(sizeof(nt));
        memset(p->code, '\0', sizeof(p->code));
        p->num = head->num + head->link->num;
        p->lchild = head;
        p->rchild = head->link;
        while (v->link && v->link->num <= p->num)
        {
            v = v->link;
        }
        p->link = v->link;
        v->link = p;
        head = head->link->link;
    }
    visit(&head, "\0");
    for (i = 0; i < 96; i++)
    {
        strcpy(key[i].chr, note[i].chr);
        strcpy(key[i].code, note[i].code);
    }
    qsort(key, 96, sizeof(key[0]), comp);
    for (i = 0; i <= length; i++)
    {
        if (get[i] == '\n' || get[i] == '\r')
            continue;
        int k;
        if (get[i])
            strcat(out, key[get[i] - ' ' + 1].code);
        else
            strcat(out, key[0].code);
        for (k = 0; k + 8 <= strlen(out); k += 8)
        {
            int t = 128, o = 0, h;
            for (h = 0; h < 8; h++)
            {
                o += (out[k + h] - '0') * t;
                t = t >> 1;
            }
            fputc(o, output);
            printf("%x", o);
        }
        strcpy(tmp, &out[k]);
        memset(out, '\0', strlen(out));
        strcpy(out, tmp);
        memset(tmp, '\0', strlen(tmp));
    }
    if (out[0] != '\0')
    {
        while (strlen(out) < 8)
        {
            out[strlen(out)] = '0';
        }
        int o = 0, t = 128;
        for (i = 0; i < 8; i++)
        {
            o += (out[i] - '0') * t;
            t = t >> 1;
        }
        fputc(o, output);
        printf("%x", o);
    }
    free(get);
    fclose(in);
    fclose(output);
    system("pause");
    return 0;
}

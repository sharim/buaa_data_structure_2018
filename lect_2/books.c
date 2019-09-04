/*
作业次数：第二次
文件名：books.c
题目：小型图书馆管理系统
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int func, bi_len = 0;
char tmp[5000];

typedef struct book_inf
{
    char name[55];
    char author[25];
    char press[35];
    char pub_date[15];
} bi;
bi b[500];

int cmp(const void *p1, const void *p2)
{
    bi *a = (bi *)p1;
    bi *b = (bi *)p2;
    return (strcmp(a->name, b->name));
}
void lower(char line[])
{
    int i;
    for (i = 0; i < strlen(line); i++)
        if (line[i] >= 'A' && line[i] <= 'Z')
            line[i] = line[i] + 'a' - 'A';
}
void cut(char line[])
{
    int i, k = 0, count = 0;
    char temp[60];
    memset(temp, '\0', sizeof(temp));
    for (i = 0; i < strlen(line); i++)
    {
        if ((line[i] == ' ' || line[i] == '\n') && line[i-1] != ' ')
        {
            count++;
            switch (count)
            {
            case 1:
                strcpy(b[bi_len].name, temp);
                break;
            case 2:
                strcpy(b[bi_len].author, temp);
                break;
            case 3:
                strcpy(b[bi_len].press, temp);
                break;
            case 4:
                strcpy(b[bi_len].pub_date, temp);
                break;
            default:
                puts("error");
                break;
            }
            memset(temp, '\0', sizeof(temp));
            k = 0;
        }
        else
        {
            temp[k] = line[i];
            k++;
        }
        if (count == 4)
        {
            count = 0;
            bi_len++;
        }
    }
}
void pass(bi a[], FILE *b, int len)
{
    int i;
    qsort(a,bi_len,sizeof(a[0]),cmp);
    for (i = 0; i < len; i++)
    {
        fprintf(b, "%-50s%-20s%-30s%-10s", a[i].name, a[i].author, a[i].press, a[i].pub_date);
        if (i < len - 1)
            fprintf(b, "\n");
    }
}
void insert()
{
    scanf("%s %s %s %s", b[bi_len].name, b[bi_len].author, b[bi_len].press, b[bi_len].pub_date);
    bi_len++;
    qsort(b, bi_len, sizeof(b[0]), cmp);
}
void search()
{
    int i;
    char key[55], temp[55];
    scanf("%s", key);
    lower(key);
    for (i = 0; i < bi_len; i++)
    {
        strcpy(temp, b[i].name);
        lower(temp);
        if (strstr(temp, key) != NULL)
            printf("%-50s%-20s%-30s%-10s\n", b[i].name, b[i].author, b[i].press, b[i].pub_date);
    }
}
void del()
{
    int i, count = 0;
    char key[55], temp[55];
    scanf("%s", key);
    lower(key);
    for (i = 0; i < bi_len; i++)
    {
        strcpy(temp, b[i].name);
        lower(temp);
        if (strstr(temp, key) != NULL)
        {
            count++;
            b[i].name[0] = '{';
        }
    }
    qsort(b, bi_len, sizeof(b[0]), cmp);
    bi_len -= count;
}
int to_work(FILE *from,FILE *to)
{
    int func;
    scanf("%d",&func);
    if (func == 0)
    {
        pass(b, to, bi_len);
        fclose(from);
        fclose(to);
        return 0;
    }
    else if (func == 1)
    {
        insert();
        to_work(from,to);
    }
    else if (func == 2)
    {
        search();
        to_work(from,to);
    }
    else if (func == 3)
    {
        del();
        to_work(from,to);
    }
}
int main()
{
    FILE *bk = fopen("books.txt", "r");
    FILE *od = fopen("ordered.txt", "w");
    fread(tmp, sizeof(char), 5000, bk);
    puts(tmp);
    cut(tmp);
    to_work(bk,od);
    return 0;
}
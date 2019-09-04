/*
作业次数：第三次作业
文件名：encode.c
题目：文件加密（环）
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
typedef struct key
{
    char ch, ciphertext;
    struct key *front, *next;
} key;
key k[95], *last, *now;
char in[32];
int cmp(const void *p1, const void *p2)
{
    key *a = (key *)p1;
    key *b = (key *)p2;
    return ((a->ch) - (b->ch));
}
int main()
{
    int i, count = 0;
    char tmp = ' ';
    FILE *fp_in = fopen("in.txt", "r");
    FILE *fp_out = fopen("in_crpyt.txt", "w");
    gets(in);
    for (i = 0; i < 95; i++)
    {
        if (i == 0)
        {
            k[i].front = &k[94];
            k[i].next = &k[i + 1];
        }
        else if (i == 94)
        {
            k[i].front = &k[i - 1];
            k[i].next = &k[1];
        }
        else
        {
            k[i].front = &k[i - 1];
            k[i].next = &k[i + 1];
        }
        if (i < strlen(in))
        {
            int j;
            for (j = 0; j <= count && k[j].ch != in[i]; j++)
            {
            }
            if (j == count + 1)
            {
                k[count].ch = in[i];
                count++;
            }
        }
        else
        {
            int j;
            for (j = 0; j <= count; j++)
            {
                if (k[j].ch == tmp)
                {
                    tmp++;
                    j = -1;
                }
            }
            k[count].ch = tmp;
            count++;
            tmp++;
        }
    }
    while (count < 95)
    {
        int j;
        for (j = 0; j <= count; j++)
        {
            if (k[j].ch == tmp)
            {
                tmp++;
                j = -1;
            }
        }
        k[count].ch = tmp;
        count++;
        tmp++;
    }
    last = &k[0];
    now = &k[1];
    while (count--)
    {
        if (count == 0)
            break;
        int times = last->ch % count == 0 ? count : last->ch, v;
        last->front->next = now;
        now->front = last->front;
        for (v = 1; v <= times - 1; v++)
        {
            now = now->next;
        }
        last->ciphertext = now->ch;
        last = now;
        now = now->next;
    }
    now->ciphertext=k[0].ch;
    while (!feof(fp_in))
    {
        char temp;
        int v;
        fread(&temp, sizeof(char), 1, fp_in);
        if (temp < 32 || temp > 126)
        {
            fwrite(&temp, sizeof(char), 1, fp_out);
            continue;
        }
        else
        {
            for (v = 0; v < 95; v++)
            {
                if (temp == k[v].ch)
                {
                    fwrite(&(k[v].ciphertext), sizeof(char), 1, fp_out);
                    break;
                }
            }
        }
    }
    fclose(fp_in);
    fclose(fp_out);
    system("pause");
    return 0;
}

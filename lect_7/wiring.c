/*
作业次数：第七次作业
文件名：wiring.c
题目：最少布线（图）
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
    typedef struct node
{
    int sign;
    int count;
    int side[100][3];
    struct node *link;
} node;
node *p;
int n, e, count = 0, out[1000], sum = 0,flag=0;
int cmp(const void *a, const void *b)
{
    int *p = (int *)a;
    int *q = (int *)b;
    return (*p-*q);
}
void MinDfs(node *s)
{
    int i,j,min=99999999,min_begin,min_id,min_end,flag=0;
    node *tmp = s;
    s->sign = 1;
    while(s)
    {
        for (j = 0; j < s->count;j++)
        {
            if(min>s->side[j][2] && p[s->side[j][1]].sign!=1)
            {
                flag = 1;
                min = s->side[j][2];
                min_id = s->side[j][0];
                min_begin = s - p;
                min_end = s->side[j][1];
            }
        }
        s = s->link;
    }
    if(flag)
    {
        sum += min;
        out[count] = min_id;
        p[min_begin].link = &p[min_end];
        p[min_end].sign = 1;
        count++;
        MinDfs(tmp);
    }
    else
    {
        qsort(out, count, sizeof(int), cmp);
        printf("%d\n", sum);
        for (i = 0; i < count - 1;i++)
            printf("%d ", out[i]);
        printf("%d\n", out[i]);
    }
}
int main()
{
    int i, id, vi, vj, weight;
    scanf("%d %d", &n, &e);
    p = (node *)malloc(sizeof(node) * n);
    for (i = 0; i < n; i++)
    {
        p[i].count = 0;
        p[i].sign = 0;
        p[i].link = NULL;
    }
    for (i = 0; i < e; i++)
    {
        scanf("%d %d %d %d", &id, &vi, &vj, &weight);
        p[vi].side[p[vi].count][0] = id;
        p[vi].side[p[vi].count][1] = vj;
        p[vi].side[p[vi].count][2] = weight;
        p[vi].count++;
        p[vj].side[p[vj].count][0] = id;
        p[vj].side[p[vj].count][1] = vi;
        p[vj].side[p[vj].count][2] = weight;
        p[vj].count++;
    }
    MinDfs(p);
    return 0;
}

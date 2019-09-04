/*
作业次数：第七次作业
文件名：path.c
题目：独立路径数计算
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int n, e,out[1000];
typedef struct node
{
    int sign;
    int count;
    int side[100][2];
} node;
node *p;
void PathDfs(int begin,int count)
{
    int i;
    p[begin].sign = 1;
    for (i = 0; i < p[begin].count; i++)
    {
        if (p[p[begin].side[i][1]].sign != 1)
        {
            out[count] = p[begin].side[i][0];
            if (p[begin].side[i][1] != n - 1)
                PathDfs(p[begin].side[i][1],count+1);
            else
            {
                int j;
                for (j = 0; j <= count;j++)
                {
                    if(j!=count)
                        printf("%d ", out[j]);
                    else
                        printf("%d\n", out[j]);
                }
            }
        }
    }
    p[begin].sign = 0;
}
int main()
{
    int i, e1, v1, v2;
    scanf("%d %d", &n, &e);
    p = (node *)malloc(sizeof(node) * n);
    for (i = 0; i < n; i++)
    {
        p[i].count = 0;
        p[i].sign = 0;
    }
    for (i = 1; i <= e; i++)
    {
        scanf("%d %d %d", &e1, &v1, &v2);
        p[v1].side[p[v1].count][0] = e1;
        p[v1].side[p[v1].count][1] = v2;
        p[v1].count++;
        p[v2].side[p[v2].count][0] = e1;
        p[v2].side[p[v2].count][1] = v1;
        p[v2].count++;
    }
    PathDfs(0,0);
    return 0;
}

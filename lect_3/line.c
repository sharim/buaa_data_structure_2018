/*
作业次数：第三次作业
文件名：line.c
题目：连续线段
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
typedef struct line
{
    int left_x, left_y, right_x, right_y, sign;
    struct line *next;
} line;
line l[100], *now_head, *now_tail, *head;
int main()
{
    int n, count = 0, i, j, max = 0, tmp[2], ans[2];
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d%d%d%d", &l[i].left_x, &l[i].left_y, &l[i].right_x, &l[i].right_y);
        l[i].next = NULL;
        l[i].sign = 0;
    }
    for (i = 0; i < n - 1; i++)
    {
        if (l[i].next != NULL)
            continue;
        now_head = &l[i], now_tail = &l[i];
        for (j = i + 1; j < n; j++)
        {
            if (l[j].next != NULL)
                continue;
            if (l[j].right_x == now_head->left_x && l[j].right_y == now_head->left_y)
            {
                l[j].next = now_head;
                now_head = &l[j];
                j = i;
            }
            else if (l[j].left_x == now_tail->right_x && l[j].left_y == now_tail->right_y)
            {
                now_tail->next = &l[j];
                now_tail = &l[j];
                j = i;
            }
        }
    }
    for (i = 0; i < n; i++)
    {
        if (l[i].sign == 1)
            continue;
        head = &l[i];
        tmp[0] = head->left_x;
        tmp[1] = head->left_y;
        while (head != NULL)
        {
            head->sign = 1;
            head = head->next;
            count++;
        }
        if (count > max)
        {
            max = count;
            ans[0] = tmp[0];
            ans[1] = tmp[1];
        }
        count = 0;
    }
    printf("%d %d %d", max, ans[0], ans[1]);
    system("pause");
    return 0;
}

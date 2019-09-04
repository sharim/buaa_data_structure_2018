/*
作业次数：第四次作业
文件名：queue.c
题目：银行排队模拟
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct line
{
    int id;
    int in_time;
    int ans;
    struct line *front;
} line, *Line;
line *tail, *head, *now;
void Add(int length, int turn, int h)
{
    if (length > 0)
    {
        while (length--)
        {
            h++;
            Line p = (Line)malloc(sizeof(line));
            p->id = h;
            p->in_time = turn;
            p->front = NULL;
            head->front = p;
            head = p;
        }
    }
}

int main()
{
        int i, sign = 0;
        int times, now_time = 1;
        int now_sum = 0, total = 0, new_in, out = 0;
        int windows = 3;
        tail = (line *)malloc(sizeof(line));
        tail->front = NULL;
        head = tail;
        scanf("%d", &times);
        while (1)
        {
            new_in = -1;
            if (now_time > times && out == total)
                break;
            if (now_time <= times)
            {
                Line tmp = head;
                scanf("%d", &new_in);
                Add(new_in, now_time, total);
                if (tmp != NULL && now == NULL)
                    now = tmp->front;
                if (tail->front != NULL && sign == 0)
                {
                    now = tail->front;
                    sign = 1;
                }
                total += new_in;
            }
            now_sum = total - out;
            if (now_sum / windows < 7)
            {
                if (now_sum / (windows - 1) < 7)
                    windows = (windows - 1 > 3) ? (windows - 1) : 3;
                else if (now_sum / (windows - 2) < 7)
                    windows = 3;
                else
                    windows = (windows - 1 > 3) ? (windows - 1) : 3;
            }
            else if (new_in != -1 && now_sum / (windows + 1) < 7)
                windows = (windows + 1 <= 5) ? (windows + 1) : 5;
            else if (new_in != -1 && now_sum / (windows + 2) < 7)
                windows = 5;
            else if (new_in != -1 && now_sum / (windows + 2) >= 7)
                windows = 5;
            out += (now_sum < windows) ? now_sum : windows;
            for (i = 0; i < windows && i < now_sum; i++)
            {
                now->ans = (now_time) - (now->in_time);
                now = now->front;
            }
            now_time++;
        }
        Line get = tail->front;
        while (get)
        {
            printf("%d : %d\n", get->id, get->ans);
            get = get->front;
        }
        while (tail)
        {
            Line p;
            p = tail;
            tail = tail->front;
            free(p);
        }
    system("pause");
    return 0;
}

/*
作业次数：第四次作业
文件名：stack.c
题目：栈操作
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int top = -1;
char in[500], stack[100][1000];
int main()
{
    int i, mode, num;
    gets(in);
    for (i = 0; in[i] != '\0' && (in[i] != '-' && in[i + 1] != '1'); i += 2)
    {
        if (in[i] == '1')
        {
            top = top < -1 ? -1 : top;
            top++;
            int j = i + 2;
            if (top > 99)
            {
                printf("error ");
                continue;
            }
            while (in[j] != ' ')
            {
                stack[top][strlen(stack[top])] = in[j];
                ++j;
            }
            i = j - 1;
            continue;
        }
        else if (in[i] == '0')
        {
            top = top > 99 ? 99 : top;
            top--;
            if (top < -1)
            {
                printf("error ");
                continue;
            }
            printf("%s ", stack[top + 1]);
            memset(stack[top + 1], '\0', sizeof(stack[top + 1]));
        }
    }
    system("pause");
    return 0;
}

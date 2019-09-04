/*
作业次数：第一次作业
文件名：expand.c
题目：扩展字符A
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
char s[1000];
int main()
{
    int h, j;
    scanf("%s", s);
    for (h = 0; h < strlen(s); h++)
    {
        if (s[h] != '-')
            printf("%c", s[h]);
        else
        {
            if (s[h - 1] >= '0' && s[h - 1] <= '9' && s[h + 1] >= '0' && s[h + 1] <= '9')
            {
                for (j = 1; j < s[h + 1] - s[h - 1]; j++)
                    printf("%c", s[h - 1] + j);
            }
            else if (s[h - 1] >= 'a' && s[h - 1] <= 'z' && s[h + 1] >= 'a' && s[h + 1] <= 'z')
            {
                for (j = 1; j < s[h + 1] - s[h - 1]; j++)
                    printf("%c", s[h - 1] + j);
            }
            else if (s[h - 1] >= 'A' && s[h - 1] <= 'Z' && s[h + 1] >= 'A' && s[h + 1] <= 'Z')
            {
                for (j = 1; j < s[h + 1] - s[h - 1]; j++)
                    printf("%c", s[h - 1] + j);
            }
            else
                printf("%c", s[h]);
        }
    }
    system("pause");
    return 0;
}

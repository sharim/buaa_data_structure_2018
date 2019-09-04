/*
作业次数：第一次作业
文件名：notation.c
题目：小数形式与科学计数法转换（简）
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
char num[105];
int a, b;
void reverse(char s[])
{
    int temp, i, j;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
    {
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }
}
void del(char str[])
{
    int i;
    char *p = strstr(str, ".");
    int n = p - str;
    for (i = n; str[i] != '\0'; i++)
        str[i] = str[i + 1];
}
int main()
{
    int i, j = 0, k = 0;
    gets(num);
    for (i = 0; num[i] != '\0'; i++)
    {
        if (num[i] == '.')
        {
            j = 1;
            continue;
        }
        if (j == 0)
            a++;
        else
            b++;
    }
    if (a == 1 && num[0] > '0')
        printf("%se0", num);
    else
    {
        del(num);
        if (a > 1)
            printf("%c.%se%d", num[0], &num[1], a - 1);
        else
        {
            reverse(num);
            for (i = strlen(num) - 1; num[i] == '0'; i--)
            {
                k++;
                num[i] = '\0';
            }
            reverse(num);
            if (a + b - k == 1)
                printf("%se-%d", num, b);
            else
                printf("%c.%se-%d", num[0], &num[1], k);
        }
    }
    system("pause");
    return 0;
}

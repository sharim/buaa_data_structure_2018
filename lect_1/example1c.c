/*
作业次数：第一次作业
文件名：example1c.c
题目：表达式计算（支持空格，连乘，连除）
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char posture_str[1000], tmp[100];
int num[1000], k = 0, ans = 0;
//除法运算
int Division(int num, char num_str[])
{
    return (num / atoi(num_str));
}

//对等式做分割处理
void cut(char s[])
{
    int i, j = 0, sn = 1;
    for (i = 0; s[i] != '\0'; i++)
    {
        if (s[i] == ' ')
            continue;
        else if (s[i] == '+')
        {
            if (sn != -19991007)
            {
                num[j] = sn * atoi(tmp);
                j++;
            }
            else
            {
                num[j] = Division(num[j - 1], tmp);
                j++;
                num[j - 2] = 0;
            }
            memset(tmp, '\0', sizeof(tmp));
            sn = 1;
        }
        else if (s[i] == '-')
        {
            if (sn != -19991007)
            {
                num[j] = sn * atoi(tmp);
                j++;
            }
            else
            {
                num[j] = Division(num[j - 1], tmp);
                j++;
                num[j - 2] = 0;
            }
            memset(tmp, '\0', sizeof(tmp));
            sn = -1;
        }
        else if (s[i] == '*')
        {
            if (sn != -19991007)
            {
                num[j] = sn * atoi(tmp);
                j++;
            }
            else
            {
                num[j] = Division(num[j - 1], tmp);
                j++;
                num[j - 2] = 0;
            }
            memset(tmp, '\0', sizeof(tmp));
            sn = num[j - 1];
            num[j - 1] = 0;
        }
        else if (s[i] == '/')
        {
            if (sn != -19991007)
            {
                num[j] = sn * atoi(tmp);
                j++;
            }
            else
            {
                num[j] = Division(num[j - 1], tmp);
                j++;
                num[j - 2] = 0;
            }
            memset(tmp, '\0', sizeof(tmp));
            sn = -19991007;
        }
        else if (s[i] == '=')
        {
            if (sn != -19991007)
            {
                num[j] = sn * atoi(tmp);
                j++;
            }
            else
            {
                num[j] = Division(num[j - 1], tmp);
                j++;
                num[j - 2] = 0;
            }
        }
        else
        {
            char num_tmp[2];
            num_tmp[0] = s[i];
            strcat(tmp, num_tmp);
        }
        k = j;
    }
}

int main()
{
    int i;
    scanf("%[^\n]", posture_str);
    cut(posture_str);
    for (i = 0; i < k; i++)
        ans += num[i];
    printf("%d\n", ans);
    system("pause");
    return 0;
}

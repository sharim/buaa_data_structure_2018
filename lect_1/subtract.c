/*
??????????
????subtract.c
???????????
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char a[81], b[81], c[81];
int sign = 1;

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

void del_0(char num_str[])
{
    int k;
    for (k = strlen(num_str) - 1; num_str[k] == '0' && k > 0; k--)
        num_str[k] = '\0';
    return;
}

void swap(char str_1[], char str_2[])
{
    char tmp[81];
    strcpy(tmp, str_1);
    strcpy(str_1, str_2);
    strcpy(str_2, tmp);
}

void cmp_then_swap(char str_3[], char str_4[])
{
    int v;
    if (strlen(str_3) < strlen(str_4))
    {
        swap(str_3, str_4);
        sign = -1;
    }
    else if (strlen(str_3) == strlen(str_4))
    {
        for (v = strlen(str_3) - 1; v >= 0; v--)
        {
            if (str_3[v] < str_4[v])
            {
                swap(str_3, str_4);
                sign = -1;
                break;
            }
            else if (str_3[v] == str_4[v])
                continue;
            else
                break;
        }
    }
}

int main()
{
    int i, j, k;
    scanf("%s %s", a, b);
    reverse(a);
    reverse(b);
    del_0(a);
    del_0(b);
    cmp_then_swap(a, b);
    for (i = 0; a[i] != '\0' && b[i] != '\0'; i++)
    {
        if (a[i] - b[i] >= 0)
            c[i] = '0' + (a[i] - b[i]);
        else
        {
            for (j = i + 1; a[j] != '\0'; j++)
            {
                if (a[j] > '0')
                {
                    a[j] = a[j] - 1;
                    for (k = j - 1; k >= i; k--)
                    {
                        if (k == i)
                            c[i] = '0' + (a[i] - b[i] + 10);
                        else
                            a[k] = '9';
                    }
                    break;
                }
            }
        }
    }
    while (a[i] != '\0')
    {
        c[i] = a[i];
        i++;
    }
    del_0(c);
    reverse(c);
    if (sign == -1)
        printf("-");
    printf("%s", c);
    system("pause");
    return 0;
}

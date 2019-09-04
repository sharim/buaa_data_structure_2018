/*
作业次数：第四次作业
文件名：matching.c
题目：C程序括号匹配检查
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char line[200], stack[405], ans[405];
int sign[405], top = -1, line_count = 0, count = 0;

int main()
{
    int i, line_count = 0;
    char *p;
    FILE *in = fopen("example.c", "r+");
    fseek(in,0,SEEK_END);
    fprintf(in,"\n\n");
    rewind(in);
    if (in == NULL)
        printf("error");
    while (!feof(in))
    {
        fgets(line, 10000, in);
        line_count++;
        for (i = 0; line[i] != '\0'; i++)
        {
            if (strstr(&line[i], "//") - (&line[i]) == 0)
            {
                break;
            }
            else if (strstr(&line[i], "/*") - (&line[i]) == 0)
            {
                if (strstr(&line[i], "*/") == NULL)
                {
                    while ((p = strstr(line, "*/")) == NULL)
                    {
                        fgets(line, 100000, in);
                        line_count++;
                    }
                    i = p - line;
                    continue;
                }
                else
                {
                    i = strstr(&line[i], "*/") - line;
                    continue;
                }
            }
            else if (strstr(&line[i], "\'") - (&line[i]) == 0)
            {
                if (strstr(&line[i + 1], "\'") == NULL)
                {
                    while ((p = strstr(line, "\'")) == NULL)
                    {
                        fgets(line, 100000, in);
                        line_count++;
                    }
                    i = p - line;
                    continue;
                }
                else
                {
                    i = strstr(&line[i + 1], "\'") - line;
                    continue;
                }
            }
            else if (strstr(&line[i], "\"") - (&line[i]) == 0)
            {
                if (strstr(&line[i + 1], "\"") == NULL)
                {
                    while ((p = strstr(line, "\"")) == NULL)
                    {
                        fgets(line, 100000, in);
                        line_count++;
                    }
                    i = p - line;
                    continue;
                }
                else
                {
                    i = strstr(&line[i + 1], "\"") - line;
                    continue;
                }
            }
            else if (line[i] == '(')
            {
                ++top;
                stack[top] = line[i];
                ans[count] = line[i];
                count++;
                sign[top] = line_count;
                continue;
            }
            else if (line[i] == ')')
            {
                if (stack[top] == '(')
                {
                    ans[count] = line[i];
                    count++;
                    stack[top] = '\0';
                    top--;
                    continue;
                }
                else
                {
                    printf("without maching \'%c\' at line %d", line[i], line_count);
                    system("pause");
                    return 0;
                }
            }
            else if (line[i] == '{')
            {
                if (stack[top] == '(')
                {
                    printf("without maching \'%c\' at line %d", stack[top], sign[top]);
                    system("pause");
                    return 0;
                }
                else
                {
                    ++top;
                    stack[top] = line[i];
                    ans[count] = line[i];
                    count++;
                    sign[top] = line_count;
                    continue;
                }
            }
            else if (line[i] == '}')
            {
                if (stack[top] == '{')
                {
                    ans[count] = line[i];
                    count++;
                    stack[top] = '\0';
                    top--;
                    continue;
                }
                else
                {
                    printf("without maching \'%c\' at line %d", line[i], line_count);
                    system("pause");
                    return 0;
                }
            }
        }
    }
    if (stack[0] == '{')
    {
        printf("without maching \'%c\' at line %d", stack[0], sign[0]);
    }
    else
    {
        printf("%s", ans);
    }

    system("pause");
    return 0;
}

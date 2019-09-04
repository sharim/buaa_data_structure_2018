/*
作业次数：第三次作业
文件名：word_frequency_statistics.c
题目：词频统计
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
typedef struct dictionary
{
    char word[50];
    int count;
    struct dictionary *front, *next;
} dictionary;
dictionary dict[100], *head, *tail;
int main()
{
    char tmp[50];
    int i, j, sign = 1;
    tmp[0] = ' ';
    for (i = 0; i < 100; i++)
    {
        dict[i].next = NULL;
        dict[i].front = NULL;
        dict[i].count = 0;
    }
    head = &dict[0];
    tail = &dict[0];
    i = 0;
    FILE *in = fopen("article.txt", "r");
    while (!feof(in))
    {
        fscanf(in, "%c", &tmp[strlen(tmp)]);
        if (tmp[strlen(tmp) - 1] >= 'A' && tmp[strlen(tmp) - 1] <= 'Z')
            tmp[strlen(tmp) - 1] = tmp[strlen(tmp) - 1] + 'a' - 'A';
        if (tmp[strlen(tmp) - 1] < 'a' || tmp[strlen(tmp) - 1] > 'z')
        {
            if (tmp[strlen(tmp) - 2] == ' ')
            {
                tmp[strlen(tmp) - 1] = '\0';
                continue;
            }
            else
            {
                tmp[strlen(tmp) - 1] = '\0';
                /*if (sign == 1)
                {
                    memset(tmp, '\0', sizeof(tmp));
                    tmp[0] = ' ';
                    sign = 0;
                    continue;
                }*/
                strcpy(dict[i].word, &tmp[1]);
                memset(tmp, '\0', sizeof(tmp));
                tmp[0] = ' ';
                for (j = 0; j <= i; j++)
                {
                    if (strcmp(dict[i].word, dict[j].word) == 0)
                    {
                        dict[j].count++;
                        if (j == i)
                            i++;
                        break;
                    }
                    else if (strcmp(dict[i].word, dict[j].word) < 0 && &dict[j] == head)
                    {
                        head = &dict[i];
                        dict[i].next = &dict[j];
                        dict[j].front = &dict[i];
                        dict[i].count++;
                        i++;
                        break;
                    }
                    else if (strcmp(dict[i].word, dict[j].word) > 0 && &dict[j] == tail)
                    {
                        tail = &dict[i];
                        dict[i].front = &dict[j];
                        dict[j].next = &dict[i];
                        dict[i].count++;
                        i++;
                        break;
                    }
                    else if (strcmp(dict[i].word, dict[j].word) > 0 && strcmp(dict[i].word, dict[j].next->word) < 0)
                    {
                        dict[i].front = &dict[j];
                        dict[i].next = dict[j].next;
                        dict[j].next = &dict[i];
                        dict[j].next->front = &dict[i];
                        dict[i].count++;
                        i++;
                        break;
                    }
                }
            }
        }
    }
    head = head->next;
    while (head != NULL)
    {
        printf("%s %d\n", head->word, head->count);
        head = head->next;
    }
    system("pause");
    return 0;
}

/*
作业次数：第四次作业
文件名：edit.c
题目：文本编辑操作模拟
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char text[600], tmp[600], temp[600], s[600];
typedef struct command_stack
{
    int command;
    int pos;
    int sign;
    char string[600];
    struct command_stack *front;
    struct command_stack *next;
} comand;
comand head, *tail;

void Init()
{
    head.front = NULL;
    head.next = NULL;
    head.sign = 0;
    tail = &head;
}
void Add(int c, int p, char s[])
{
    if (tail->sign == 1)
    {
        comand *p;
        p = (comand *)malloc(sizeof(head));
        p->front = tail;
        p->next = tail->next;
        tail->next = p;
        tail = p;
    }
    tail->command = c;
    tail->pos = p;
    strcpy(tail->string, s);
    tail->sign = 1;
}
void Insert(int p, char s[])
{
    memset(tmp, '\0', sizeof(tmp));
    strcpy(tmp, &text[p]);
    strcpy(&text[p], s);
    strcpy(&text[strlen(text)], tmp);
}
void del(int p, int num)
{
    // memset(temp, '\0', sizeof(temp));
    // if (p + num > strlen(text))
    //     num = strlen(text) - p;
    // strncpy(temp, &text[p], num);
    // strcpy(&text[p], &text[p + num]);
    int i=p,j;
    memset(temp, '\0', sizeof(temp));
    for(j=0;j<num;j++)
    {
        temp[j]=text[i];
        i++;
    }
    temp[j]='\0';
    for(j=p;j<strlen(text);j++)
    {
        text[j]=text[j+num];
    }
}
void Take()
{
    if (head.sign == 1)
    {
        if (tail->command == 1)
        {
            del(tail->pos, strlen(tail->string));
        }
        else if (tail->command == 2)
        {
            Insert(tail->pos, tail->string);
        }
        if (tail == &head)
        {
            Init();
        }
        else
        {
            comand *p = tail;
            tail = tail->front;
            tail->next = NULL;
            free(p);
        }
    }
}
int main()
{
    int n, c, p;
    gets(text);
    scanf("%d", &n);
    Init();
    while (n--)
    {
        scanf("%d %d %s", &c, &p, s);
        Add(c, p, s);
    }
    while (1)
    {
        scanf("%d", &c);
        if (c == -1)
            break;
        else if (c == 1)
        {
            scanf("%d %s", &p, s);
            Insert(p, s);
            Add(c, p, s);
            // puts(text);
        }
        else if (c == 2)
        {
            int num;
            scanf("%d %d", &p, &num);
            del(p, num);
            Add(c, p, temp);
            // puts(text);
        }
        else if (c == 3)
        {
            Take();
            // puts(text);
        }
    }
    printf("%s",text);
    system("pause");
    return 0;
}

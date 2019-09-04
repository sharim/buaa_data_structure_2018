/*
作业次数：第四次作业
文件名：calculator.c
题目：计算器
*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STACK_INIT_SIZE 14
#define STACK_INCREMENT 2

char expression_in[500], final_expression[500], stack[500];
int stack_top = -1, count = 0, ans;

typedef struct SqStack
{
    int *base;
    int *top;
    int stacksize;
} SqStack;

void Init_stack(SqStack *s)
{
    s->base = (int *)malloc(STACK_INIT_SIZE * sizeof(int));
    if (!s->base)
    {
        printf("error");
        system("pause");
        exit(0);
    }
    s->top = s->base;
    s->stacksize = STACK_INIT_SIZE;
}
void Push_stack(SqStack *s, int num)
{
    if (s->top - s->base >= s->stacksize)
    {
        s->base = (int *)realloc(s->base, (s->stacksize + STACK_INCREMENT) * sizeof(int));
        if (!s->base)
        {
            printf("error");
            system("pause");
            exit(0);
        }
        s->top = s->base + s->stacksize;
        s->stacksize += STACK_INCREMENT;
    }
    *(s->top) = num;
    s->top++;
}
void Pop_stack(SqStack *s, int *num)
{
    if (s->top == s->base)
    {
        printf("error");
        system("pause");
        exit(0);
    }
    s->top--;
    *num = *(s->top);
}

int main()
{
    int i;
    SqStack final_stack;
    Init_stack(&final_stack);
    gets(expression_in);
    for (i = 0; expression_in[i] != '='; i++)
    {
        if (expression_in[i] == ' ')
        {
            if (expression_in[i - 1] >= '0' && expression_in[i - 1] <= '9')
            {
                final_expression[count] = ' ';
                count++;
                continue;
            }
        }
        else if (expression_in[i] >= '0' && expression_in[i] <= '9')
        {
            final_expression[count] = expression_in[i];
            count++;
            continue;
        }
        else if (expression_in[i] == '(')
        {
            if (expression_in[i - 1] >= '0' && expression_in[i - 1] <= '9')
            {
                final_expression[count] = ' ';
                count++;
            }
            stack_top++;
            stack[stack_top] = '(';
            continue;
        }
        else if (expression_in[i] == ')')
        {
            if (expression_in[i - 1] >= '0' && expression_in[i - 1] <= '9')
            {
                final_expression[count] = ' ';
                count++;
            }
            while (stack[stack_top] != '(')
            {
                final_expression[count] = stack[stack_top];
                count++;
                stack[stack_top] = '\0';
                stack_top--;
            }
            stack[stack_top] = '\0';
            stack_top--;
            continue;
        }
        else if (expression_in[i] == '+' || expression_in[i] == '-')
        {
            if (expression_in[i - 1] >= '0' && expression_in[i - 1] <= '9')
            {
                final_expression[count] = ' ';
                count++;
            }
            while (stack[stack_top] != '(' && stack_top > -1)
            {
                final_expression[count] = stack[stack_top];
                count++;
                stack[stack_top] = '\0';
                stack_top--;
            }
            stack_top++;
            stack[stack_top] = expression_in[i];
            continue;
        }
        else if (expression_in[i] == '*' || expression_in[i] == '/' || expression_in[i] == '%')
        {
            if (expression_in[i - 1] >= '0' && expression_in[i - 1] <= '9')
            {
                final_expression[count] = ' ';
                count++;
            }
            while (stack[stack_top] == '*' || stack[stack_top] == '/' || stack[stack_top] == '%')
            {
                final_expression[count] = stack[stack_top];
                count++;
                stack[stack_top] = '\0';
                stack_top--;
            }
            stack_top++;
            stack[stack_top] = expression_in[i];
            continue;
        }
    }
    while (stack_top != -1)
    {
        final_expression[count] = stack[stack_top];
        count++;
        stack[stack_top] = '\0';
        stack_top--;
    }
    puts(final_expression);
    for (i = 0; final_expression[i] != '\0'; i++)
    {
        int j = i, num = 0;
        if (final_expression[i] >= '0' && final_expression[i] <= '9')
        {
            for (j = i; final_expression[j] >= '0' && final_expression[j] <= '9'; j++)
            {
                num = num * 10 + (final_expression[j] - '0');
            }
            i = j - 1;
            Push_stack(&final_stack, num);
            num = 0;
            continue;
        }
        else if (final_expression[i] == ' ')
        {
            continue;
        }
        else
        {
            int get_num_a, get_num_b;
            switch (final_expression[j])
            {
            case '+':
                Pop_stack(&final_stack, &get_num_a);
                Pop_stack(&final_stack, &get_num_b);
                Push_stack(&final_stack, get_num_a + get_num_b);
                break;
            case '-':
                Pop_stack(&final_stack, &get_num_a);
                Pop_stack(&final_stack, &get_num_b);
                Push_stack(&final_stack, get_num_b - get_num_a);
                break;
            case '*':
                Pop_stack(&final_stack, &get_num_a);
                Pop_stack(&final_stack, &get_num_b);
                Push_stack(&final_stack, get_num_a * get_num_b);
                break;
            case '/':
                Pop_stack(&final_stack, &get_num_a);
                Pop_stack(&final_stack, &get_num_b);
                Push_stack(&final_stack, get_num_b / get_num_a);
                break;
            case '%':
                Pop_stack(&final_stack, &get_num_a);
                Pop_stack(&final_stack, &get_num_b);
                Push_stack(&final_stack, get_num_b % get_num_a);
                break;
            default:
                printf("error in switch()");
                break;
            }
        }
    }
    Pop_stack(&final_stack, &ans);
    printf("%d", ans);
    free(final_stack.base);
    system("pause");
    return 0;
}

/*
作业次数：第五次作业
文件名：tree_calculator.c
题目：计算器（表达式计算-表达式树实现）
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
char in[100];
int tmp_stack[100], top_1 = -1, top_2 = -1;
typedef struct calculator_tree
{
    int num;
    struct calculator_tree *lchild;
    struct calculator_tree *rchild;
} tree;
tree *stack[100], *root;
void visit(tree *p)
{
    if (p)
    {
        visit(p->lchild);
        visit(p->rchild);
        if (p->lchild != NULL)
        {
            switch (p->num)
            {
            case '+':
                p->num = p->lchild->num + p->rchild->num;
                break;
            case '-':
                p->num = p->lchild->num - p->rchild->num;
                break;
            case '*':
                p->num = p->lchild->num * p->rchild->num;
                break;
            case '/':
                p->num = p->lchild->num / p->rchild->num;
                break;
            default:
                printf("error");
                break;
            }
        }
    }
}
int main()
{
    int i;
    fgets(in, 100, stdin);
    for (i = 0; in[i] != '='; i++)
    {
        switch (in[i])
        {
        case '(':
        {
            top_1++;
            tmp_stack[top_1] = '(';
        }
        break;
        case ')':
        {
            for (; tmp_stack[top_1] != '('; top_1--)
            {
                top_2--;
                tree *p = (tree *)malloc(sizeof(tree));
                p->num = tmp_stack[top_1];
                p->lchild = stack[top_2];
                p->rchild = stack[top_2 + 1];
                stack[top_2] = p;
            }
            top_1--;
        }
        break;
        case '+':
        {
            if (top_1 != -1 && tmp_stack[top_1] != '(')
            {
                top_2--;
                tree *p = (tree *)malloc(sizeof(tree));
                p->num = tmp_stack[top_1];
                p->lchild = stack[top_2];
                p->rchild = stack[top_2 + 1];
                stack[top_2] = p;
                top_1--;
            }
            top_1++;
            tmp_stack[top_1] = '+';
        }
        break;
        case '-':
        {
            if (top_1 != -1 && tmp_stack[top_1] != '(')
            {
                top_2--;
                tree *p = (tree *)malloc(sizeof(tree));
                p->num = tmp_stack[top_1];
                p->lchild = stack[top_2];
                p->rchild = stack[top_2 + 1];
                stack[top_2] = p;
                top_1--;
            }
            top_1++;
            tmp_stack[top_1] = '-';
        }
        break;
        case '*':
        {
            if (tmp_stack[top_1] == '*' || tmp_stack[top_1] == '/')
            {
                top_2--;
                tree *p = (tree *)malloc(sizeof(tree));
                p->num = tmp_stack[top_1];
                p->lchild = stack[top_2];
                p->rchild = stack[top_2 + 1];
                stack[top_2] = p;
                top_1--;
            }
            top_1++;
            tmp_stack[top_1] = '*';
        }
        break;
        case '/':
        {
            if (tmp_stack[top_1] == '*' || tmp_stack[top_1] == '/')
            {
                top_2--;
                tree *p = (tree *)malloc(sizeof(tree));
                p->num = tmp_stack[top_1];
                p->lchild = stack[top_2];
                p->rchild = stack[top_2 + 1];
                stack[top_2] = p;
                top_1--;
            }
            top_1++;
            tmp_stack[top_1] = '/';
        }
        break;
        case ' ':
            break;
        default:
        {
            int temp = in[i] - '0', aa = 10;
            for (i = i + 1; in[i] >= '0' && in[i] <= '9'; i++)
                temp = temp * aa + (in[i] - '0');
            i--;
            top_2++;
            tree *p = (tree *)malloc(sizeof(tree));
            p->num = temp;
            p->lchild = NULL;
            p->rchild = NULL;
            stack[top_2] = p;
        }
        break;
        }
    }
    while (top_1 != -1)
    {
        top_2--;
        tree *p = (tree *)malloc(sizeof(tree));
        p->num = tmp_stack[top_1];
        p->lchild = stack[top_2];
        p->rchild = stack[top_2 + 1];
        stack[top_2] = p;
        top_1--;
    }
    if (stack[0]->lchild)
        printf("%c", stack[0]->num);
    else
        printf("%d", stack[0]->num);
    if (stack[0]->lchild != NULL)
    {
        if (stack[0]->lchild->lchild)
            printf(" %c", stack[0]->lchild->num);
        else
            printf(" %d", stack[0]->lchild->num);
    }
    if (stack[0]->rchild != NULL)
    {
        if (stack[0]->rchild->rchild)
            printf(" %c", stack[0]->rchild->num);
        else
            printf(" %d", stack[0]->rchild->num);
    }
    visit(stack[0]);
    printf("\n%d\n", stack[0]->num);
    system("pause");
    return 0;
}

/*
作业次数：第五次作业
文件名：bst.c
题目：树叶节点遍历（树-基础题）
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
typedef struct tree
{
    int num;
    int length;
    struct tree *lchild;
    struct tree *rchild;
} tree;
tree *root,*now;
void insert(int in)
{
    if(root==NULL)
    {
        root=(tree *)malloc(sizeof(tree));
        root->num=in;
        root->length=1;
        root->lchild=NULL;
        root->rchild=NULL;
        now=root;
        return;
    }
    tree *tmp=NULL;
    int sign=0,count=1;
    while(now)
    {
        tmp=now;
        count++;
        if(now->num>in)
        {
            now=now->lchild;
            sign=1;
        }
        else
        {
            now=now->rchild;
            sign=0;
        }
    }
    now=(tree *)malloc(sizeof(tree));
    now->num=in;
    now->length=count;
    now->lchild=NULL;
    now->rchild=NULL;
    if(sign)
        tmp->lchild=now;
    else
        tmp->rchild=now;
    now=root;
}
void visit(tree *p)
{
    if(p)
    {
        visit(p->lchild);
        if(p->lchild==NULL && p->rchild==NULL)
            printf("%d %d\n",p->num,p->length);
        visit(p->rchild);
    }
}
int main()
{
    root=NULL;
    int n, in_num;
    scanf("%d", &n);
    while (n--)
    {
        scanf("%d", &in_num);
        insert(in_num);
    }
    visit(root);
    system("pause");
    return 0;
}

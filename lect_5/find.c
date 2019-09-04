/*
作业次数：第五次作业
文件名：find.c
题目：在家谱中查找关系远近
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
char get[3][25];
int a, b;
typedef struct family_tree
{
    char name[25];
    int generation;
    struct family_tree *lchild;
    struct family_tree *rchild;
    struct family_tree *father;
} tree;
tree *l, *r, *f, *c;
tree *init(tree *p, char *s)
{
    if (strcmp(s, "NULL") != 0)
    {
        p = (tree *)malloc(sizeof(tree));
        strcpy(p->name, s);
        p->lchild = NULL;
        p->rchild = NULL;
        p->father = NULL;
    }
    return p;
}
void visit(tree *p, char *s)
{
    if (p)
    {
        visit(p->lchild, s);
        visit(p->rchild, s);
        if (strcmp(p->name, s) == 0)
            f = p;
    }
}
void search(tree *p, char *s, int count, int mode)
{
    if (p)
    {
        search(p->lchild, s, count + 1, mode);
        if (!strcmp(p->name, s))
        {

            if (mode)
            {
                l = p;
                a = count;
            }
            else
            {
                r = p;
                b = count;
            }
        }
        search(p->rchild, s, count + 1, mode);
    }
}
int find()
{
    int count = 0;
    while (l != r)
    {
        count++;
        l = l->father;
        r = r->father;
    }
    c = l;
    return count;
}
int main()
{
    int n;
    tree *root = NULL;
    FILE *in = fopen("in.txt", "r");
    fscanf(in,"%d", &n);
    while (n--)
    {
        tree *p = NULL, *q = NULL;
        fscanf(in, "%s %s %s", get[0], get[1], get[2]);
        p = init(p, get[1]);
        q = init(q, get[2]);
        if (root == NULL)
        {
            root = init(root, get[0]);
            root->lchild = p;
            root->rchild = q;
            if (p)
                p->father = root;
            if (q)
                q->father = root;
            continue;
        }
        visit(root, get[0]);
        f->lchild = p;
        f->rchild = q;
        if (p)
            p->father = f;
        if (q)
            q->father = f;
    }
    scanf("%s %s", get[0], get[1]);
    search(root, get[0], 1, 1);
    search(root, get[1], 1, 0);
    int out = a - b;
    if (out > 0)
        printf("%s %s %d", get[0], get[1], out);
    else if (out < 0)
        printf("%s %s %d", get[1], get[0], -1 * out);
    else
    {
        int v=find();
        printf("%s %s %d\n%s %s %d",c->name,get[0],v,c->name,get[1],v);
    }
    system("pause");
    return 0;
}

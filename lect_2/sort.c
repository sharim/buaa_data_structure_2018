/*
作业次数：第二次
文件名：sort.c
题目：通讯录整理
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct tle_book
{
	char name[23];
	long long num;
} tb;

int cmp(const void *p1, const void *p2)
{
	tb *a = (tb *)p1;
	tb *b = (tb *)p2;
	return (strcmp(a->name, b->name));
}
tb t[100];

int main()
{
	int n, i, j, count = 0;
	char a = 'z' + 1, replace_str[2];
	replace_str[0] = a;
	scanf("%d", &n);
	for (i = 0; i < n; i++)
		scanf("%s %lld", t[i].name, &t[i].num);
	for (i = 0; i < n - 1; i++)
	{
		for (j = i + 1; j < n; j++)
			if (strcmp(t[i].name, t[j].name) == 0)
			{
				if (strcmp(t[i].name, replace_str) == 0)
					continue;
				else if (t[i].num == t[j].num)
					strcpy(t[j].name, replace_str);
				else
				{
					count++;
					sprintf(&t[j].name[strlen(t[j].name)], "_%d", count);
				}
			}
		count = 0;
	}
	qsort(t, n, sizeof(t[0]), cmp);
	for (i = 0; i < n; i++)
	{
		if (strcmp(t[i].name, replace_str) == 0)
			break;
		else
			printf("%s %lld\n", t[i].name, t[i].num);
	}
	system("pause");
	return 0;
}

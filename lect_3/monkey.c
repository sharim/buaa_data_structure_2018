/*
作业次数：第三次作业
文件名：monkey.c
题目：猴子选大王
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
typedef struct monkey
{
	int id;
	struct monkey *next;
} monkey;
monkey mk[1000];
int main()
{
	int n, m, q, i, out_num = 0, now = 0;
	scanf("%d%d%d", &n, &m, &q);
	for (i = 1; i < n; i++)
	{
		mk[i].id = i;
		mk[i].next = &mk[i + 1];
	}
	mk[n].id = n;
	mk[n].next = &mk[1];
	monkey *out = &mk[q];
	while (out_num <= n - 1)
	{
		now++;
		if (now == m - 1)
		{
			out->next = out->next->next;
			now = 0;
			out_num++;
		}
		out = out->next;
	}
	printf("%d", out->id);
	system("pause");
	return 0;
}

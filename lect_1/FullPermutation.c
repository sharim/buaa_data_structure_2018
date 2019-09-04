/*
作业次数：第一次作业
文件名：FullPermutation.c
题目：全排列数的生成
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
int m, vis[20], ans[20];
void dfs(int p)
{
	int i;
	if (p > m)
	{
		for (i = 1; i <= m; ++i)
			printf("%d ", ans[i]);
		printf("\n");
		return;
	}
	for (i = 1; i <= m; ++i)
	{
		if (!vis[i])
		{
			ans[p] = i;
			vis[i] = 1;
			dfs(p + 1);
			vis[i] = 0;
		}
	}
}
int main()
{
	scanf("%d", &m);
	dfs(1);
	system("pause");
	return 0;
}
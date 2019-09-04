/*
作业次数：第七次作业
文件名：graphSearch.c
题目：图遍历（图-基本题）
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
	char a[20];
int point_num, length, side_num, delpoint = -1, count = 1, point[100], sign[100], side[100][100];
void to_zero()
{
	int i;
	count = 1;
	for (i = 0; i < point_num; i++)
	{
		point[i] = 0;
		sign[i] = 0;
	}
}
void dfs(int p)
{
	int i = 0;
	point[p] = 1;
	printf("%d ", p);
	for (i = 0; i < point_num; i++)
	{
		if (point[i] != 1 && side[p][i] == 1)
			dfs(i);
	}
}
void bfs(int p)
{
	int i;
	point[sign[p]] = 1;
	for (i = 0; i < point_num; i++)
	{
		if (point[i] != 1 && side[sign[p]][i] == 1)
		{
			sign[count] = i;
			count++;
			point[i] = 1;
		}
	}
	if (p == length)
		return;
	printf("%d ", sign[p]);
	bfs(p + 1);
}
int main()
{
	int i, begin, end;
	scanf("%d %d", &point_num, &side_num);
	length = point_num;
	for (i = 0; i < side_num; i++)
	{
		scanf("%d %d", &begin, &end);
		side[begin][end] = 1;
		side[end][begin] = 1;
	}
	scanf("%d", &delpoint);
	dfs(0);
	putchar('\n');
	to_zero();
	bfs(0);
	putchar('\n');
	to_zero();
	for (i = 0; i < point_num; i++)
	{
		side[i][delpoint] = 0;
		side[delpoint][i] = 0;
	}
	length--;
	dfs(0);
	putchar('\n');
	to_zero();
	bfs(0);
	putchar('\n');
	return 0;
}

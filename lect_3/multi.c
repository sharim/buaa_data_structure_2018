/*
作业次数：第三次作业
文件名：multi.c
题目：多项式相乘
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
typedef struct polynomial
{
	int coefficient;
	int index;
} poly;
struct ans
{
	int coefficient;
	int index;
	struct ans *front, *next;
} ans[100], *now = NULL, *head = NULL;
poly poly_a[100], poly_b[100];
int main()
{
	int a, b, i, j, k;
	char end = ' ';
	for (a = 0; end != '\n'; a++)
		scanf("%d %d%c", &poly_a[a].coefficient, &poly_a[a].index, &end);
	end = ' ';
	for (b = 0; end != '\n'; b++)
		scanf("%d %d%c", &poly_b[b].coefficient, &poly_b[b].index, &end);
	for (i = 0; i < b; i++)
	{
		ans[i].coefficient = poly_a[0].coefficient * poly_b[i].coefficient;
		ans[i].index = poly_a[0].index + poly_b[i].index;
		if (i == 0)
		{
			ans[i].front = NULL;
			ans[i].next = &ans[i + 1];
		}
		else if (i == a - 1)
		{
			ans[i].front = &ans[i - 1];
			ans[i].next = NULL;
		}
		else
		{
			ans[i].front = &ans[i - 1];
			ans[i].next = &ans[i + 1];
		}
	}
	now = &ans[0], head = &ans[0];
	for (j = 1; j < a; j++)
	{
		for (k = 0; k < b; k++)
		{
			int count = 0;
			ans[i].coefficient = poly_a[j].coefficient * poly_b[k].coefficient;
			ans[i].index = poly_a[j].index + poly_b[k].index;
			while (now != NULL)
			{
				if (ans[i].index == now->index)
				{
					now->coefficient += ans[i].coefficient;
					now = head;
					count = 0;
					break;
				}
				else if (now->index < ans[i].index)
				{
					ans[i].front = now->front;
					ans[i].next = now;
					;
					now->front->next = &ans[i];
					now->front = &ans[i];
					i++;
					now = head;
					count = 0;
					break;
				}
				if (count == i - 1)
				{
					now->next = &ans[i];
					ans[i].front = now;
					ans[i].next = NULL;
					i++;
					now = head;
					count = 0;
					break;
				}
				count++;
				now = now->next;
			}
		}
	}
	while (head != NULL)
	{
		if (head->coefficient != 0)
			printf("%d %d ", head->coefficient, head->index);
		head = head->next;
	}
	system("pause");
	return 0;
}

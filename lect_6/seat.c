/*
作业次数：第六次作业
文件名：seat.c
题目：排座位（简）a
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct student_info
{
	int id;
	char name[30];
	int pos;
} student;
student stu[3500];
int sign[3500];
int get_num(char s[])
{
	int i, num = 0;
	num = s[0] - '0';
	for (i = 1; i < strlen(s); i++)
	{
		num = num * 10 + (s[i] - '0');
	}
	return num;
}
int cmp(const void *a, const void *b)
{
	student *p = (student *)a;
	student *q = (student *)b;
	if (p->pos != q->pos)
		return p->pos - q->pos;
	else
		return p->id - q->id;
}
int comp(const void *a, const void *b)
{
	student *p = (student *)a;
	student *q = (student *)b;
	return p->id - q->id;
}
int main()
{
	int count = 0, m, n, i, j = 0, k, max = 0;
	char in_id[9], in_pos[8];
	FILE *in = fopen("in.txt", "r");
	FILE *out = fopen("out.txt", "w");
	scanf("%d", &n);
	m = n;
	for (i = 0; i < n; i++)
	{
		fscanf(in, "%s %s %s", in_id, stu[i].name, in_pos);
		stu[i].id = get_num(in_id);
		stu[i].pos = get_num(in_pos);
	}
	qsort(stu, n, sizeof(stu[0]), cmp);
	int p = stu[n - 1].pos;
	int q = p < n ? p : n;
	for (i = 0; i < n; i++)
	{
		if (i < q)				//q为最大值
		{
			int v = 1;
			for (k = 0; k < count; k++)		//检查当前查询座位号是否为之前被替换座位号
			{
				if (sign[k] == i + 1)
				{
					v = 0;
					break;
				}
			}
			if (v)
			{
				for (; stu[j].pos <= i + 1 && j <= m; j++)		//检查是否漏排
					;
				if (stu[j - 1].pos != i + 1)
				{
					q = stu[m - 1].pos < n ? stu[m - 1].pos : n;		//更新q
					sign[count] = stu[m - 1].pos;		//将被替换座位号入sign，便于查询
					count++;
					stu[m - 1].pos = i + 1;			//更新座位号
					m--;
				}
			}
		}
		if (max < stu[i].pos)			//更新最大值
			max = stu[i].pos;
	}
	max++;
	for (i = 0; i < n; i++)
	{
		for (j = i + 1; stu[i].pos == stu[j].pos; j++)
		{
			stu[j].pos = max;
			max++;
		}
		i = j - 1;
	}
	qsort(stu, n, sizeof(stu[0]), comp);
	for (i = 0; i < n; i++)
		fprintf(out, "%d %s %d\n", stu[i].id, stu[i].name, stu[i].pos);
	return 0;
}
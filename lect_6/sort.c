/*
作业次数：第六次作业
文件名：sort.c
题目：整数排序（排序-基本题）
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int merge_count = 0;
int quick_count = 0;
int adjust(int *p, int node, int length)
{
    int j;
    int count = 0;
    int temp;
    temp = p[node];
    j = 2 * node + 1;
    while (j < length)
    {
        if (j < length - 1 && p[j] < p[j + 1])
            j++;
        count++;
        if (temp >= p[j])
            break;
        p[(j - 1) / 2] = p[j];
        j = 2 * j + 1;
    }
    p[(j - 1) / 2] = temp;
    return count;
}
int merge(int *p, int left, int right)
{
    int mid = (left + right) / 2;
    int i = left, j = mid + 1, k = 0;
    int count = 0;
    int *tmp = (int *)malloc(sizeof(int) * (right - left + 1));
    while (i <= mid && j <= right)
    {
        count++;
        if (p[i] <= p[j])
        {
            tmp[k] = p[i];
            i++;
        }
        else
        {
            tmp[k] = p[j];
            j++;
        }
        k++;
    }
    while (i <= mid)
    {
        tmp[k] = p[i];
        k++;
        i++;
    }
    while (j <= right)
    {
        tmp[k] = p[j];
        k++;
        j++;
    }
    for (i = left, k = 0; i <= right; i++, k++)
        p[i] = tmp[k];
    return count;
}
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
int Selection_sort(int *p, int length)
{
    int temp, min[2];
    int i, j;
    int count = 0;
    min[0] = *p, min[1] = 0;
    for (i = 0; i < length; i++)
    {
        count += length - (i + 1);
        for (j = i + 1; j < length; j++)
        {
            if (min[0] > p[j])
            {
                min[0] = p[j];
                min[1] = j;
            }
        }
        if (min[0] < p[i])
        {
            temp = p[i];
            p[i] = min[0];
            p[min[1]] = temp;
        }
        min[0] = p[i + 1];
        min[1] = i + 1;
    }
    return count;
}
int Bubble_sort(int *p, int length)
{
    int i, j;
    int temp;
    int count = 0;
    for (i = 0; i < length; i++)
    {
        int sign = 0;
        for (j = 1; j < length - i; j++)
        {
            count++;
            if (p[j - 1] > p[j])
            {
                sign = 1;
                temp = p[j - 1];
                p[j - 1] = p[j];
                p[j] = temp;
            }
        }
        if (!sign)
            break;
    }
    return count;
}
int Heap_sort(int *p, int length)
{
    int i;
    int temp;
    int count = 0;
    for (i = length / 2 - 1; i >= 0; i--)
        count += adjust(p, i, length);
    for (i = length - 1; i >= 0; i--)
    {
        temp = p[0];
        p[0] = p[i];
        p[i] = temp;
        count += adjust(p, 0, i);
    }
    return count;
}
void Merge_sort(int *p, int left, int right)
{
    if (left >= right)
        return;
    int mid = (left + right) / 2;
    Merge_sort(p, left, mid);
    Merge_sort(p, mid + 1, right);
    merge_count += merge(p, left, right);
}
void Quick_sort(int *p, int left, int right)
{
    if (left < right)
    {
        int i;
        int final = left;
        for (i = left + 1; i <= right; i++)
        {
            quick_count++;
            if (p[i] < p[left])
            {
                final++;
                swap(&p[final], &p[i]);
            }
        }
        swap(&p[left], &p[final]);
        Quick_sort(p, left, final - 1);
        Quick_sort(p, final + 1, right);
    }
}
int main()
{
    printf("hello");
    int total, mode, out = 0, i;
    scanf("%d %d", &total, &mode);
    int *num = (int *)malloc(sizeof(int) * total);
    for (i = 0; i < total; i++)
        scanf("%d", &num[i]);
    switch (mode)
    {
    case 1:
        out = Selection_sort(num, total);
        break;
    case 2:
        out = Bubble_sort(num, total);
        break;
    case 3:
        out = Heap_sort(num, total);
        break;
    case 4:
    {
        Merge_sort(num, 0, total - 1);
        out = merge_count;
    }
    break;
    case 5:
    {
        Quick_sort(num, 0, total - 1);
        out = quick_count;
    }
    break;
    default:
        break;
    }
    for (i = 0; i < total; i++)
        printf("%d ", num[i]);
    getchar();
    printf("\n%d", out);
    system("pause");
    return 0;
}

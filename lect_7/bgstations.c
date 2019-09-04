/*
作业次数：第七次作业
文件名：bgstations.c
题目：北京地铁乘坐线路查询
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
    int sum = 1,
        length = 1, from, to, pathsum = 0, no[500], top[500][3], p = 0, q = -1;
char FindBegin[100], FindEnd[200];
struct out
{
    int index;
    int id;
} out[100];
typedef struct path
{
    int id;
    char name[100];
    int sign;
} path;
path get[1000];
typedef struct station
{
    char name[50];
    int sign;
    int count;
    int side[10][2];
} station;
station *s;
int Cmp(const void *a, const void *b)
{
    station *p = (station *)a;
    station *q = (station *)b;
    return strcmp(p->name, q->name);
}
int Search(char *find)
{
    int left = 0, right = length - 2;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        int judge = strcmp(s[mid].name, find);
        if (judge == 0)
            return mid;
        else if (judge > 0)
            right = mid - 1;
        else
            left = mid + 1;
    }
    return -1;
}
void Insert(int index_1, int index_2)
{
    if (get[index_1].id != -1)
    {
        s[index_2].side[s[index_2].count][0] = get[index_1].id;
        s[index_2].side[s[index_2].count][1] = Search(get[index_1].name);
        s[index_2].count++;
    }
}
void Back(int point)
{
    if (point == from)
        return;
    int i;
    for (i = 0; i < p; i++)
    {
        if (top[i][1] == point)
        {
            out[pathsum].id = top[i][0];
            out[pathsum].index = point;
            pathsum++;
            if (top[i][2] != from)
                Back(top[i][2]);
            break;
        }
    }
}
void MinBfs(int on)
{
    int i;
    no[on] = 1;
    for (i = 0; i < s[on].count; i++)
    {
        if (no[s[on].side[i][1]] != 1)
        {
            top[p][0] = s[on].side[i][0];
            top[p][1] = s[on].side[i][1];
            top[p][2] = on;
            p++;
        }
        if (s[on].side[i][1] == to)
        {
            out[pathsum].id = s[on].side[i][0];
            out[pathsum].index = s[on].side[i][1];
            pathsum++;
            Back(on);
            return;
        }
    }
    for (i = 0; i < s[on].count; i++)
        no[s[on].side[i][1]] = 1;
    q++;
    MinBfs((top[q][1]));
}
void Write()
{
    int i, j = 0;
    printf("%s", s[from].name);
    for (i = pathsum - 1; i >= 0; i--)
    {
        if (i == pathsum - 1)
        {
            j++;
            continue;
        }
        else
        {
            if (out[i].id != out[i + 1].id)
            {
                printf("-%d(%d)-%s", out[i + 1].id, j, s[out[i + 1].index].name);
                j = 1;
            }
            else
            {
                j++;
            }
        }
    }
    printf("-%d(%d)-%s\n", out[i + 1].id, j, s[out[i + 1].index].name);
}
int main()
{
    int i, sign = 0, flag = 0;
    int LineNum, LineId, StationNum;
    get[0].id = -1;
    FILE *in = fopen("bgstations.txt", "r");
    FILE *out = fopen("out.txt", "w");
    fscanf(in, "%d", &LineNum);
    fprintf(out, "%d\n", LineNum);      //output
    while (!feof(in))
    {
        fscanf(in, "%d %d", &LineId, &StationNum);
        fprintf(out, "%d %d\n", LineId, StationNum);        //output
        for (i = sum; i < sum + StationNum; i++)
        {
            get[i].id = LineId;
            fscanf(in, "%s %d", get[i].name, &get[i].sign);
            fprintf(out, "%s %d\n", get[i].name, get[i].sign);  //output
            if (flag == 0)
            {
                s = (station *)malloc(sizeof(station) * length);
                s[length - 1].sign = get[i].sign;
                strcpy(s[length - 1].name, get[i].name);
                s[length - 1].count = 0;
                length++;
                flag = 1;
            }
            else if (sign == 0)
            {
                s = (station *)realloc(s, sizeof(station) * length);
                s[length - 1].sign = get[i].sign;
                strcpy(s[length - 1].name, get[i].name);
                s[length - 1].count = 0;
                length++;
            }
            else
            {
                int j;
                for (j = 0; j < length - 1; j++)
                    if (strcmp(s[j].name, get[i].name) == 0)
                        break;
                if (j == length - 1)
                {
                    s = (station *)realloc(s, sizeof(station) * length);
                    s[length - 1].sign = get[i].sign;
                    strcpy(s[length - 1].name, get[i].name);
                    s[length - 1].count = 0;
                    length++;
                }
            }
        }
        fprintf(out, "\n");
        sign = 1;
        get[i].id = -1;
        sum += StationNum + 1;
    }
    qsort(s, length - 1, sizeof(station), Cmp);
    for (i = 0; i < sum; i++)
    {
        if (get[i].id == -1)
            continue;
        int index = Search(get[i].name);
        Insert(i - 1, index);
        Insert(i + 1, index);
    }
    scanf("%s%s", FindBegin, FindEnd);
    from = Search(FindBegin);
    to = Search(FindEnd);
    if (from == to)
    {
        printf("%s--%d(0)--%s\n", s[from].name, s[from].side[0][0], s[from].name);
        return 0;
    }
    if (from == -1 || to == -1)
        return 0;
    MinBfs(from);
    Write();
    system("pause");
    return 0;
}

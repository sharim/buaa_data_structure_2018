/*
作业次数：第二次
文件名：replace.c
题目：字符串替换（新）
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char in[1000], tmp[1000], a[30], b[30], c[30];

void lower(char line[])
{
    int i;
    for (i = 0; i < strlen(line); i++)
        if (line[i] >= 'A' && line[i] <= 'Z')
            line[i] = line[i] + 'a' - 'A';
}

int main()
{
    int j;
    scanf("%s %s", a, b);
    strcpy(c, b);
    lower(a);
    lower(b);
    FILE *fp_in = fopen("filein.txt", "r");
    FILE *fp_out = fopen("fileout.txt", "w");
    fread(in, sizeof(char), 1000, fp_in);
    strcpy(tmp, in);
    lower(in);
    for (j = 0; j < strlen(in); j++)
    {

        if ((strstr(&in[j], a) - (&in[j])) == 0)
        {
            fwrite(c, sizeof(char), strlen(c), fp_out);
            j += (strlen(a) - 1);
            continue;
        }
        else
            fwrite(&tmp[j], sizeof(char), 1, fp_out);
    }
    fclose(fp_in);
    fclose(fp_out);
    system("pause");
    return 0;
}

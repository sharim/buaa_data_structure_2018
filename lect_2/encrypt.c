/*
作业次数：第二次
文件名：encrypt.c
题目：加密文件
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char tmp[50],word[50],key[26],txt[1000];

int main()
{
    int i,j;
    FILE *in=fopen("encrypt.txt","r");
    FILE *out=fopen("output.txt","w");
    fread(txt,sizeof(char),1000,in);
    scanf("%s",tmp);
    for(i=0;i<strlen(tmp)-1;i++)
    {
        for(j=i+1;j<strlen(tmp);j++)
            if(tmp[j]==tmp[i])
                tmp[j]='0';
    }
    for(i=0,j=0;i<strlen(tmp);i++)
    {
        if(tmp[i]!='0')
        {
            word[j]=tmp[i];
            j++;
        }
    }
    int count=0;
    for(i=strlen(word);i<26;i++)
    {
        int j;
        for(j=0;j<strlen(word);j++)
        {
            if(word[j]=='z'-count)
            {
                count++;
                j=-1;
            }
        }
        word[i]='z'-count;
    }
    strncpy(key,word,26);
    int jump=0;
    for(i=0;i<strlen(txt);i++)
    {
        if(txt[i]<'a' || txt[i]>'z')
        {
            jump++;
            continue;
        }
        txt[i]=key[txt[i]-'a'];
    }
    fwrite(txt,sizeof(char),1000,out);
    fclose(in);
    fclose(out);
    system("pause");
    return 0;
}

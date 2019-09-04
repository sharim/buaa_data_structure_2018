/*
作业次数：第二次
文件名：chess.c
题目：五子棋危险判断
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int i,j,chess[21][21];

int main()
{
    for(i=1;i<=19;i++)
    {
        chess[i][0]=-1;
        chess[i][20]=-1;
        for(j=1;j<=19;j++)
        {
            chess[0][j]=-1;
            chess[20][j]=-1;
            scanf("%d",&chess[i][j]);
        }
    }
    for(i=1;i<=19;i++)
        for(j=1;j<=19;j++)
        {
            if(j<=16)
            {
                if(chess[i][j]!=0 && chess[i][j]==chess[i][j+1] && chess[i][j]==chess[i][j+2] && chess[i][j]==chess[i][j+3])
                    if(chess[i][j-1]==0 || chess[i][j+4]==0)
                    {
                        printf("%d:%d,%d",chess[i][j],i,j);
                        system("pause");
                        return 0;
                    }
            }
            if(i<=16 && j<=16)
                if(chess[i][j]!=0 && chess[i][j]==chess[i+1][j+1] && chess[i][j]==chess[i+2][j+2] && chess[i][j]==chess[i+3][j+3])
                    if(chess[i-1][j-1]==0 || chess[i+4][j+4]==0)
                    {
                        printf("%d:%d,%d",chess[i][j],i,j);
                        system("pause");
                        return 0;
                    }
            if(i<=16 && j>=4)
                if(chess[i][j]!=0 && chess[i][j]==chess[i+1][j-1] && chess[i][j]==chess[i+2][j-2] && chess[i][j]==chess[i+3][j-3])
                    if(chess[i-1][j+1]==0 || chess[i+4][j-4]==0)
                    {
                        printf("%d:%d,%d",chess[i][j],i,j);
                        system("pause");
                        return 0;
                    }
        }
    for(j=1;j<=19;j++)
        for(i=1;i<=16;i++)
        {
            if(chess[i][j]!=0 && chess[i][j]==chess[i+1][j] && chess[i][j]==chess[i+2][j] && chess[i][j]==chess[i+3][j])
                if(chess[i-1][j]==0 || chess[i+4][j]==0)
                {
                    printf("%d:%d,%d",chess[i][j],i,j);
                    system("pause");
                    return 0;
                }
        }
    printf("NO");
    system("pause");
    return 0;
}

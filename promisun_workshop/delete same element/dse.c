/*消除类游戏是一种益智游戏，其核心规则是将一定的彼此相邻的相同元素配对消除。现给定一个n行m列的棋盘，棋盘中的每一个方格上放着一个棋子，每个棋子都有颜色，编号用1~9表示。当一行或一列上有连续3个或3个以上同色棋子时，这些棋子都被同时消除，对应的方格用0表示，请输出经过消除后的棋盘。例如，给定棋盘为：
4 4 3 1 4
3 1 1 1 1
4 3 4 1 2
4 4 2 2 2
消除后为：
4 4 3 0 4
3 0 0 0 0
4 3 4 0 2
4 4 0 0 0

示例
输入（输入的前两个数字为棋盘的行数和列数）：
4 5
4 4 3 1 4
3 1 1 1 1
4 3 4 1 2
4 4 2 2 2
输出（同行每个元素之间以空格分隔）：
4 4 3 0 4
3 0 0 0 0
4 3 4 0 2
4 4 0 0 0   */


//以下方法较蠢，会浪费部分时间，没能做到不重复记录，因而在交叉消除处会归零至少两次
//且在分配空间时没能做到按需分配，主要是针对二维数组的传递问题（类之前的maze），a[][n],n根据需求而定而非常量，故传参出现小插曲
#include <stdio.h>
int row,col;
int rpos=0,cpos=0;  //记录pos位置
int pos[50][2];  //记录可消除的位置


void delete(int chess[][10]);
void deleteRow(int chess[][10]);
void deleteCol(int chess[][10]);

int main()
{
    scanf("%d %d",&row,&col);
    int chess[row][10];
    //输入
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++) scanf("%d",&chess[i][j]);
    }
    //消除
    delete(chess);
    //输出
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++) 
        {
            printf("%d",chess[i][j]);
            if(j<col-1) printf(" ");
        }
        if(i<row-1) printf("\n");
    }
}

void delete(int chess[][10])
{
    deleteRow(chess);
    deleteCol(chess);
    for(int i=0;i<rpos;i++)
    {
        chess[pos[i][0]][pos[i][1]]=0;
        chess[pos[i][0]][pos[i][1]+1]=0;
        chess[pos[i][0]][pos[i][1]+2]=0;
    }
    for(int j=rpos;j<cpos;j++)
    {
        chess[pos[j][0]][pos[j][1]]=0;
        chess[pos[j][0]+1][pos[j][1]]=0;
        chess[pos[j][0]+2][pos[j][1]]=0;
    }
}

void deleteRow(int chess[][10])//按理说应该是标记而非删除，deleteCol同理
{
    for(int r=0;r<row;r++)
    {
        for(int i=0;i<col-2;i++)
        {
            if(chess[r][i]==chess[r][i+1]&&chess[r][i]==chess[r][i+2]) 
            {
                pos[rpos][0]=r;
                pos[rpos][1]=i;
                rpos++;
            }
        }
    }
    cpos=rpos;
}

void deleteCol(int chess[][10])
{
    for(int c=0;c<col;c++)
    {
        for(int i=0;i<row-2;i++)
        {
            if(chess[i][c]==chess[i+1][c]&&chess[i][c]==chess[i+2][c]) 
            {
                pos[cpos][0]=i;
                pos[cpos][1]=c;
                cpos++;
            }
        }
    }
}

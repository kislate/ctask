#include <stdio.h>
int row,col;//迷宫大小 
int count=0;
int pos[100][2];//记录当前位置xy
int victor[4][2]={{-1,0},{1,0},{0,-1},{0,1}}; //上下左右
 
 
int isOk(int x,int y,int mg[][15]) 
{
    if(x>=0&&x<row&&y>=0&&y<col&&(mg[x][y]==1)) return 1;
    else return 0;
}

void printPath(int mg[][15],int row,int col)
{
    printf("%d\n",++count);
    
    for(int m=0;m<row;m++)
    {
        for(int n=0;n<col;n++) 
        {
            if(mg[m][n]==2)
            {
                printf ("1");
                if(n!=col-1) 
                    printf(" ");
            }
            else 
            {
                printf("0");
                if(n!=col-1) 
                    printf(" ");
            }
        }
        if(m!=row-1) 
            putchar(10);
    }//修改了一下输出格式
}
//第i次move 
void move(int i,int mg[][15])
{
    if((pos[i][0]==row-1)&&(pos[i][1]==col-1))
    {
        mg[pos[i][0]][pos[i][1]] = 2;//终点的点没有打印出来；
        printPath(mg,row,col);
        mg[pos[i][0]][pos[i][1]] = 1;//回溯，把原来的点还原
        return;
    }
    else
    {
        for(int j=0;j<4;j++)
    {
        if(isOk(pos[i][0]+victor[j][0],pos[i][1]+victor[j][1],mg))
        {
            pos[i+1][0]=pos[i][0]+victor[j][0];
            pos[i+1][1]=pos[i][1]+victor[j][1];
            mg[pos[i][0]][pos[i][1]]=2;
            move(i+1,mg);
        }
        mg[pos[i][0]][pos[i][1]]=1;//回溯，把原来的点还原
    }
    }
    mg[pos[i][0]][pos[i][1]]=1;//回溯，把原来的点还原（理论上这个可以删）
    return;
}

int main()
{
    scanf("%d %d",&row,&col);
    int mg[row][15];
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++) scanf("%d",&mg[i][j]);
    }
    move(0,mg);
}
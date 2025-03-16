//22.走
// 【题目描述】
// 在一个 m × m 的棋盘上，每个方格可能是红色、黄色或无色。任务是从最左上角
// 移动到最右下角。在任何时刻，所站的位置必须是有颜色的，只能向上、下、左、右四
// 个方向移动。当从一个格子移动到另一个格子时，如果两个格子的颜色相同，则无需支
// 付金币；如果颜色不同，则需要支付 1 个金币。
// 此外，可以花费 2 个金币使用魔法，将下一个无色格子短暂变为指定颜色。魔法不
// 能连续使用，且持续时间有限。一旦使用了魔法，当走到这个暂时有颜色的格子上时不
// 能再次使用魔法；只有在离开这个位置，走到原本有颜色的格子上时才能再次使用魔法。
// 当离开位置时（通过施展魔法使其变为有颜色的格子），该格子恢复为无色。
// 现在的问题是，从最左上角移动到最右下角，要求达成的最少金币花费是多少？
// 【输入格式】
// 第一行包含两个正整数 $ m, n$，以一个空格分开，分别代表棋盘的大小，棋盘上
// 有颜色的格子的数量。
// 接下来的 $ n $ 行，每行三个正整数 $ x, y, c$，分别表示坐标为 (x, y) 的格子有颜
// 色 $ c$。
// 其中 $ c=1$ 代表黄色，$ c=0$ 代表红色。棋盘左上角的坐标为 (1, 1)，右下角的坐
// 标为 (m, m)。
// 棋盘上其余的格子都是无色。保证棋盘的左上角一定是有颜色的。
// 【输出格式】
// 一个整数，表示花费的金币的最小值，如果无法到达，输出 −1。
// 【样例 1 输入】
// 1 5 7
// 2 1 1 0
// 3 1 2 0
// 4 2 2 1
// 5 3 3 1
// 6 3 4 0
// 7 4 4 1
// 8 5 5 0
// 【样例 1 输出】
// 1 8
// 【样例 2 输入】
// 1 5 5
// 2 1 1 0
// 3 1 2 0
// 4 2 2 1
// 5 3 3 1
// 6 5 5 0
// 【样例 2 输出】
// 1 ‐1
// 【子任务】
// 对于 30% 的数据，1 ≤ m ≤ 5，1 ≤ n ≤ 10。
// 对于 60% 的数据，1 ≤ m ≤ 20，1 ≤ n ≤ 200。
// 对于 100% 的数据，1 ≤ m ≤ 100，1 ≤ n ≤ 1000。
// 【提示】
// 题目中说，只能朝四个方向走。可否对使用金币变化颜色的规则做一些拓展，让主
// 角可以往十二个方向走，同时去部分关于颜色的规则呢？
// 方向太多，若逐个回溯是否代码太长？请查找资料并学习搜索中的增. 量. 数. 组. 。
#include<stdio.h>
#include<stdlib.h>

int use=1,flag=0;//use用来判断是否能使用魔法,flag用来回魔；
int count=20000,temp=0;//金币花费
int x=0,y=0;//记录当前位置xy

int v[4][2]={{0,1},{0,-1},{1,0},{-1,0}};//四个方向
//判断是否可以走
int isOK(int use,int x,int y,int m,int **chess)
{
    if(x>=0&&x<m&&y>=0&&y<m&&(chess[x][y]!=-1||use==1)) return 1;
    else return 0;
}

//走
void move(int **chess,int x,int y,int m)
{
    if(x==m-1&&y==m-1)
    {
        if(temp<count)
            count=temp;
        return;
    }
    else
    {
        for(int i=0;i<4;i++)
        {
            if(isOK(use,x+v[i][0],y+v[i][1],m,chess))
            {
                if(chess[x+v[i][0]][y+v[i][1]]==-1)//用魔法（加上前置isOK判断，此时use=1；）
                {
                    temp+=2;
                    use=0;
                    chess[x+v[i][0]][y+v[i][1]]=chess[x][y];
                }
                else if(chess[x+v[i][0]][y+v[i][1]]!=chess[x][y])//不同颜色
                    temp++;
                if(!use) flag++;
                if(flag==2 )//魔法恢复
                {
                    use=1;
                    flag=0;
                }
                int t=chess[x][y];
                chess[x][y]=-1;//尽量防止回头
                move(chess,x+v[i][0],y+v[i][1],m);
                //回溯
                chess[x][y]=t;
                if(chess[x+v[i][0]][y+v[i][1]]==-1)
                {
                    temp-=2;
                    use=1;
                    chess[x+v[i][0]][y+v[i][1]]=-1;
                }
                else if(chess[x+v[i][0]][y+v[i][1]]!=chess[x][y])
                    temp--;
            }
            else if(i==3)
                return;
        }
    }
}

int main()
{
	int m,n;
	scanf("%d %d",&m,&n);
	int **chess=(int**)malloc(sizeof(int*)*m);
        for(int i=0;i<m;i++)
            chess[i]=(int*)malloc(sizeof(int)*m); 
    //初始化棋盘
	for(int i=0;i<m;i++)
        for(int j=0;j<m;j++)
            chess[i][j]=-1;
    //读入有颜色的格子
    for(int i=0;i<n;i++)
    {
        int x,y,c;
        scanf("%d %d %d",&x,&y,&c);
        chess[x-1][y-1]=c;
    }
    //开走
    move(chess,0,0,m);
    if(count==20000)
        printf("-1");
    else
        printf("%d",count);

    //free
    for(int i=0;i<m;i++)
        free(chess[i]);
    free(chess);
	return 0; 
} 
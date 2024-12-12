/*Problem 4: 教室分配 I
 Input file:
 Output file:
 Time limit:
 standard input
 standard output
 1 seconds
 Memory limit: 512 megabytes
 Problem Description
华中科技大学的教学楼方方正正，教室的布局也是如此。
现有n×m个教室排布成一个n行m列的矩形，你需要为这些教室分配编号，满足对于
任意两个上下相邻或左右相邻的教室，它们的编号之和在所有的和中仅出现过一次。
现在给定你n和m，请问能否构造出上述矩阵？如果能，请输出任意一种可行方案。
Input
每个测试点包含多组测试数据，第一行包含测试数据的组数T(1≤T ≤10)。
每组测试数据仅一行，包含两个整数n,m(1≤n,m≤1000)
 Output
对于每组数据，在第一行输出是否有可行方案，如果有，输出Yes，否则输出No。
如果存在可行方案，你还需要输出n行，每行m个整数，第i行的第j 个数表示矩阵的第i
行第j 列上的数字。你需要保证输出的数字都在1 n×m之间且没有重复。
可行的方案可能有多种，只输出一种即可。
Examples
 Standard Input
 3
 Standard Output
 Yes
 1 1
 2 3
 2 2
 1
 Yes
 1 2
 3 4
 Yes
 1 3 2
 6 5 4
 Scoring
对于10%的测试数据，保证：n=1；
对于另外10%的数据，保证：n=2；
对于另外20%的数据，保证：T =1,n×m≤36；
对于另外30%的数据，保证：n和m至少有一个是偶数；
对于100% 的测试数据，保证：1≤T ≤10,1≤n,m≤1000；*/
#include<stdio.h>
int isYes(int n,int m,int sum,int Mark[],int matrix[][1000],int x,int y);
int main(void)
{
    int T=0;
    scanf("%d",&T);
    for(int i=0;i<T;i++)
    {
        int r,c;
        int Mark[1000000]={0};
        scanf("%d %d",&r,&c);
    }
}
int isYes(int n,int m,int sum,int Mark[],int matrix[][1000],int x,int y)
{
    if(sum==0)
    {
        if(Mark[matrix[x][y]+matrix[x-1][y]]!=0||Mark[matrix[x][y]+matrix[x][y-1]]!=0)
        {
            matrix[x][y]=0;
            return 0;
        }
        else{
            return 1;
        }
    }
    for(int i=1;i<=n*m;i++);
    {
        
    }
}
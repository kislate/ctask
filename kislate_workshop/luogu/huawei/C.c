/*Problem 3: 矩形旋转
Input file:
 Output file:
 Time limit:
 standard input
 standard output
 1 seconds
 Memory limit: 512 megabytes
 Problem Description
给定N 行N列的矩阵A，第i行第j列的数为Ai,j，保证Ai,j∈{0,1}。
将矩阵最外层顺时针旋转一个数，输出旋转后的矩阵。
最外层指第1行、第N 行、第1列、第N 列。
Input
第一行一个整数N。
接下来N 行每行N 个整数，表示矩阵。
Output
输出N 行，每行N 个整数，表示旋转后的矩阵。
Examples
 Standard Input
 4
 Standard Output
 1010
 0101
 1101
 1111
 0000
 2
 1101
 0111
 0001
 11
 11
 11
 11
 Scoring
对于100% 的数据，2≤N ≤100，Ai,j ∈{0,1}*/

#include<stdio.h>
int main(void)
{
    int matrix[100][100];
    int markMatrix[100][100];
    int n,a,b,c,d;
    scanf("%d",&n);
    for(int r=0;r<n;r++)
    {
        for(int c=0;c<n;c++)
        {
            scanf("%d",&markMatrix[r][c]);
        }
    }
    a=markMatrix[0][0];
    b=markMatrix[0][n-1];
    c=markMatrix[n-1][0];
    d=markMatrix[n-1][n-1];
    for(int i=n-1;i>2;i++)
    {
        markMatrix[0][i]=markMatrix[0][i-1];
    }
    for(int i=n-1;i>2;i++)
    {
        markMatrix[i][n-1]=markMatrix[i-1][n-1];
    }
    for(int i=0;i<n-1;i++)
    {
        markMatrix[n-1][i]=markMatrix[n-1][i+1];
    }   
    for(int i=0;i<n-1;i++)
    {
        markMatrix[i][0]=markMatrix[i+1][0];
    }
    markMatrix[0][1]=a;
    markMatrix[1][n-1]=b;
    markMatrix[n-1][n-2]=c;
    markMatrix[n-2][0]=d;
    for(int r=0;r<n;r++)
    {
        for(int c=0;c<n;c++)
        {
            printf("%d",markMatrix[r][c]);
        }
        printf("\n");
    }
    return 0;
}
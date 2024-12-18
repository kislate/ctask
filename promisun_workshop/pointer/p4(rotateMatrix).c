// 输入图像矩阵的行数n和列数m，接下来的n行每行输入m个整数，表示输入的图像，输出原始矩阵逆时针旋转90°后的矩阵。

// 输入输出示例
// 输入：
// 2 3
// 1 5 3
// 3 2 4

// 输出：
// 3 4
// 5 2
// 1 3
#include<stdio.h>
#include <stdlib.h>
int row,col;
void RotateMartix(int **s,int **t);

int main()
{
    scanf("%d %d",&row,&col);
    
    //分配空间
    int **Martix = (int **)malloc(row * sizeof(int *));
    int **Rmartix = (int **)malloc(col * sizeof(int *));
    for (int i = 0; i < row; ++i) {
        Martix[i] = (int *)malloc(col * sizeof(int));
        // 初始化数组
        for (int j = 0; j < col; ++j) {
            scanf("%d",&Martix[i][j]) ;
        }
    }
    for (int i = 0; i < col; ++i) {
        Rmartix[i] = (int *)malloc(row * sizeof(int));
    }
    

    RotateMartix(Rmartix,Martix);
    

  //输出  
    for(int i=0;i<col;i++)
    {
        for(int j=0;j<row;j++) 
        {
            printf("%d",Rmartix[i][j]);
            if(j<(row-1))printf(" ");
        }
        if(i<col-1) printf("\n");
    }
    
    //释放
    for (int i = 0; i < row; ++i) {
        free(Martix[i]);
    }
    for (int i = 0; i < col; ++i) {
        free(Rmartix[i]);
    }
    free(Rmartix);
    free(Martix);
}


void RotateMartix(int **s,int **t)
{
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            s[col-j-1][i]=t[i][j]; //转后列即原来的行
        }
    }
}

 //为了给函数传**s,**t写了很多给指针指向处分配空间并释放，使代码有点长，其实用数组就可解决
 //算是熟悉给二级指针分配空间的过程了
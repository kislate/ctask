/*
任务描述
本关任务：编写一个矩阵加法。

相关知识
为了完成本关任务，你需要掌握：1.数组的压缩存储，2.稀疏矩阵。
在后台测试程序中，已经定义了如下稀疏矩阵三元组顺序表类型。
#define  MAXSIZE 10000
typedef struct  {
   int       i,j;//非零元行、列下标
   ElemType    e;
 } Triple;        //三元组定义

typedef struct  {
   Triple  data[MAXSIZE+1];   //三元组从下标1开始存放
   int  mu,nu,tu;         //对于矩阵的行数、列数和非零元素值
 } TSMatrix;              //三元组顺序表的定义

编程要求
根据提示，在右侧编辑器补充代码，完成函数ADD的编写。
函数原型：TSMatrix ADD(TSMatrix A,TSMatrix B);

测试说明
平台会对你编写的代码进行测试,首先依次输入2个矩阵的行列数以及非零元素个数，接着输入相应的三元组，输出运算结果。

测试输入：6 7 5
       1 1 5  1 2 10  3 1 2  5 7 6  6 6 6
       6 7 4
       1 1 -5  2 2 13  3 1 20  5 7 2  
预期输出： 6 7 5
          1 2 10  2 2 13  3 1 22  5 7 8  6 6 6  
*/
#include "stdio.h"
#define  MAXSIZE 10000
typedef int ElemType;
typedef struct  {
   int       i,j;//非零元行、列下标
   ElemType    e;
 } Triple;        //三元组定义

typedef struct  {
   Triple  data[MAXSIZE+1];   //三元组从下标1开始存放
   int  mu,nu,tu;         //对于矩阵的行数、列数和非零元素值
 } TSMatrix;              //三元组顺序表的定义
TSMatrix ADD(TSMatrix A,TSMatrix B)
//返回矩阵A、B相加的结果
{
/************** begin *****************/
ElemType Temp[10][10] = {0};
TSMatrix C;
C.mu = A.mu, C.nu = A.nu, C.tu = A.tu;
for(int i = 1; i <= A.tu; i++) Temp[A.data[i].i][A.data[i].j] += A.data[i].e;
for(int i = 1; i <= B.tu; i++) Temp[B.data[i].i][B.data[i].j] += B.data[i].e;
int cnt = 0;
for(int i = 0; i < 10; i++)
    for(int j = 0; j < 10; j++)
    {
        if(Temp[i][j] != 0)
        {
            C.data[++cnt].e = Temp[i][j];
            C.data[cnt].i = i;
            C.data[cnt].j = j;
        }
    }
C.tu = cnt;
return C;
/**************  end  *****************/
}
int main()
{
	TSMatrix A[3],B,C;
   int i,j;
   for(i=0;i<2;i++)
   {
   		scanf("%d%d%d",&A[i].mu,&A[i].nu,&A[i].tu);
   		for(j=1;j<=A[i].tu;j++)
   		 	scanf("%d%d%d",&A[i].data[j].i,&A[i].data[j].j,&A[i].data[j].e);
   }
   A[2]=ADD(A[0],A[1]);
   printf("%d %d %d\n",A[2].mu,A[2].nu,A[2].tu);
   for(i=1;i<=A[2].tu;i++)
   		printf("%d %d %d     ",A[2].data[i].i,A[2].data[i].j,A[2].data[i].e);
	return 1;
}
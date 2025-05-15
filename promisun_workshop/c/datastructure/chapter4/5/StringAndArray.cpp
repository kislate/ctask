// 本关任务：编写一个算法，将数组A中的n个元素A[0]至A[n-1]循环右移k位。要求算法时间复杂度为O（n），空间复杂度为O（1）

// 相关知识
// 为了完成本关任务，你需要掌握：1.一维数组，2.数组的遍历。

// 编程要求
// 根据提示，在右侧编辑器填写算法函数，实现将大小为n的数据元素数组a中的元素循环右移k位。要求函数原型为：
// void ShiftRightCircular(ElemType a[],int n,int k)
// 其中k的值可为负整数，表示循环左移；ElemType已经在后台测试程序中定义。

// 测试说明
// 平台会自动读取输入数据，对你编写的代码进行测试，并输出结果。

// 测试输入：10，5；（输入的是n与k的值）
// 预期输出：
//  6 7 8 9 10 1 2 3 4 5

// 测试输入：10，-3；
// 预期输出：
//  4 5 6 7 8 9 10 1 2 3
#include<stdio.h>
#include<stdlib.h>
typedef int ElemType;

void ShiftRightCircular(ElemType *A,int n,int k)
{
/************** begin *****************/
    while(k<0) k=n+k; 
    while(k>n) k=k-n;
    if(k==0) return;
    int temp=0,j=0;
    for(int i=k;i<n;i++)
    {
        temp=A[i];
        A[i]=A[j];
        A[j++]=temp;
        if(j>=(k)) j=0;
    }
    ShiftRightCircular(A,k,-j);
/**************  end  *****************/
}
int main()
{
    int n,i,k;
    ElemType *p;
    scanf("%d%d",&n,&k);
    p=(int *)malloc(n*sizeof(int));
    for(i=0;i<n;i++)
        p[i]=i+1;
    ShiftRightCircular(p,n,k);
    for(i=0;i<n;i++)
        printf(" %d",p[i]);
    return 1;
}



// 本关任务：编写一个矩阵加法。

// 相关知识
// 为了完成本关任务，你需要掌握：1.数组的压缩存储，2.稀疏矩阵。
// 在后台测试程序中，已经定义了如下稀疏矩阵三元组顺序表类型。
// #define  MAXSIZE 10000
// typedef struct  {
//    int       i,j;//非零元行、列下标
//    ElemType    e;
//  } Triple;        //三元组定义

// typedef struct  {
//    Triple  data[MAXSIZE+1];   //三元组从下标1开始存放
//    int  mu,nu,tu;         //对于矩阵的行数、列数和非零元素值
//  } TSMatrix;              //三元组顺序表的定义

// 编程要求
// 根据提示，在右侧编辑器补充代码，完成函数ADD的编写。
// 函数原型：TSMatrix ADD(TSMatrix A,TSMatrix B);

// 测试说明
// 平台会对你编写的代码进行测试,首先依次输入2个矩阵的行列数以及非零元素个数，接着输入相应的三元组，输出运算结果。

// 测试输入：6 7 5
//        1 1 5  1 2 10  3 1 2  5 7 6  6 6 6
//        6 7 4
//        1 1 -5  2 2 13  3 1 20  5 7 2  

// 预期输出： 6 7 5
//           1 2 10  2 2 13  3 1 20  5 7 8  6 6 6  
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
    TSMatrix C;
    int m=1,n=1;
    C.mu=A.mu;C.nu=A.nu;C.tu=0;
    while(m<=A.tu && n<=B.tu)
    {
        if(A.data[m].i==B.data[n].i && A.data[m].j==B.data[n].j)
        {
            if(A.data[m].e+B.data[n].e!=0){
                C.data[++C.tu].i=A.data[m].i;
                C.data[C.tu].j=A.data[m].j;
                C.data[C.tu].e=A.data[m].e+B.data[n].e;
            }
            m++;n++;
        }
        else if(A.data[m].i<B.data[n].i || (A.data[m].i==B.data[n].i && A.data[m].j<B.data[n].j))
        {
            C.data[++C.tu]=A.data[m++];
        }
        else
        {
            C.data[++C.tu]=B.data[n++];
        }
    }
    while(m<=A.tu) C.data[++C.tu]=A.data[m++];
    while(n<=B.tu) C.data[++C.tu]=B.data[n++];  
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


// 本关任务：编写一个实现字符串的替换操作Replace（&S,T,V）。

// 相关知识
// 为了完成本关任务，你需要掌握：
// 1.字符串以及字符串的基本操作;
// 2.字符串的堆分配存储结构，其数据类型定义：
// typedef struct {
//     char *ch;
//    int length;
// } HString;
// 3. Replace（&S,T,V）的语义：用V替换主串S中出现的所有与T相等的不重叠的子串。假定：S的串值为：`abc aaaaa 123`, T的串值为：`aa`, V的串值为：`#`，
// 则执行操作Replace（&S,T,V）后，S的串值为：`abc ##a 123`。

// 编程要求
// 根据提示，在右侧编辑器补充代码，完成Replace（&S,T,V）。

// 测试说明
// 平台会自动读取输入数据，对你编写的代码进行测试，并输出结果。

// 测试输入：abc aaaaa 123
//        aa
//        #
// 预期输出：S的长度：11
//        abc ##a 123

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
typedef struct {
	char *ch;
   int length;
} HString;

void Replace(HString &S,HString T,HString V)
//
{
/************** begin *****************/
    int i,j,k,s=0,count=0;//s控制指向修改后位置，i控制指向原串位置,count控制替换次数
    int len=T.length-V.length;
    char *p=S.ch,*q=T.ch,*r=V.ch;
    if(len>=0)
    {
        for(i=0;i<S.length;)
        {
        if(memcmp(p+i,q,T.length)==0)//替换
        {
                for(j=s,k=0;k<V.length;k++)
                    *(p+j+k)=*(r+k);
                s+=V.length;
                i+=T.length;
                count ++;
        }
        else{
                s++;
                i++;
        }
        }
        *(p+s)='\0';//结束符
        S.length=S.length-count*len;
    }
    else { // 无需 s 了
        for (i=0;i<S.length;i++) {
            if (memcmp(p+i,q,T.length) == 0) { // 替换
                // 将后续字符后移，为插入 V 腾出空间
                for (k=S.length;k>=i+T.length;k--) {
                    *(p+k+V.length-T.length) =*(p+k);
                }
                // 插入 V 
                for (j=0;j<V.length;j++) {
                    *(p+i+j)=*(r+j);
                }
                i+=V.length-1; // 跳过已替换的部分
                S.length+=V.length-T.length; // 更新长度
            }
        }
        *(p+S.length)='\0'; // 结束符
    }
/**************  end  *****************/
}

int main()
{
HString S[3];
char buf[100],i,j;
for(i=0;i<3;i++)
{
	fgets(buf,100,stdin);
	S[i].length=strlen(buf)-1;  //-1是去掉回车符号
	S[i].ch=(char *)malloc(S[i].length);
	for(j=0;j<S[i].length; j++)
		S[i].ch[j]=*(buf+j);
}
Replace(S[0],S[1],S[2]);
printf("S的长度：%d\n",S[0].length);
for(i=0;i<S[0].length;i++)
	putchar(S[0].ch[i]);
return 1;

}

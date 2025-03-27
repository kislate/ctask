/*
任务描述
本关任务：已知A、B和C为3个递增有序的线性表，现要求对A表做如下操作，删除那些既在B中出现，也在C中出现的元素。以顺序表作为线性表的物理结构，编写实现上述操作的算法。
函数原型：void  TriSqList(SqList  &A,SqList  B,SqList  C)；

相关知识
为了完成本关任务，你需要掌握：1.线性表，2.顺序表。
相关定义：
typedef int ElemType;
typedef struct
   { 
        ElemType *elem;
        int length;
        int listsize;
    } SqList;

编程要求
根据提示，在右侧编辑器补充代码，完成函数TriSqList(SqList  &A,SqList  B,SqList  C)。
要求算法效率尽可能高。

测试说明
平台会自动读取输入三个线性表的数据，对你编写的代码进行测试，并输出结果。

测试输入：1  3  5  7  9  10  11  12  20  0
                 3  9  10  11  30 0
                 3  6  7  9 11  13  50  0
预期输出：1  5  7  10  12  20

开始你的任务吧，祝你成功！
*/
#include<stdio.h>
#include<stdlib.h>
#define LIST_INIT_SIZE 5000
#define LISTINCREMENT 10
typedef int ElemType;
typedef struct
{ 
    ElemType *elem;
    int length;
    int listsize;
} SqList;
void  TriSqList(SqList  &A,SqList  B,SqList  C)
{
/**********Begin**********/
// 代码已经知道A、B、C是递增有序的，所以可以直接比较
int flag_1 = 3, flag_2 = 3; // 存储了B, C 对于A的三种状态, 0: 小于, 1: 等于, 2: 大于, 3表示已经到达末尾,或未比较
int i =0 , j = 0, k = 0;
while(i < A.length)
{
    
}
/**********End**********/
}
int main()
{
    SqList L[3];
    ElemType x;
    int i;
    for(i=0;i<3;i++)
    {
    	L[i].elem=(ElemType *)malloc(sizeof(ElemType)*LIST_INIT_SIZE);
    	L[i].length=0;
    	L[i].listsize=LIST_INIT_SIZE;
    	scanf("%d",&x);
        // 逆天读入数据
    	while (x)
    	{
        	L[i].elem[L[i].length++]=x;
        	scanf("%d",&x);
    	}
    }
    TriSqList(L[0],L[1],L[2]);
    for(i=0;i<L[0].length;i++)
        printf(" %d",L[0].elem[i]);
	return 0;
}


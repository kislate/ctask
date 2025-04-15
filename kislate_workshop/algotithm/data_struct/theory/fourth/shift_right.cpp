/*
任务描述
本关任务：编写一个算法，将数组A中的n个元素A[0]至A[n-1]循环右移k位。要求算法时间复杂度为O（n），空间复杂度为O（1）

相关知识
为了完成本关任务，你需要掌握：1.一维数组，2.数组的遍历。

编程要求
根据提示，在右侧编辑器填写算法函数，实现将大小为n的数据元素数组a中的元素循环右移k位。要求函数原型为：
void ShiftRightCircular(ElemType a[],int n,int k)
其中k的值可为负整数，表示循环左移；ElemType已经在后台测试程序中定义。

测试说明
平台会自动读取输入数据，对你编写的代码进行测试，并输出结果。

测试输入：10，5；（输入的是n与k的值）// 1 2 3 4 5 6 7 8 9 10
// 10 9 8 7 6 5 4 3 2 1
预期输出：
 6 7 8 9 10 1 2 3 4 5

测试输入：10，-3；
预期输出：
 4 5 6 7 8 9 10 1 2 3

开始你的任务吧，祝你成功！
*/
#include<stdio.h>
#include<stdlib.h>
typedef int ElemType;

void ShiftRightCircular(ElemType *A,int n,int k)
{
/************** begin *****************/
// 空间复杂度为O(1)意味着不能有辅助空间, 使用反转字符串的方法
int split = (k % n + n) % n, temp;
for(int i = 0; i < n / 2; i++) temp = A[i], A[i] = A[n-i-1], A[n-i-1] = temp;
for(int i = 0; i < split / 2; i++) temp = A[i], A[i] = A[split-i-1], A[split-i-1] =temp;
for(int i = 0; i < (n-split) / 2; i++) temp = A[split+i], A[split+i] = A[n-i-1], A[n-i-1] = temp;
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

// 命令行实现对N个整数排序。

// 编程实现对 n 个整数排序，排序元素的个数 n 由命令行参数指定，排序的原则由命令行可选参数决定，可选参数以负号开头，
// 有参数 -d 时按递减顺序排序，否则按递增顺序排序。假设该程序名为 sort，那么命令 "sort 10 -d" 表示对 10 个整数按降序排序，
// 在 main 函数中输入 10 个整数和输出排序后的结果，要求 n 个整数的存储无冗余

// 输入输出示例
// 输入：执行输入的命令，再按照命令输入N个整数。
// sort 5 -d      (这是命令行)
// 4 3 8 5 1      (这是程序执行后输入的5个待排序数据) 

// 输出：输出排序后的结果。
// 8 5 4 3 1

// 注意：要求n个整数的存储无冗余。——>若不采用可变数组是s[n]的用法，即要求动态分配
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int mode=0;//mode控制排序规则，0升序，1降序
void sort(int *s,int n)
{
    for(int *i=s;i<s+n-1;i++)
        for(int *j=i;j<s+n;j++)
            if((!mode&&(*i)>(*j))||(mode&&(*i)<(*j)))
            {
                int temp=*i;
                *i=*j;
                *j=temp;
            }
}

int main(int agrc,char* agrv[])
{
    int n=atoi(agrv[1]);
    if(agrc>=3)
    {
        if(strcmp(agrv[2],"-d")==0) mode=1;
    }
    //输入数据
    int *s=(int *)malloc(n*sizeof(int));//动态分配
    for(int i=0;i<n;i++)scanf("%d",&s[i]);

    sort(s,n);

    for(int i=0;i<n;i++)printf("%d ",s[i]);

    free(s);
}
// 定义函数RemoveSame(a,n)，去掉有n个元素的有序整数序列a中的重复元素，返回去重后序列的长度。

// 示例
// 输入：
// 5
// 3 3 3 6 6

// 输出：注意不需要输出结果长度后的内容
// 3 6
// 2
#include<stdio.h>
int RemoveSame(int *s,int n)
{
    int c=1,same=*s,*j=s;//c记忆不同元素，same做相同判断，j用于改变数组 
    
    for(int *i=s+1;i<s+n;i++)
    {
        if(*i==same)continue;
        else {
            j++;
            same=*i;
            *j=*i;
            c++;
        }
    }
    return c;
}

int main()
{
    int n,count;
    scanf("%d",&n);
    int arr[n];
    for(int i=0;i<n;i++) scanf("%d",&arr[i]);//输入是有序的，故不需要排序
    count=RemoveSame(arr,n);
    for(int j=0;j<count;j++) printf("%d ",arr[j]);
    printf("\n");
    printf("%d",count);
}
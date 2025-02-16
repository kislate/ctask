/*Problem 2: 暴雨症候
Input file:
 Output file:
 Time limit:
 standard input
 standard output
 1 seconds
 Memory limit: 512 megabytes
 Problem Description
 W市气候潮湿，全年多雨。W市气象部门预计在接下来的N 天内将产生连续降水。
每一天的降水量可以用一个正整数来量化，第i天的降水量为ri。若在接下来的N 天内，
有超过X天的降水量不低于X，则称接下来的N 天可以构成X级暴雨症候。
请问，接下来的N 天最高构成几级暴雨症候。
Input
第一行为一个整数N。
第二行为N 个整数，第i个为ri。
Output
输出一行一个整数，表示最高构成的暴雨症候等级。
Examples
 Standard Input
 9
 Standard Output
 3
 3 3 3 1 2 2 4 4 4
 Scoring
对于60%的测试数据，1≤N,ri≤1000；
对于100% 的测试数据，1≤N,ri≤106*/

#include<stdio.h>
int main(void)
{
    int n;
    scanf("%d",&n);
    int arr[1000000]={0};
    int markArr[1000000]={0};
    int max=0;
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
        markArr[arr[i]]++;
        if((markArr[arr[i]]>=arr[i])&&(arr[i]>=max))
        {
            max=arr[i];
        }
    }
    printf("%d",max);
}//这道题审错了
//这个方法是错的
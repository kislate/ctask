//23.选择

// 【题目描述】
// 给你 n 个数和一个整数 k。
// 问有你有多少种方法从 n 个数里面选 k 个数使得和为质数？
// 【输入格式】
// 第一行两个空格隔开的整数 n, k。
// 第二行 n 个整数，分别为 x1, x2, · · · , xn。
// 【输出格式】
// 输出一个整数，表示种类数。
// 【样例 1 输入】
// 1 4 3
// 2 3 7 12 19
// 【样例 1 输出】
// 1 1
// 【子任务】
// 数据保证：1 ≤ n ≤ 20，k < n，1 ≤ xi ≤ 5 × 106。
#include<stdio.h>

int count=0,flag=0,reset=0;//flag用于判断k是否>n/2;
long ans=0,sum=0;

int isPrime(int n){
    for(int i=2,j=n>>1;i<=j;++i){
      if(!(n%i)) return 0;
  }
  return 1;
}

//k重循环
void cicle(int *a,int n,int k,int start)
{
    if(k==0)
        return;
    for(int i=start;i<n;i++)
    {
        ans+=a[i];
        reset++;
        if(reset==k)
        {
            if(!flag&&isPrime(ans) || flag&&isPrime(sum-ans))
                count++;
            //回溯,将后续结果找完
            reset--;
            ans-=a[i];
            continue;
        }
        cicle(a,n,k,i+1);
        //回溯,即将上一次的操作撤销
        reset--;
        ans-=a[i];
    }
}

int main()
{
    int n,k;
    scanf("%d %d",&n,&k);
    int a[n];
    for(int i=0;i<n;i++)
        {
            scanf("%d",&a[i]);
            sum+=a[i];
        }
    if(k>n/2)
    {
        k=n-k;
        flag=1;
    }

    cicle(a,n,k,0);
    printf("%d",count);
    return 0;

}

//此题难点在于如何设计k重循环，该解思路是递归，同时利用了迷宫回溯的想法。
//由于是找有多少种合题意的解，故每种情况都得考虑计算（不知道有没有更好的方法）
//如果k>n/2,则将k=n-k,同时flag=1,利用sum-ans可以减少计算量与循环次数（最糟糕也就是n/2重循环）
//如果在质数判断时，若将n开根号（即利用math库里的开根号函数，是否更快呢？————应该会）



//好吧，ai解法更简洁，明显更好（针对backtrack函数）
// emmm... 自己局限于迷宫回溯的思想，导致思路不够开阔，同时太过于执着于k重循环，没能做到下述的简洁
//ai解法
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// // 判断一个数是否为质数
// bool is_prime(int num) {
//     if (num < 2) return false;
//     for (int i = 2; i <= sqrt(num); i++) {
//         if (num % i == 0) return false;
//     }
//     return true;
// }

// ***回溯法枚举所有组合
void backtrack(int *nums, int n, int k, int start, int sum, int *count) {
    // 如果已经选了 k 个数，检查它们的和是否为质数
    if (k == 0) {
        if (is_prime(sum)) (*count)++;
        return;
    }

    // 从 start 开始枚举
    for (int i = start; i < n; i++) {
        // 选择当前数，并递归进入下一层
        backtrack(nums, n, k - 1, i + 1, sum + nums[i], count);//***直接利用了函数回调(sum+nums[i]直接变回sum）
    }
}

// int main() {
//     int n, k;
//     scanf("%d %d", &n, &k);

//     int nums[n];
//     for (int i = 0; i < n; i++) {
//         scanf("%d", &nums[i]);
//     }

//     int count = 0; // 记录符合条件的组合数
//     backtrack(nums, n, k, 0, 0, &count); // 调用回溯函数

//     printf("%d\n", count); // 输出结果

//     return 0;
// }
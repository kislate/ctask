/*
lhm 玩数字（lhmb）
【题目描述】
lhm 有 n 个正整数，他很喜欢它们。lhm 突然想知道这些正整数中第 k 个最小整数
（大小一样的整数只算一次），你能帮帮他吗？
【输入格式】
第一行为 n 和 k。
第二行开始为 n 个正整数的值，整数间用空格隔开。
【输出格式】
第 k 个最小整数的值；若无解，则输出 NO RESULT。
【样例 1 输入】
1   10 3
2   1 3 3 7 2 5 1 2 4 6
【样例 1 输出】
1   3
【子任务】
数据保证：n ≤10000，k ≤1000，正整数均小于 30000。
*/
// #include<stdio.h>
// #include<stdlib.h>
// #include<string.h>
// #include<math.h>
// int cmp(const void *a,const void *b)
// {
//     return *(int *)a - *(int *)b;
// }
// int main(void)
// {
//     int n,k;
//     scanf("%d%d",&n,&k);
//     int *arr = (int *)malloc(sizeof(int) * n);
//     if(arr == NULL)
//     {
//         fprintf(stderr,"没成\n");
//         return -1;
//     }
//     for(int i = 0 ; i < n ; i++)
//     {
//         scanf("%d",arr + i);
//     }
//     qsort(arr,n,sizeof(int),cmp);
//     int cnt = 1;
//     for(int i = 1 ; i < n ; i++)
//     {
//         if(arr[i] != arr[i - 1])
//         {
//             cnt++;
//         }
//         if(cnt == k)
//         {
//             printf("%d\n",arr[i]);
//             return 0;
//         }
//     }
//     printf("NO RESULT\n");
//     return 0;
// }
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int cmp(const void *a,const void *b)
{
    return *(int *)a - *(int *)b;
}
int main(void)
{
    
}
/*
lhm 玩 01（lhma）
【题目描述】
lhm 喜欢 01，于是他写了一个由 N ×N 的 0 和 1 的矩阵。
但 lhm 感觉这个矩阵太大了，于是他要压缩！他要把矩阵压缩成一串数字，其中第
一个数字是 N ，剩下的数字为：从矩阵的第一行第一个符号开始计算，按书写顺序从左
到右，由上至下。第一个数表示连续有几个 0，第二个数表示接下来连续有几个 1，第
三个数再接下来连续有几个 0，第四个数接着连续几个 1，以此类推......
例如: 以下矩阵：
1 0001000
2 0001000
3 0001111
4 0001000
5 0001000
6 0001000
7 1111111
对应的压缩数字序列是：7 3 1 6 1 6 4 3 1 6 1 6 1 3 7 （第一个数是 N , 其余各位表
示交替表示 0 和 1 的个数，压缩数字序列保证 N ×N = 交替的各位数之和）
【输入格式】
数据输入一行，由空格隔开的若干个整数，表示压缩数字序列。
其中，压缩数字序列的第一个数字就是 N ，表示这个矩阵应当是 N ×N 的大小。
接下来的若干个数字，含义如题目描述所述。
【输出格式】
输出一个 N ×N 的 01 矩阵（点阵符号之间不留空格）。
【样例 1 输入】
1 7 3 1 6 1 6 4 3 1 6 1 6 1 3 7
【样例 1 输出】
1 0001000
2 0001000
3 0001111
4 0001000
5 0001000
6 0001000
7 1111111
【子任务】
数据保证，3 ≤N ≤200。*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
int main(void)
{
    int N;
    scanf("%d",&N);
    int *matrix = (int *)malloc(sizeof(int) * N * N);
    if(matrix == NULL)
    {
        fprintf(stderr,"没成\n");
        return -1;
    }
    int cnt;
    int *p_mov = matrix;
    int flag = 0;
    while(scanf("%d",&cnt) != EOF)
    {
        if(flag == 0){
            for(int i = 0 ; i < cnt ; i++)
            {
                *p_mov = 0;
                p_mov++;
            }
        }
        else{
            for(int i = 0; i < cnt ; i++)
            {
                *p_mov = 1;
                p_mov++;
            }
        }
        flag = 1 - flag;
    }
    p_mov = matrix;
    for(int i = 0 ; i < N ; i++)
    {
        for(int j = 0 ; j < N ; j++)
        {
            printf("%d",*p_mov);
            p_mov++;
        }
        putchar(10);
    }
    free(matrix);
    return 0;
}
/*
【题目描述】
小明十分热爱学习数学，为了方便他查找相关数学定理，他有一个 M 页的笔记本。
小明十分勤俭节约，他只会用铅笔在笔记本上书写，如果笔记本写完了，就把最早记录
的那一页用橡皮擦擦干净。
小明现在在阅读一篇数学论文，在证明中依次提到了 N 个定理，同一定理可能被
多次提及。由于小明的记性不太好，每次遇到一个定理，小明都会在自己的笔记本里面
查询这个定理，假如没有这个定理，就翻看教材，然后用 1 页将这个定理记下。假如笔
记本已经满了，那么他会将当前的笔记本中最先记录的那一页定理擦除，再记下这个定
理。
小明现在想要知道，在阅读整篇论文的过程中，他需要翻阅多少次教材？起初，小
明的笔记本是空的。
【输入格式】
共 2 行。每行中两个数之间用一个空格隔开。
第一行为两个正整数 M, N ，代表笔记本页数和论文提及定理的次数。
第二行为 N 个非负整数，按照论文的顺序，每个数（大小不超过 1000）代表一个
数学定理。论文中提及的两个定理是同一个定理，当且仅当它们对应的非负整数相同。
【输出格式】
一个整数，为小明需要翻教材的次数。
【样例 1 输入】
1 3 7
2 1 2 1 5 4 4 1
【样例 1 输出】
1 5
【样例 1 解释】
整个阅读论文的过程如下：每行表示遇到了一个定理后的笔记本内容：
1. 1：查找定理 1 并写进笔记本。
2. 1 2：查找定理 2 并写进笔记本。
3. 1 2：在笔记本中找到定理 1。
4. 1 2 5：查找定理 5 并写进笔记本。
5. 2 5 4：查找定理 4 并写进笔记本替代定理 1。
6. 2 5 4：在笔记本中找到定理 4。
7. 5 4 1：查找定理 1 并调入笔记本替代定理 2。
【子任务】
对于 10% 的数据有 M = 1，N ≤5；
对于 100% 的数据有 1 ≤M ≤100，1 ≤N ≤1000。
【提示】
请注意表示数学定理的数可能为 0，你需要采取有效的手段，分辨数组中“尚未存
储有效元素的位置”和“已经存储了 0 的位置”。
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//
int read(int *Theo , int M,int N);
//
int main(void)
{
    int N,M;
    int cnt = 0;
    scanf("%d%d",&N,&M);
    int *Theo = (int *)malloc(sizeof(int) * M);
     if ( Theo == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    memset(Theo,0,sizeof(int)*M);
    for(int i = 0 ; i < M ; i++)
    {
        scanf("%d",Theo + i);
    }
    cnt = read(Theo,M,N);
    printf("%d\n",cnt);
    free(Theo);
    // system("pause");
    return 0;
}
int read(int *Theo , int M , int N)
{
    int ret = 0;
    int *Note = (int *)malloc(sizeof(int) * N);
    if ( Note == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    int last = 0;
    memset(Note,-1,sizeof(int)*N);
    for(int i = 0 ; i < M ; i++)
    {
        for(int j = 0 ; j < N ; j++)
        {
            if(Theo[i] == Note[j])
            {
                break;
            }
            if(Note[j] == -1)
            {
                ret++;
                Note[j] = Theo[i];
                break;
            }
            if(j == N -1)
            {
                ret++;
                Note[last] = Theo[i];
                last++;
                if(last == N)
                {
                    last = 0;
                }
            }
        }
    }
    free(Note);
    return ret;
}
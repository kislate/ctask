//19.任务管理
// 【题目描述】
// 你现在有 N 个任务，依次编号为 1 ∼ N。部分任务有一些前置任务。现在，由于
// 你编号为 1 的任务已经接近截止时间，十分紧急。你想要知道，如果要完成 1 号任务，
// 至少一共要完成多少任务？
// 【输入格式】
// 输入共 N + 1 行。
// 输入的第一行为一个正整数 N。
// 接下来 N 行，第 i 行描述了编号为 i 的任务的前置任务：
// • 第 i 行共有 Ci + 1 个数。
// • 第一个数为 Ci。
// • 接下来 Ci 个数，描述了该任务的前置任务的编号。
// 【输出格式】
// 输出一行一个整数，表示至少需要完成的任务数量。
// 【样例 1 输入】
// 1 5
// 2 1 2
// 3 1 3
// 4 1 4
// 5 0
// 6 0
// 【样例 1 输出】
// 1 4
// 【子任务】
// 对于 100% 的测试数据，1 ≤ N ≤ 5000，0 ≤ Ci < N，保证任务之间不会构成循环
// 依赖。
#include<stdio.h>
#include<stdlib.h>
int count=0;
void dotask(int **task,int *done,int now)
{
	count++;
	done[now-1]=1;
	
	for(int i=1;i<=task[now-1][0];i++)//遍历前置任务
			if(done[task[now-1][i]-1]==0)
				dotask(task,done,task[now-1][i]);
}
int main()
{
	int N,a;
	scanf("%d",&N);
	int done[N];//记录是否被做过 
	for(int i = 0; i < N; i++) {
		done[i] = 0;
	}
	int **task=(int **)malloc(N*sizeof(int*));

	//记录任务 
	for(int i=0;i<N;i++)
	{
		scanf("%d",&a);
		task[i] = (int *)malloc((a+1)*sizeof(int));
		task[i][0] = a;
		for(int j=1;j<=a;j++) scanf("%d",&task[i][j]);
	}
	//开始做任务 
	dotask(task,done,1);
	printf("%d",count);

	//free
	for (int i = 0; i < N; i++) {
        free(task[i]);
    }
    free(task);
    free(done);

	return 0; 
} 
//这个题目我傻逼了，以为是前置任务完成一个就行（以为是找次数最优解问题），但其实是所有前置任务都完成才行，直接一个简单的递归就能解决！！！
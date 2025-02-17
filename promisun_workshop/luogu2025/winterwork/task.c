//19.任务管理
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
//15.lhm 玩数字
// 【题目描述】
// lhm 有 n 个正整数，他很喜欢它们。lhm 突然想知道这些正整数中第 k 个最小整数
// （大小一样的整数只算一次），你能帮帮他吗？
// 【输入格式】
// 第一行为 n 和 k。
// 第二行开始为 n 个正整数的值，整数间用空格隔开。
// 【输出格式】
// 第 k 个最小整数的值；若无解，则输出 NO RESULT。
// 【样例 1 输入】
// 1 10 3
// 2 1 3 3 7 2 5 1 2 4 6
// 【样例 1 输出】
// 1 3
// 【子任务】
// 数据保证：n ≤ 10000，k ≤ 1000，正整数均小于 30000。

#include<stdio.h>
#include<stdlib.h>                          
void selectSort(int *arr,int n){
    for(int i=0;i<n;i++){
    	for(int j=i+1;j<n;j++){
    		if(arr[i]>arr[j]){
    			int t=arr[i];
    			arr[i]=arr[j];
    			arr[j]=t;
			}
		}
	}
}
int main()
{
	int n,k,j=1,res,find=0;
	scanf("%d %d",&n,&k);
	int *s=(int *)malloc(n*sizeof(int));
	for(int i=0;i<n;i++)
		scanf("%d",&s[i]);
	selectSort(s,n);
	res=s[0];
	for(int i=0;i<n;i++)
	{
		if(s[i]>res) 
		{
			res=s[i];
			j++;
		}
		if(j==k) {
			find=1;
			break;
		}
	}
	if(find) printf("%d",res);
	else printf("NO RESULT");
	free(s);
	return 0; 
} 
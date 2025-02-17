//18.小 S 与历史长河
// 【题目描述】
// 小 S 是历史长河。
// 一条历史长河是对一个文明从发展到衰亡的记录，若有好事者对这个文明感兴趣，便可以从历史长河中一探究竟。
// 历史长河是一段仅包含大小写字母的字符串，记录了每一个时间点这个文明发生的重要事件。字典序越小的字母代表的事件越重要。
// 现在，有两条不同的历史长河 S 和 T，作为好事者的你正打算对比研究它们。在研究过程中，你遇到了 Q 个问题，在每个问题中，你想要比较两个文明中特定时段的事件重要程度。
// 形式化的，每次给出 ls, rs 和 lt , rt，你需要判断 S[ls, rs] 和 T[lt , rt ] 谁的字典序更小。
// 其中，S[l, r] 表示从字符串 S 的第 l 个字符到第 r 个字符连起来构成的字符串。例如，若 S 为 kitsuki，则 s[3, 5] 为 tsu。
// 【输入格式】
// 第一行是一个字符串 S。
// 第二行是一个字符串 T。
// 第三行是一个整数，表示询问次数 Q。
// 接下来 Q 行，每行四个整数 ls, rs, lt, rt，表示一次询问。
// 【输出格式】
// 对每次询问，输出一行一个字符串：
// • 如果 S[ls, rs] 的字典序更小，请输出 yifusuyi。
// • 如果 T[lt , rt] 的字典序更小，请输出 erfusuer。
// • 如果两者的字典序一样大，请输出 ovo。
// 【样例 1 输入】
// 1 Yifusuyi
// 2 yifusuYi
// 3 3
// 4 1 2 7 8
// 5 1 2 1 2
// 6 7 8 7 8
// 【样例 1 输出】
// 1 ovo
// 2 yifusuyi
// 3 erfusuer
// 【子任务】
// 对 100% 的数据，1 ≤ |S|, |T|, Q ≤ 103，1 ≤ ls ≤ rs ≤ |S|，1 ≤ lt ≤ rt ≤ |T|。输入
// 字符串仅含大小写英文字母。其中 |S| 表示历史长河 S 的长度，|T| 表示历史长河 T 的
// 长度。
#include<stdio.h>
#include<string.h>
#include<stdlib.h>  
int main()
{
	char s[1001]={0},t[1001]={0};
	int count=0,ls,rs,lt,rt; 
	
	scanf("%s",s);
	scanf("%s",t);
	scanf("%d",&count);
	char **result=(char**)malloc(count*sizeof(char*));
	for(int i=0;i<count;i++)
		result[i]=(char*)malloc(8*sizeof(char));
	//处理 
	for(int i=0;i<count;i++)
	{
		char S[1001]={0},T[1001]={0};
		scanf("%d %d %d %d",&ls,&rs,&lt,&rt);
		
		for(int m=ls-1,p=0;m<rs;m++) S[p++]=s[m];
		for(int n=lt-1,q=0;n<rt;n++) T[q++]=t[n];
		
		if(strcmp(S,T)<0) result[i]="yifusuyi";
		if(strcmp(S,T)>0) result[i]="erfusuer";
		if(strcmp(S,T)==0) result[i]="ovo";
	}
	//打印结果
	for(int i=0;i<count;i++)
		{
			printf("%s",result[i]);
			if(i<(count-1))
				printf("\n");
		}
	for (int i=0;i<count;i++) {
        free(result[i]);
    }
    free(result);
	return 0; 
} //全是紫色，free有问题吗？




//如果不分配空间直接输入一行，输出一行洛谷能过
#include<stdio.h>
#include<string.h>
int main()
{
	char s[1001]={0},t[1001]={0};
	int count=0,ls,rs,lt,rt; 
	
	scanf("%s",s);
	scanf("%s",t);
	scanf("%d",&count);
	//处理 
	for(int i=0;i<count;i++)
	{
		char S[1001]={0},T[1001]={0};
		scanf("%d %d %d %d",&ls,&rs,&lt,&rt);
		
		for(int m=ls-1,p=0;m<rs;m++) S[p++]=s[m];
		for(int n=lt-1,q=0;n<rt;n++) T[q++]=t[n];
		
		if(strcmp(S,T)<0) printf("yifusuyi");
		if(strcmp(S,T)>0) printf("erfusuer");
		if(strcmp(S,T)==0) printf("ovo");

        if(i<count-1)printf("\n");
	}
	return 0;
}

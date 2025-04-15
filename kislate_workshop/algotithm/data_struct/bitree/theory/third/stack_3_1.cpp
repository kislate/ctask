/*
任务描述
本关任务：编写程序实现双向栈。
假定以顺序存储结构实现一个双向栈，即在一个一维数组的存储空间中存在着两个栈，它们的栈底分别设在数组的两个端点。试编写实现着个双向栈的3个函数：
初始化栈inistack、入栈push和出栈pop

相关知识
为了完成本关任务，你需要掌握：1.栈，2.双向栈。
双向栈的物理结构示意图如下：

相应地，根据该示意图定义其数据类型：
#define N 100
typedef struct TWSTACK {
     ElemType elem[N];
     int top1,top2;
     } TWSTACK;

编程要求
根据提示，在右侧编辑器补充代码，实现3个函数；相应函数原型如下：
int inistack（TWSTACK &S）；
int push（TWSTACK &S，int i，ElemType e）；
int pop（TWSTACK &S，int i，ElemType &e）；

测试说明
平台会自动读取输入数据，对你编写的代码进行测试，并输出结果。

测试输入：0    系统测试初始化
预期输出： OK

测试输入：1    系统测试入栈
预期输出： OK

测试输入：2    系统测试出栈
预期输出： OK

测试输入：3  1 1 1 -1 -1 1 1 0    系统仅测试第一个栈的进出栈操作序列，第一个3代表此含义，对提供的整数序列1、2、3、...，后面1代表进栈操作，-1代表出栈操作，0代表操作结束，完成操作序列后，依次显示栈底到栈顶的元素值。
预期输出：  1 4 5

开始你的任务吧，祝你成功！
*/
#include <stdio.h>
#include <stdlib.h>
#define N 100
typedef int ElemType;
typedef struct TWSTACK {
     ElemType elem[N];
     int top1,top2;
     } TWSTACK;
//在下面的begin和end间填写相应代码
void inistack(TWSTACK &S)
//该函数实现初始化S，得到2个空栈。根据双向栈的示意图，理解初始化要求。
{
/***************begin***************/
S.top1 = 0;
S.top2 = N-1;
/*************** end ***************/
}
int push(TWSTACK &S,int i,ElemType e)
//i取值1或2，分别对应左或右栈，将元素e压入S的对应栈。成功入栈返回1，否则返回0
{
/***************begin***************/
if(S.top1 == S.top2+1) return 0;
if(i == 1) S.elem[S.top1] = e, S.top1++;
else if(i == 2) S.elem[S.top2] = e, S.top2--;
else return 0;
return 1;
/*************** end ***************/
}
int pop(TWSTACK &S,int i, ElemType &e)
//i取值1或2，分别对应左或右栈，将S对应栈的栈顶元素出栈，赋值给e。成功出栈返回1，否则返回0
{
/***************begin***************/
if(i == 1){
    if(S.top1 == 0) return 0;
    else e = S.elem[S.top1 - 1], S.top1--;
}
if(i == 2){
    if(S.top2 == N-1) return 0;
    else e = S.elem[S.top2 + 1], S.top2++;
}
return 1;
/*************** end ***************/
}

int main()
{
int  i,f,e1,e2;
TWSTACK S;
scanf("%d",&f);
switch(f)
{
case 0: inistack(S);
      if (S.top1==0 && S.top2==N-1) printf("OK");
      else printf("初始化失败");
		break;
case 1:	S.top1=rand()%N;
		S.top2=S.top1-1;
      if (push(S,1,10))
      		{  printf("栈1入栈时未判满");break;}
		S.top1=rand()%N;
		S.top2=S.top1-1;
      if (push(S,2,10))
      		{  printf("栈2入栈时未判满");break;}
      S.top1=rand()%N;
		S.top2=S.top1;
      e1=rand();
      if (push(S,1,e1)==0 || S.top1!=S.top2+1|| S.elem[S.top1-1]!=e1)
      		{  printf("栈1入栈时有错");break;}
      S.top1=rand()%N;
		S.top2=S.top1;
      if (push(S,2,e1)==0 || S.top1!=S.top2+1 || S.elem[S.top2+1]!=e1)
      		{  printf("栈2入栈时有错");break;}
      printf("OK");
		break;
case 2: S.top1=0;
      S.top2=N-1;
      if (pop(S,1,e1) || pop(S,2,e1)) 
      	{  printf("出栈时未判空");break;}
      e1=rand();
      push(S,1,e1);
     if (pop(S,1,e2)==0 || e1!=e2) {printf("栈1出栈有错");break;} 
      e1=rand();
      push(S,2,e1);
     if (pop(S,2,e2)==0 || e1!=e2) {printf("栈2出栈有错");break;} 
       printf("OK");
		break;
case 3: i=1;
	   inistack(S);
      scanf("%d",&f);
      while (f)
      {
      	if (f==1) push(S,1,i++);
       else pop(S,1,e1);
	     scanf("%d",&f);
      }
      for(i=0;i<S.top1;i++)
      	printf(" %d",S.elem[i]);
}
return 1;

}
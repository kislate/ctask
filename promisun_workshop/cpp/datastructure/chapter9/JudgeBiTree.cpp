#include "stdio.h"
#include "stdlib.h"

#define TRUE 1
	#define FALSE 0
	#define OK 1
	#define ERROR 0
	#define YES 1
	#define NO 0
	#define INFEASIBLE -1
	#define OVERFLOW -2

	typedef int status;
	typedef int KeyType; 
	typedef struct {
         KeyType  key;
         char others[20];
	} TElemType; //二叉树结点类型定义


	typedef struct BiTNode{  //二叉链表结点的定义
	      TElemType  data;
	      struct BiTNode *lchild,*rchild;
	} BiTNode, *BiTree;

typedef struct {
    int pos;
    TElemType data;
} DEF;
status CreateBiTree(BiTree &T,DEF definition[])
{
    int i=0,j;
    static BiTNode *p[100];
    while (j=definition[i].pos)
    {
    	 p[j]=(BiTNode *)malloc(sizeof(BiTNode));
       p[j]->data=definition[i].data;
       p[j]->lchild=NULL;
       p[j]->rchild=NULL;
       if (j!=1)
       		if (j%2)   p[j/2]->rchild=p[j];  
       	   else      p[j/2]->lchild=p[j];
       i++;
    }
    T=p[1];
    return OK;
}
status max(BiTree T)
{
    if (T == NULL) return 0;
    int leftMax = max(T->lchild);
    int rightMax = max(T->rchild);
    int currentMax = T->data.key;
    if (leftMax > currentMax) currentMax = leftMax;
    if (rightMax > currentMax) currentMax = rightMax;
    return currentMax;
}
status min(BiTree T)
{
    if (T == NULL) return 100000;
    int leftMin = min(T->lchild);
    int rightMin = min(T->rchild);
    int currentMin = T->data.key;
    if (leftMin < currentMin) currentMin = leftMin;
    if (rightMin < currentMin) currentMin = rightMin;
    return currentMin;
}
status JudgeBiTree(BiTree T)
//判断二叉树T是否为二叉排序树
{
    // 请在这里补充代码，完成本关任务
    
    if (T == NULL) return YES; // 空树是二叉排序树
    if (T->lchild != NULL && (T->lchild->data.key > T->data.key || max(T->lchild)>T->data.key)) return NO;
    if (T->rchild != NULL && (T->rchild->data.key < T->data.key|| min(T->rchild)<T->data.key)) return NO; 
    if (!JudgeBiTree(T->lchild)) return NO;
    if (!JudgeBiTree(T->rchild)) return NO;
    return YES; 
}


int main()
{
DEF definition[100];
BiTree T;
int ans,i=0;
do {
	scanf("%d%d%s",&definition[i].pos,&definition[i].data.key,definition[i].data.others);
} while (definition[i++].pos);
CreateBiTree(T,definition);
if (JudgeBiTree(T))
	   printf("YES");
else 	printf("NO");
return 1;
}
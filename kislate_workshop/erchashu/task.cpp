#include "stdio.h"
#include "stdlib.h"
#include <bits/stdc++.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int KeyType; 
typedef struct {
    int pos;
    TElemType data;
} DEF;
typedef struct {
    KeyType  key;
    char others[20];
} TElemType; //二叉树结点类型定义


typedef struct BiTNode{  //二叉链表结点的定义
	TElemType  data;
	struct BiTNode *lchild,*rchild;
} BiTNode, *BiTree;

using namespace std;
status CreateBiTree(BiTree &T,TElemType definition[])
/*根据带空枝的二叉树先根遍历序列definition构造一棵二叉树，将根节点指针赋值给T并返回OK，
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    static KeyType mem[10000] = {0};
    static int idx = 0;
    if(definition[idx].key == -1 || definition[idx].key == 0){
        T = NULL;
        idx++;
        return OK;
    }
    if(mem[definition[idx].key] == 1){
        return ERROR;
    }
    mem[definition[idx].key] = 1;

    T = (BiTNode *)malloc(sizeof(BiTNode));
    if(!T) return OVERFLOW;
    T->data = definition[idx++];
    status lres = CreateBiTree(T->lchild, definition);
    status rres = CreateBiTree(T->rchild, definition);
    return (lres == OK && rres == OK);
    /********** End **********/
}

status ClearBiTree(BiTree &T)
//将二叉树设置成空，并删除所有结点，释放结点空间
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T == NULL) return OK;
    ClearBiTree(T->lchild);
    ClearBiTree(T->rchild);
    free(T);
    T = NULL;
    return OK;
    /********** End **********/
}

int BiTreeDepth(BiTree T)
//求二叉树T的深度
{
    static int depth;
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T == NULL) return 0;
    return 1 + max(BiTreeDepth(T->lchild), BiTreeDepth(T->rchild));
    /********** End **********/
}

BiTNode* LocateNode(BiTree T,KeyType e)
//查找结点
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T == NULL) return NULL;
    if(T->data.key == e) return T;
    BiTNode* lres = LocateNode(T->lchild, e);
    if(lres) return lres;
    BiTNode* rres = LocateNode(T->rchild, e);
    if(rres) return rres;
    return NULL;
    /********** End **********/
}

int mem[10000] = {0};
status to_mem(BiTree T)
{
    if(T == NULL) return 0;
    mem[T->data.key] = 1;
    to_mem(T->lchild);
    to_mem(T->rchild);
    return 0;
}

status Assign(BiTree &T,KeyType e,TElemType value)
//实现结点赋值。此题允许通过增加其它函数辅助实现本关任务
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T == NULL) return ERROR;
    for(int i = 0; i < 100; i++) mem[i] = 0;
    to_mem(T);
    if(value.key != e  && mem[value.key] == 1) 
    {
        return ERROR;
    }
    // printf("%d, %d", value.key, mem[e]);
    BiTNode* node = LocateNode(T, e);
    mem[e] = 0;
    mem[value.key] = 1;
    if(node == NULL) return ERROR;
    node->data = value;
    return OK;
    /********** End **********/
}

BiTNode* GetSibling(BiTree T,KeyType e)
//实现获得兄弟结点
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T == NULL) return NULL;
    if(T->lchild && T->lchild->data.key == e) return T->rchild;
    if(T->rchild && T->rchild->data.key == e) return T->lchild;
    BiTNode* lres = GetSibling(T->lchild, e);
    if(lres) return lres;
    BiTNode* rres = GetSibling(T->rchild, e);
    if(rres) return rres;
    return NULL;
    /********** End **********/
}

status InsertNode(BiTree &T,KeyType e,int LR,TElemType c)
//插入结点。此题允许通过增加其它函数辅助实现本关任务
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T == NULL) return ERROR;
    if(LR == -1)
    {
        T->data = c;
        T->rchild = T;
        T->lchild = NULL;
        return OK;
    }
    BiTNode * node = LocateNode(T, e);
    if(node == NULL) return ERROR;
    if(LR == 0)
    {
        if(node->lchild != NULL) return ERROR;
        node->lchild = (BiTNode *)malloc(sizeof(BiTNode));
        if(!node->lchild) return OVERFLOW;
        node->lchild->data =c;
        node->lchild->lchild = NULL;
        node->lchild->rchild = NULL;
    }
    else if(LR == 1)
    {
        if(node->rchild != NULL) return ERROR;
        node->rchild = (BiTNode *)malloc(sizeof(BiTNode));
        if(!node->rchild) return OVERFLOW;
        node->rchild->data =c;
        node->rchild->lchild = NULL;
        node->rchild->rchild = NULL;
    }
    else return ERROR;
    return OK;
    

    /********** End **********/
}




//////////////////////////////
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

void PreOrderTraverse(BiTree T)
{
    if (T)
    {
        printf(" %d,%s",T->data.key,T->data.others);
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}

void InOrderTraverse(BiTree T)
{
    if (T)
    {
        InOrderTraverse(T->lchild);
        printf(" %d,%s",T->data.key,T->data.others);
        InOrderTraverse(T->rchild);
    }
}

int main()
{
DEF definition[100];
BiTree T;
TElemType e;
int ans,i=0,key;
do {
	scanf("%d%d%s",&definition[i].pos,&definition[i].data.key,definition[i].data.others);
} while (definition[i++].pos);
ans=CreateBiTree(T,definition);
	scanf("%d%d%s",&key,&e.key,e.others);
	ans=Assign(T,key,e);
	if (ans==OK)
	{
	    PreOrderTraverse(T);
	    printf("\n");
	    InOrderTraverse(T);
	}
	else printf("赋值操作失败");
	return 1;
}

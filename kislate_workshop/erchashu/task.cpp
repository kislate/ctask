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

status InsertNode(BiTree &T,KeyType e,int LR,TElemType c)
//插入结点。此题允许通过增加其它函数辅助实现本关任务
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T == NULL) return ERROR;
    if(LR != 0 && LR != 1 && LR != -1) return ERROR;
    if(LocateNode(T, c.key) != NULL) return ERROR; // 不能有相同的关键字
    if(LR == -1)
    {
        BiTNode * newNode = (BiTNode *)malloc(sizeof(BiTNode));
        if(!newNode) return OVERFLOW;
        newNode->data = c;
        newNode->rchild = T;
        newNode->lchild = NULL;
        T = newNode;
        return OK;
    }
    BiTNode * node = LocateNode(T, e);
    if(node == NULL) return ERROR;
    if(LR == 0)
    {
        BiTNode * newNode = (BiTNode *)malloc(sizeof(BiTNode));
        if(!newNode) return OVERFLOW;
        newNode->data = c;
        newNode->lchild = NULL;
        newNode->rchild = node->lchild;
        node->lchild = newNode;
        return OK;
    }
    else if(LR == 1)
    {
        BiTNode * newNode = (BiTNode *)malloc(sizeof(BiTNode));
        if(!newNode) return OVERFLOW;
        newNode->data = c;
        newNode->lchild = NULL;
        newNode->rchild = node->rchild;
        node->rchild = newNode;
        return OK;
    }
    else return ERROR;
    return ERROR;
    /********** End **********/
}

status InOrderTraverse(BiTree T,void (*visit)(BiTree))
//中序遍历二叉树T
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T == NULL) return ERROR;
    InOrderTraverse(T->lchild, visit);
    visit(T);
    InOrderTraverse(T->rchild, visit);
    return OK;
    /********** End **********/
}

status PostOrderTraverse(BiTree T,void (*visit)(BiTree))
//后序遍历二叉树T
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/


    /********** End **********/
}



/*
任务描述
本关任务：编写一个函数实现结点删除
函数原型：status DeleteNode(BiTree &T,KeyType e)；
功能说明：e是和T中结点关键字类型相同的给定值。删除T中关键字为e的结点；同时，根据该被删结点的度进行讨论：

如关键字为e的结点度为0，删除即可；
如关键字为e的结点度为1，用关键字为e的结点孩子代替被删除的e位置；
如关键字为e的结点度为2，用e的左子树（简称为LC）代替被删除的e位置，将e的右子树（简称为RC）作为LC中最右节点的右子树。
成功删除结点后返回OK，否则返回ERROR。

相关知识
为了完成本关任务，你需要掌握：1.二叉树，2.二叉链表，3.删除结点的语义。

编程要求
根据提示，在右侧编辑器补充代码，完成函数DeleteNode的编写

测试说明
平台会自动提供输入，对你编写的代码进行测试：

下列输入为结点在满二叉树中的编号和结点值的序列，当结点在满二叉树中的编号为0时表示输入结束。例如： 6 4 d  表示（4，d）的结点在满二叉树中的编号为6； 0 0 null代表结束标记。接着输入的是e值。正确完成删除后，通过输出先序和中序遍历序列检验正确性。


测试输入：1 1 a    2 2 b     3 3 c    6 4 d    7 5 e    0 0 null   1
预期输出： 
 2,b 3,c 4,d 5,e
 2,b 4,d 3,c 5,e

 
测试输入：1 1 a    2 2 b     3 3 c    6 4 d    7 5 e    0 0 null   10
 预期输出：  删除操作失败

开始你的任务吧，祝你成功！
*/
// 找到父亲节点
status FindParent(BiTree T, KeyType e, BiTNode* &parent)
{
    if(T == NULL) return ERROR;
    if(T->lchild != NULL && T->lchild->data.key == e)
    {
        parent = T;
        return OK;
    }
    if(T->rchild != NULL && T->rchild->data.key == e)
    {
        parent = T;
        return OK;
    }
    if(FindParent(T->lchild, e, parent) == OK) return OK;
    if(FindParent(T->rchild, e, parent) == OK) return OK;
    return ERROR;
}

status DeleteNode(BiTree &T,KeyType e)
//删除结点。此题允许通过增加其它函数辅助实现本关任务
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T == NULL) return ERROR;
    if (T->data.key == e) {
    BiTNode *del = T;
        // 度为0
        if (T->lchild == NULL && T->rchild == NULL) {
            T = NULL;
        }
        // 度为1
        else if (T->lchild == NULL) {
            T = T->rchild;
        }
        // 度为1（只有左孩子）
        else if (T->rchild == NULL) {
            T = T->lchild;
        }
        // 度为2
        else {
            BiTNode *p = T->lchild;
            while (p->rchild != NULL) {
                p = p->rchild;
            }
            p->rchild = T->rchild;
            T = T->lchild;
        }
        free(del);
        return OK;
    }
    // 递归;
    if(T->lchild && DeleteNode(T->lchild, e) == OK) return OK;
    if(T->rchild && DeleteNode(T->rchild, e) == OK) return OK;
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

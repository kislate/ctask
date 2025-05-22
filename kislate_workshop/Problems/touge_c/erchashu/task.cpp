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

// 非递归
status PreOrderTraverse(BiTree T, void (*visit)(BiTree)) {
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    BiTree stack[1000];
    int top = 0;
    if(T != NULL){
        stack[top++] = T;
    }
    while(top > 0){
        T = stack[--top]; // 弹出栈顶元素
        visit(T); // 访问当前节点
        
        // 先压右孩子, 在压左孩子
        if(T->rchild != NULL){
            stack[top++] = T->rchild;
        }
        if(T->lchild != NULL){
            stack[top++] = T->lchild;
        }
    }
    return OK;
    /********** End **********/
}

status In_feidigui(BiTree T, void (*visit)(BiTree))
{
    BiTree stack[1000];
    int top = 0;
    stack[top++] = T;
    while(top){
        T = stack[top-1];
        while(T)
        {
            T=T->lchild;
            stack[top++] = T;
        }
        top--;
        if(top){
            T=stack[--top];
            visit(T);
            stack[top++] = T->rchild;
        }
    }
    return OK;
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
    if(T == NULL) return ERROR;
    PostOrderTraverse(T->lchild, visit);
    PostOrderTraverse(T->rchild, visit);
    visit(T);
    return OK;
    /********** End **********/
}

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

// 按层遍历
status LevelOrderTraverse(BiTree T,void (*visit)(BiTree))
//按层遍历二叉树T
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T == NULL) return ERROR;
    BiTree queue[1000];
    int front = 0, rear = 0;
    queue[rear++] = T;
    while(front < rear)
    {
        T = queue[front++];
        visit(T);
        if(T->lchild!=NULL) queue[rear++] = T->lchild;
        if(T->rchild!=NULL) queue[rear++] = T->rchild;
    }
    return OK;
    /********** End **********/
}

void saveNode(BiTree T, FILE* fp){
    if(T == NULL){
        fputc(0, fp);
        return;
    }
    fputc(1, fp);
    fwrite(&T->data, sizeof(TElemType), 1, fp);
    saveNode(T->lchild, fp);
    saveNode(T->rchild, fp);
}

status SaveBiTree(BiTree T, const char FileName[])
{
    FILE* fp;
    if((fp = fopen(FileName, "wb")) == NULL) return ERROR;
    saveNode(T, fp);
    fclose(fp);
    return OK;
}

void loadNode(BiTree& T, FILE* fp){
    int flag = fgetc(fp);
    if(flag == 0){
        T = NULL;
        return;
    }
    T = (BiTNode*)malloc(sizeof(BiTNode));
    fread(&T->data, sizeof(TElemType), 1, fp);
    loadNode(T->lchild, fp);
    loadNode(T->rchild, fp);
}

status LoadBiTree(BiTree& T, const char FileName[])
{
    FILE* fp;
    if((fp = fopen(FileName, "rb")) == NULL) return ERROR;
    loadNode(T, fp);
    fclose(fp);
    return OK;
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


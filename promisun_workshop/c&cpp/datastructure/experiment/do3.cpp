#include "stdio.h"
#include "stdlib.h"

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
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

status CreateBiTree(BiTree &T,TElemType definition[])
/*根据带空枝的二叉树先根遍历序列definition构造一棵二叉树，将根节点指针赋值给T并返回OK，
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    static int i=0;
    static int mem[100]={0};
    if(definition[i].key==-1||definition[i].key==0) 
    {         
        T=NULL;
        i++;
        return OK;
    }
    if(mem[definition[i].key]==1) return ERROR; //关键字不唯一
    mem[definition[i].key]=1;
    T = (BiTNode *)malloc(sizeof(BiTNode));
    if(!T) return OVERFLOW; //内存分配失败
    T->data=definition[i++];
    status lstatus=CreateBiTree(T->lchild,definition);
    status rstatus=CreateBiTree(T->rchild,definition);
    if(lstatus==OK && rstatus==OK) return OK;
    /********** End **********/
}

void visit(BiTree T) {
    if(T->data.key != 0 || T->data.others[0] != '\0') // 空树不输出
        printf("%d,%s ", T->data.key, T->data.others);
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

status ClearBiTree(BiTree &T)
//将二叉树设置成空，并删除所有结点，释放结点空间
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T==NULL) return OK;
    ClearBiTree(T->lchild);
    ClearBiTree(T->rchild);
    free(T);
    T=NULL;
    return OK;
    /********** End **********/
}

int BiTreeDepth(BiTree T)
//求二叉树T的深度
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T == NULL) return 0;
    return 1 + (BiTreeDepth(T->lchild)>=BiTreeDepth(T->rchild)? BiTreeDepth(T->lchild) : BiTreeDepth(T->rchild));
    /********** End **********/
}

BiTNode* LocateNode(BiTree T,KeyType e)
//查找结点
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T==NULL) return NULL;
    if(T->data.key==e) return T;
    BiTNode*left=LocateNode(T->lchild,e);
    if(left) return left;
    BiTNode*right=LocateNode(T->rchild,e);
    if(right) return right;
    return NULL;
    /********** End **********/
}

int mem[100]={0};
status to_mem(BiTree T)
{
    if(T == NULL) return OK;
    mem[T->data.key] = 1;
    to_mem(T->lchild);
    to_mem(T->rchild);
    return OK;
}

status Assign(BiTree &T,KeyType e,TElemType value)
//实现结点赋值。此题允许通过增加其它函数辅助实现本关任务
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    BiTNode* p=LocateNode(T,e);
    if(p==NULL || (value.key!=e && mem[value.key])) return ERROR;

    mem[e] = 0;
    mem[value.key] = 1;
    p->data=value;
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
    /*功能说明：e是和T中结点关键字类型相同的给定值，LR为0或1，c是待插入结点；根据LR为0或者1，插入结点c到T中，作为关键字为e的结点的左或右孩子结点，结点e的原有左子树或右子树则为结点c的右子树，返回OK。如果插入失败，返回ERROR。
特别地，当LR为-1时，作为根结点插入，原根结点作为c的右子树。*/
    if(T == NULL || e==c.key) return ERROR;
    BiTNode* New=(BiTNode *)malloc(sizeof(BiTNode));
    New->data = c;
    New->lchild = NULL;
    if(LR == -1)
    {
        New->rchild = T;
        T = New;
        return OK;
    }
    BiTNode* a=LocateNode(T,e);
    if(a == NULL) return ERROR;
    if(LR == 0)
    {
        New->rchild = a->lchild;
        a->lchild = New;
        return OK;
    }
    else if(LR == 1)
    {
        New->rchild = a->rchild;
        a->rchild = New;
        return OK;
    }
    else return ERROR;
    /********** End **********/
}

// BiTNode* findParent(BiTree T,KeyType e,int type){
//     if(T == NULL) return NULL;
//     if(T->data.key == e) { type=2; return NULL;}
//     if(T->lchild && T->lchild->data.key == e) { type = 0; return T;}
//     if(T->rchild && T->rchild->data.key == e) { type = 1; return T;}
//     BiTNode* left = findParent(T->lchild,e,type);
//     if(left) {type=0;return left;}
//     BiTNode* right = findParent(T->rchild,e,type);
//     if(right) {type=1;return right;}
//     return NULL;
// }

status DeleteNode(BiTree &T, KeyType e) {
    if(T == NULL) return ERROR;
    if(T->data.key == e) {
        BiTNode *del = T;
        if(T->lchild == NULL && T->rchild == NULL) {
            // 如果是根节点且无子树，清空为“空树”而不是销毁
            T->data.key = 0;
            T->data.others[0] = '\0';
            return OK;
        } else if(T->lchild == NULL) {
            T = T->rchild;
        } else if(T->rchild == NULL) {
            T = T->lchild;
        } else {
            BiTNode *p = T->lchild;
            while(p->rchild != NULL) p = p->rchild;
            p->rchild = T->rchild;
            T = T->lchild;
        }
        free(del);
        return OK;
    }
    if(T->lchild && DeleteNode(T->lchild, e) == OK) return OK;
    if(T->rchild && DeleteNode(T->rchild, e) == OK) return OK;
    return ERROR;
}

// status DeleteNode(BiTree &T,KeyType e)
// //删除结点。此题允许通过增加其它函数辅助实现本关任务
// {
//     // 请在这里补充代码，完成本关任务
//     /********** Begin *********/
//     if(T == NULL) return ERROR;
//     if(T->data.key == e) {
//         BiTNode *del = T;
//         if(T->lchild == NULL && T->rchild == NULL) {
//             T=NULL;
//         }
//         else if(T->lchild == NULL) {
//             T = T->rchild;
//         } else if(T->rchild == NULL) {
//             T = T->lchild;
//         } else {
//             BiTNode *p = T->lchild;
//             while(p->rchild != NULL) p = p->rchild;
//             p->rchild = T->rchild;
//             T = T->lchild;
//         }
//         free(del);
//         return OK;
//     }
//     if(T->lchild && DeleteNode(T->lchild, e) == OK) return OK;
//     if(T->rchild && DeleteNode(T->rchild, e) == OK) return OK;
//     return ERROR;
//     /********** End **********/
// }


int memo[1000]={0};
status PostOrderTraverse(BiTree T,void (*visit)(BiTree))
//后序遍历二叉树T
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T == NULL) return ERROR;
    BiTree stack[1000];
    int top = 0;
    stack[top++] = T;
    if(T->rchild) stack[top++]=T->rchild;
    if(T->lchild) stack[top++]=T->lchild;
    while(top > 0 ) {
    T = stack[top-1];
    int ldone = (T->lchild == NULL) ? 1 : memo[T->lchild->data.key];
    int rdone = (T->rchild == NULL) ? 1 : memo[T->rchild->data.key];
    if(ldone && rdone) {
        visit(T);
        memo[T->data.key]=1;
        top--;
        continue;
    }
    if(T->rchild) stack[top++] = T->rchild;
    if(T->lchild) stack[top++] = T->lchild;
}
    return OK;
    /********** End **********/
}
//出现段错误（Segmentation Fault）的原因
// 在访问T->rchild->data.key或T->lchild->data.key时，如果T->rchild或T->lchild为NULL，就会解引用空指针，导致段错误。

// 正确写法
// 在访问T->rchild->data.key或T->lchild->data.key前，必须先判断指针是否为NULL。

status LevelOrderTraverse(BiTree T,void (*visit)(BiTree))
//按层遍历二叉树T
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T == NULL) return ERROR;
    BiTree queue[1000];
    int front = 0, rear = 0;
    queue[rear++] = T;
    while(front < rear) {
        T = queue[front++];
        visit(T);
        if(T->lchild) queue[rear++] = T->lchild;
        if(T->rchild) queue[rear++] = T->rchild;
    }
    return OK;
    /********** End **********/
}

void SaveTreeNode(BiTree T, FILE* fp) {
    if(T == NULL) {
        TElemType temp = {-1, ""};
        fwrite(&temp, sizeof(TElemType), 1, fp);
        return;
    }
    fwrite(&T->data, sizeof(TElemType), 1, fp);
    SaveTreeNode(T->lchild, fp);
    SaveTreeNode(T->rchild, fp);
}
status SaveBiTree(BiTree T, char FileName[])
//将二叉树的结点数据写入到文件FileName中
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 1 *********/
    if(T==NULL){
        printf("二叉树不存在，无法保存！\n");
        return ERROR;
    }
    FILE *fp=fopen(FileName,"w");
    if(fp==NULL) {
        printf("文件打开失败！\n");
        return ERROR;
    }
    SaveTreeNode(T,fp);
    fclose(fp);
    printf("已保存到文件：%s\n",FileName);
    return OK;
    /********** End 1 **********/
}
status LoadTreeNode(BiTree &T,FILE* fp){
    TElemType temp;
    if(fread(&temp,sizeof(TElemType),1,fp)!=1) return ERROR;
    if(temp.key==-1){
        T=NULL;
        return OK;
    }
    T=(BiTNode*)malloc(sizeof(BiTNode));   
    T->data=temp;
    status lstatus=LoadTreeNode(T->lchild,fp);
    status rstatus=LoadTreeNode(T->rchild,fp);
    if(lstatus==OK && rstatus==OK) return OK;
    else return ERROR;
}
status LoadBiTree(BiTree &T,  char FileName[])
//读入文件FileName的结点数据，创建二叉树
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 2 *********/
    if(T != NULL)  printf("二叉树已存在，请先销毁!\n");
    FILE *fp=fopen(FileName,"r");
    if(!fp){
        printf("文件打开失败!\n");
        return ERROR;
    }
    status result=LoadTreeNode(T,fp);
    fclose(fp);
    if(result == OK){
        printf("二叉树创建成功！\n");
        return OK;
    }
    else{
        printf("二叉树创建失败！\n");
        return ERROR;
    }
    /********** End 2 **********/
}

status MaxPathSum(BiTree T){
    int max=0;
    int temp=0;
    if(T==NULL) return 0;
    if(T->lchild==NULL && T->rchild==NULL) return T->data.key;
    temp=MaxPathSum(T->lchild);
    if(temp+T->data.key>max) max=temp;
    temp=MaxPathSum(T->rchild);
    if(temp+T->data.key>max) max=temp;
    return max;
}

void InvertTree(BiTree &T) {
    if(T == NULL) return;
    BiTree temp = T->lchild;
    T->lchild = T->rchild;
    T->rchild = temp;
    InvertTree(T->lchild);
    InvertTree(T->rchild);
}

BiTNode* LowestCommonAncestor(BiTree T,KeyType e1,KeyType e2){
    if(T == NULL) return NULL;
    if(T->data.key == e1 || T->data.key == e2) return T;
    BiTNode* left = LowestCommonAncestor(T->lchild, e1, e2);
    BiTNode* right = LowestCommonAncestor(T->rchild, e1, e2);
    if(left && right) return T;
    return left ? left : right;
}
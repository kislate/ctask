#include "stdio.h"
#include "stdlib.h"
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType; //数据元素类型定义

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef int ElemType;
typedef struct LNode{  //单链表（链式结构）结点的定义
      ElemType data;
      struct LNode *next;
    }LNode,*LinkList;
FILE *fp;
char FileName[30];

status InitList(LinkList &L)
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
    if(L != NULL) //线性表已经存在
        return INFEASIBLE;
    L = (LinkList)malloc(sizeof(LNode)); 
    if(L != NULL)
        return OK; 
}

status DestroyList(LinkList &L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
    if(L == NULL) 
        return INFEASIBLE;
    LinkList p,q;
    p = L->next; //p指向第一个结点
    while(p != NULL) {
        q = p; //q指向当前结点
        p = p->next; 
        free(q); 
    }
    free(L); 
    L = NULL; //L置空
    return OK;
}

status ClearList(LinkList &L)
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
    if(L == NULL) 
        return INFEASIBLE;
    LinkList p,q;
    p = L->next; //p指向第一个结点
    while(p != NULL) {
        q = p; //q指向当前结点
        p = p->next; 
        free(q); 
    }
    L->next = NULL; //清空线性表
    return OK;
}

status ListEmpty(LinkList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
    if (L == NULL) 
        return INFEASIBLE;
    if (L->next == NULL)
        return TRUE; //线性表为空
    else
        return FALSE; //线性表不为空
}

status ListLength(LinkList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
    if (L == NULL) 
        return INFEASIBLE;
    int length = 0; 
    LinkList p = L->next; 
    while(p!=NULL){
        length++; 
        p = p->next;
    }
    return length;
}

status GetElem(LinkList L,int i,ElemType &e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L == NULL)
        return INFEASIBLE;
    else if(i < 1 || i > ListLength(L)) 
        return ERROR; 
    else {
        LinkList p=L->next;
        while(--i) p=p->next; 
        e = p->data; 
        return OK;  
    }
}

status LocateElem(LinkList L,ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
{
    if(L == NULL)
        return INFEASIBLE;
    LinkList p = L->next;
    int i = 1;
    while( p!= NULL){
        if(p->data == e)
            return i;
        p = p->next;
        i++;
    }
    return ERROR; 
}

status PriorElem(LinkList L,ElemType e,ElemType &pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L == NULL)
        return INFEASIBLE;
    if(L->next == NULL || L->next->next == NULL)
        return ERROR; //线性表为空或只有一个元素，没有前驱
    LinkList p = L->next;
    while(p->next != NULL) {
        if(p->next->data == e) {
            pre = p->data; 
            return OK;
        }
        p = p->next; 
    }
    return ERROR; 
}

status NextElem(LinkList L,ElemType e,ElemType &next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L == NULL)
        return INFEASIBLE;
    if(L->next == NULL || L->next->next == NULL)
        return ERROR; //线性表为空或只有一个元素，没有后继
    LinkList p = L->next;
    while(p->next != NULL) {
        if(p->data == e) {
            next = p->next->data; 
            return OK;
        }
        p = p->next; 
    }
    return ERROR;
}

status ListInsert(LinkList &L,int i,ElemType e)
// 如果线性表L存在，将元素e插入到线性表L成为第i个元素，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L == NULL)
        return INFEASIBLE;
    if(i < 1 || i > ListLength(L)+1)
        return ERROR;
    LinkList p = L; //p指向头结点
    for(int j = 1; j < i; j++) 
        p = p->next; 
    LinkList s = (LinkList)malloc(sizeof(LNode)); //创建新结点
    s->data = e;
    s->next = p->next; 
    p->next = s; 
    return OK;
}

status ListDelete(LinkList &L,int i,ElemType &e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L == NULL)
        return INFEASIBLE;
    if(i < 1 || i > ListLength(L))
        return ERROR;
    LinkList p = L; 
    while(--i) 
        p = p->next;
    LinkList q = p->next; //q指向要删除的结点
    p->next = q->next; 
    e = q->data; 
    free(q); 
    return OK;
}

status ListTraverse(LinkList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    if(L == NULL)
        return INFEASIBLE;
    LinkList p = L->next;
    while( p != NULL){
        if(p->next != NULL) 
            printf("%d ",p->data); 
        else
            printf("%d",p->data); 
        p = p->next; 
    }
    return OK;
}

status SaveList(LinkList L,char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    if(L == NULL)
        return INFEASIBLE;
    fp = fopen(FileName,"w"); 
    LinkList p = L->next; 
    for(; p != NULL ; p = p->next) 
        fprintf(fp, "%d ", p->data); 
    fclose(fp); 
    return OK; 
}

status LoadList(LinkList &L,char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
    if(L != NULL)
        return INFEASIBLE;
    fp = fopen(FileName,"r");
    L = (LinkList)malloc(sizeof(LNode)); 
    L->next = NULL;
    LinkList p = L;
    ElemType e;
    while(fscanf(fp, "%d", &e) != EOF) {
        LinkList s = (LinkList)malloc(sizeof(LNode)); 
        s->data = e; 
        s->next = NULL; 
        p->next = s; 
        p = s; 
    }
    fclose(fp);
    return OK;
}
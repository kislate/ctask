/*
任务描述
本关任务：设以带头结点的双向循环链表表示线性表L=（a1，a2，...，an），试编写一个时间复杂度为O(n)的算法，将L改变成L=（a1，a3，...，an，...，a4，a2）。
相关定义如下：
typedef int ElemType;
typedef  struct  Dnode
    {
        ElemType     data;
        struct  Dnode  * prior, * next;
    }  * DuLinkList;
函数原型：void  adjust(DuLinkList  L);

相关知识
为了完成本关任务，你需要掌握：1.线性表的物理结构，2.双向循环链表的插入与删除。

编程要求
根据提示，在右侧编辑器补充代码，写出函数 void  adjust(DuLinkList  L) 的定义。

测试说明
平台会自动读取输入数据，对你编写的代码进行测试，并输出结果。

测试输入：6 
         1 2 3 4 5 6
预期输出：1 3 5 6 4 2

测试输入：11
                  2 11 3 5 7 6 12 13 8 9 20 
预期输出：2 3 7 12 8 20 9 13 6 5 11

开始你的任务吧，祝你成功！*/
#include <stdio.h>
#include <stdlib.h>
typedef int ElemType;
typedef  struct  Dnode
    {
        ElemType     data;
        struct  Dnode *prior,*next;
    } *DuLinkList;
/*void  adjust(DuLinkList  L)
{
/**********Begin**********/
Dnode *oddlist, *evenlist, *p, *q;
/*初始化头节点*//*
oddlist = (Dnode *)malloc(sizeof(Dnode));
evenlist = (Dnode *)malloc(sizeof(Dnode));
oddlist->next = oddlist;
evenlist->next = evenlist;
oddlist->prior = oddlist;
evenlist->prior = evenlist;
p = L->next;
int cnt = 1;
while (p != L)
{
    if(cnt % 2 == 1){
        oddlist->prior->next = p;
        p->prior = oddlist->prior;
        oddlist->prior = p;
        p->next = oddlist;
    }
    else{
        p->next = evenlist->next;
        p->next->prior = p;
        evenlist->next = p;
        p->prior = evenlist;
    }
    cnt++;
    p = p->next;
}
    L->next = oddlist->next;
    oddlist->next->prior = L;
    oddlist->prior->next = evenlist->next;
    evenlist->next->prior = oddlist->prior;
    L->prior = evenlist->prior;
    evenlist->prior->next = L;

/**********End**********/
/*}*/
void adjust(DuLinkList L) {
/**********Begin**********/
    if (L == NULL || L->next == L || L->next->next == L) {
        return;  // 链表为空或只有一个元素时，不需要调整
    }

    DuLinkList oddlist, evenlist, oddtail, eventail;
    oddlist = (DuLinkList)malloc(sizeof(struct Dnode));
    evenlist = (DuLinkList)malloc(sizeof(struct Dnode));
    oddtail = oddlist;
    eventail = evenlist;

    oddlist->next = oddlist;
    evenlist->next = evenlist;
    oddlist->prior = oddlist;
    evenlist->prior = evenlist;

    DuLinkList p = L->next;
    int cnt = 1;
    // 遍历链表，将奇数位置节点和偶数位置节点分别存入两个链表
    while (p != L) {
        DuLinkList next = p->next;  // 保存下一个节点
        if (cnt % 2 == 1) {  // 奇数位置节点
            oddtail->next = p;
            p->prior = oddtail;
            oddtail = p;
        } else {  // 偶数位置节点
            eventail->prior = p;
            p->next = eventail;
            eventail = p;
        }
        cnt++;
        p = next;  // 移动到下一个节点
    }

    // 合并
    oddtail->next = eventail;
    eventail->prior = oddtail;
    L->next = oddlist->next;
    oddlist->next->prior = L;
    evenlist->prior->next = L;
    L->prior = eventail->prior;
    //oddtail->next = evenlist->next;
    //if (evenlist->next != L) {
    //    evenlist->next->prior = oddtail;
    //}
    /* evenlist->prior->next = L;
    L->prior = eventail->prior;
    L->next = oddlist->next;
    oddlist->next->prior = L;
    */
    //eventail->next = L;
    //L->prior = eventail;
    free(oddlist);
    free(evenlist);
/**********End**********/
}

int main()
{
    DuLinkList L,p,tail;
    int n,i;
    L=tail=(DuLinkList)malloc(sizeof(struct Dnode));
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        p=(DuLinkList)malloc(sizeof(struct Dnode));
        scanf("%d",&p->data);
        tail->next=p;
        p->prior=tail;
        tail=p;
    }
    L->prior=tail;
    tail->next=L;
    adjust(L);
    p=L->next;
    while(p!=L)
    {
        printf(" %d",p->data);
        p=p->next;
    }
}

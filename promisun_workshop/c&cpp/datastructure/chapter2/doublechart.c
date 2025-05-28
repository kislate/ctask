// 设以带头结点的双向循环链表表示线性表L=（a1，a2，...，an），试编写一个时间复杂度为O(n)的算法，将L改变成L=（a1，a3，...，an，...，a4，a2）。
// 相关定义如下：
// typedef int ElemType;
// typedef  struct  Dnode
//     {
//         ElemType     data;
//         struct  Dnode  * prior, * next;
//     }  * DuLinkList;
// 函数原型：void  adjust(DuLinkList  L);

// 相关知识
// 为了完成本关任务，你需要掌握：1.线性表的物理结构，2.双向循环链表的插入与删除。

// 编程要求
// 根据提示，在右侧编辑器补充代码，写出函数 void  adjust(DuLinkList  L) 的定义。

// 测试说明
// 平台会自动读取输入数据，对你编写的代码进行测试，并输出结果。

// 测试输入：6 
//                  1 2 3 4 5 6
// 预期输出：1 3 5 6 4 2

// 测试输入：11
//                   2 11 3 5 7 6 12 13 8 9 20 
// 预期输出：2 3 7 12 8 20 9 13 6 5 11
#include <stdio.h>
#include <stdlib.h>
typedef int ElemType;
typedef  struct  Dnode
    {
        ElemType     data;
        struct  Dnode *prior,*next;
    } *DuLinkList;
void adjust(DuLinkList L) {
    int flag=1;
    DuLinkList p=L->next,q;
    q=p->next;
    L->prior=q;
    do{
        p->next=q->next;
        q->next->prior=p;
        p=q->next;//p=p->next;
        if(p->next==L) {
            flag=2;    
            break;
        }//奇数 终止 
        q->prior=p->next;
        if(p->next->next==L) flag=0;//偶数 终止 
        p->next->next=q;
        q=p->next;//q=q->prior;
    }while(flag);
    if(flag==2) {
        p->next=q;
        q->prior=p;
    }
    L->prior->next=L;
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



    // DuLinkList odd = L->next;  // 奇数位置节点
    // DuLinkList even = odd->next;  // 偶数位置节点
    // DuLinkList evenHead = even;  // 保存偶数链表的头节点

    // // 分离奇数和偶数位置的节点
    // while (even != L && even->next != L) {
    //     odd->next = even->next;
    //     odd->next->prior = odd;
    //     odd = odd->next;

    //     even->next = odd->next;
    //     even->next->prior = even;
    //     even = even->next;
    // }

    // // 连接奇数链表和偶数链表
    // odd->next = evenHead;
    // evenHead->prior = odd;

    // // 修复偶数链表的尾节点指向头节点
    // if (even != L) {
    //     even->next = L;
    //     L->prior = even;
    // } else {
    //     odd->next = L;
    //     L->prior = odd;
    // }
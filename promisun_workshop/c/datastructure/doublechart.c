
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
void  adjust(DuLinkList  L)
{
/**********Begin**********/


 /**********End**********/
}
#include <stdio.h>
#include <stdlib.h>
typedef int ElemType;
typedef  struct  Dnode
    {
        ElemType     data;
        struct  Dnode *prior,*next;
    } *DuLinkList;

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
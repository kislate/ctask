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
void  adjust(DuLinkList  L)
{
/**********Begin**********/
// 采用先分别存储然后合并的策略
    DuLinkList evenHead = (DuLinkList)malloc(sizeof(Dnode));
    DuLinkList oddHead = (DuLinkList)malloc(sizeof(Dnode));
    DuLinkList evenTail = evenHead;
    DuLinkList oddTail = oddHead;
    DuLinkList p = L->next;
    int cnt = 1;
    while(p != L) {
        if(cnt % 2 == 0) {
            evenTail->next = p;
            p->prior = evenTail;
            evenTail = p;
        } else {
            oddTail->prior = p;
            p->next = oddTail;
            oddTail = p;
        }
        p = p->next;
        cnt++;
    }
    oddHead->next->prior = L;
    L->next = oddHead->next;
    evenHead->prior->next = L;
    L->prior = evenHead->prior;
    free(evenHead);
    free(oddHead);
    evenHead = NULL;
    oddHead = NULL;
/**********End**********/
}

void adjust(DuLinkList L) {
    /**********Begin**********/
    // 采用先分别存储然后合并的策略
        if (L == NULL || L->next == L) {
            return;
        }
    
        DuLinkList evenHead = (DuLinkList)malloc(sizeof(Dnode));// 偶数
        DuLinkList oddHead = (DuLinkList)malloc(sizeof(Dnode));// 奇数
        evenHead->next = evenHead->prior = evenHead;
        oddHead->next = oddHead->prior = oddHead;
    
        DuLinkList p = L->next;
        int cnt = 1;
    
        while (p != L) {
            DuLinkList nextNode = p->next;
            if (!cnt) {
                p->next = evenHead->next;
                p->prior = evenHead;
                evenHead->next->prior = p;
                evenHead->next = p;
            } else {
                p->prior = oddHead->prior;
                p->next = oddHead;
                oddHead->prior->next = p;
                oddHead->prior = p;
            }
            p = nextNode;
            cnt^=1;
        }
    
        if (oddHead->next != oddHead) {
            L->next = oddHead->next;
            oddHead->next->prior = L;
        }
        if (evenHead->next != evenHead) {
            oddHead->prior->next = evenHead->next;
            evenHead->next->prior = oddHead->prior;
            evenHead->prior->next = L;
            L->prior = evenHead->prior;
        }
    
        free(evenHead);
        free(oddHead);
        evenHead = NULL;
        oddHead = NULL;
    /**********End**********/
    }

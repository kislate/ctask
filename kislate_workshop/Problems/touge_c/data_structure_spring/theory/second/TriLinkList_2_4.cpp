/*
任务描述
本关任务：已知A、B和C为3个递增有序的线性表，现要求对A表做如下操作，删除那些既在B中出现，也在C中出现的元素。以带表头结点的单链表作为线性表的物理结构，编写实现上述操作的算法。
函数原型：void  TriLinkList(LinkList  A,LinkList  B,LinkList  C)；

相关知识
为了完成本关任务，你需要掌握：1.线性表，2.顺序表。
相关定义：
typedef int ElemType;
typedef struct node
   { 
        ElemType data;
        struct node *next;
   } NODE, *LinkList;

编程要求
根据提示，在右侧编辑器补充代码，完成函数TriLinkList(LinkList  A,LinkList  B,LinkList  C)。要求算法效率尽可能高。

测试说明
平台会自动读取输入三个线性表的数据，对你编写的代码进行测试，并输出结果。

测试输入：1  3  5  7  9  10  11  12  20  0
                 3  9  10  11  30 0
                 3  6  7  9 11  13  50  0
预期输出：1  5  7  10  12  20

开始你的任务吧，祝你成功！
*/
#include<stdio.h>
#include<stdlib.h>
typedef int ElemType;
typedef struct node
{ ElemType data;
    struct node *next;
} NODE,*LinkList;
void TriLinkList(LinkList  A,LinkList  B,LinkList  C)
{
/**********Begin**********/
// 延用顺序表的简单实现方式
LinkList p = A, q = B->next, r = C->next, temp;
while(p->next != NULL)
{
    while(q != NULL && q->data < p->next->data) q = q->next;
    while(r != NULL && r->data < p->next->data) r = r->next;
    if(q != NULL && r != NULL && q->data == p->next->data && r->data == p->next->data)
    {
        temp = p->next;
        p->next = temp->next;
        free(temp);
    }
    else
    {
        p = p->next;
    }
}   
/**********End**********/
}
int main()
{
    LinkList L[3],p;
    ElemType x;
    int i;
    for(i=0;i<3;i++)
    {
    	L[i]=p=(NODE *)malloc(sizeof(NODE));
    	scanf("%d",&x);
    	while (x)
    	{
				p->next=(NODE *)malloc(sizeof(NODE));
				p=p->next;
				p->data=x;
				scanf("%d",&x);
    	}
      p->next=NULL;
    }
    TriLinkList(L[0],L[1],L[2]);
    for(p=L[0]->next;p;p=p->next)
        printf(" %d",p->data);
	return 0;
}


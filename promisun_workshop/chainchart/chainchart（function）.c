/*本关任务：编程实现
（1）用一个单向链表接收一个长字符串，且每个节点接收一个字符，遍历输出链表中的所有字符，并将字符串无冗余地存放到一个动态存储分配的的字符数组中，并且输出该字符串。（本题暂不考虑空字符串情况）(结尾以回车结束)
（2）再输入一个字符，如果该字符已在链表中，则删除该结点，否则在输入字符和结点的数据域字符差值最小的结点后面插入包含该字符的结点，输出最后的字符串。

要求：采用模块化设计方法，将创建链表、遍历链表、删除结点、插入结点等功能用函数实现。

测试说明
平台会对你编写的代码进行测试，若是与预期输出相同，则算通关。

测试输入：
qwertyuiopasdfghjkl
i
预期输出：
q w e r t y u i o p a s d f g h j k l
qwertyuiopasdfghjkl
qwertyuopasdfghjkl

测试输入：
qwertyuiopasdfghjkl
q
预期输出：
q w e r t y u i o p a s d f g h j k l
qwertyuiopasdfghjkl
wertyuiopasdfghjkl

测试输入：
qwer1234?@%
5
预期输出：
q w e r 1 2 3 4 ? @ %
qwer1234?@%
qwer12345?@%

开始你的任务吧，祝你成功！  *///该题没讲清楚删结点是把所有相同或相近字符的结点都删掉还是只删一个(该程序只删一个)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
struct Node
{
    char value;
    struct Node *next;
};
typedef struct Node node;

node * createList(void);//创建链表(尾插法)
void addback(node *q,char c);//尾部加节点
node *operateSimilar(node *phead,char c);//找到链表中与c最接近的结点并操作
void printList(node *phead);//遍历链表
node * deleteNode(node* p,node *phead);//删除结点

int main()
{
    node *phead=createList();
    char c;
    scanf(" %c",&c);//防止前导空格影响

    node *p=phead;
    for(;p!=NULL;p=p->next)
        printf("%c ",p->value);
    printf("\n");
    printList(phead);
    
    phead=operateSimilar(phead,c);
    printList(phead);
    
    return 0;
}

node *createList(void)
{
    node *head=NULL,*p,*tail=NULL;
    char c;
    while((c=getchar())!='\n')
    {
        p=(node*)malloc(sizeof(node));
        p->value=c;
        if(head==NULL)
            head=p;//首结点插入空表
        else
            tail->next=p;//其余结点插入尾部
        tail=p;//尾插法
    }
    if (tail != NULL) {
        tail->next = NULL;
    }
    return head;
}

void printList(node *phead)
{
    node *p=phead;
    for(;p!=NULL;p=p->next)
        printf("%c",p->value);
    printf("\n");
}

node *operateSimilar(node *phead,char c)//
{
    node  *p=phead,*q=NULL,*last=NULL;//q标记最近点,便于添加操作;last指向p的前一个结点,便于删除操作
    int min=100;

    for(;p!=NULL&&p->value!=c;)
    {
        last = p;
        if(abs(p->value-c)<min)
        {
            min=abs(p->value-c);
            q=p;
        }
        p=p->next;
    } 
    if(p==NULL) addback(q,c);//没找到
    else 
    {
        return deleteNode(last,phead);
    }
    return phead;
}

node* deleteNode(node* p,node *phead)
{
    if(p==NULL) //说明头部即要删去的结点
    {
        node *q=phead;
        phead=phead->next;
        free(q);
        return phead;
    }
    node *temp = p->next;
    p->next = p->next->next;
    free(temp);//free不能直接free（p->next）否则会出错
    return phead;
}

void addback(node *q,char c)
{
    node *p=(node*)malloc(sizeof(node));
    p->value=c;
    p->next=q->next;
    q->next=p;
}
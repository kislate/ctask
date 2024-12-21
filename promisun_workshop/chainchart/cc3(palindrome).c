/*本关任务：
回文字符串是正读和反读都相同的字符串，例如“abba”和“abcba”是回文字符串。设计程序判断输入的任意长度的字符串是否为回文字符串。
提示：由于要求字符串长度任意，所以用单链表存储字符串，即判断一个单链表是否为回文链表。

编程要求
根据题目要求，在右侧编辑器中两个函数的算法设计。

void createLinkList(C_NODE **headp, char s[]) 根据字符串s构造单链表，得到一个以单链表表示的字符串，单链表结点定义见右侧编辑器。
void judgePalindrome(C_NODE *head) 判断以head为头指针的单链表表示的字符串是否为回文，是则显示true，否则显示false。
测试说明
平台会对你编写的代码进行测试：

测试输入1：
ababa
预期输出1：
true

测试输入2：
race a car
预期输出2：
false

测试输入2：
happycoding!
预期输出2：
false

开始你的任务吧，祝你成功！*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct c_node{
    char data;
    struct c_node *next;
} C_NODE;   
int main()  
{
    char s[1000],*pc=s;
    int len=0;
    C_NODE *head=NULL,*p;
    scanf("%[^\n]",s);
    createLinkList(&head,s);   
    for(p=head;p;p=p->next) len++;
    if (len!=strlen(s)) { printf("单链表长度不正确");return 1;}
    else for(p=head;p;p=p->next)
        if (p->data!=*pc++) { printf("单链表有错误结点");return 1;}
    judgePalindrome(head);
    return 1;
}

/*测试程序定义了如下结点类型
typedef struct c_node{
    char data;  struct c_node *next;
} C_NODE;*/

void createLinkList(C_NODE **headp, char s[]) 
{
    int i=0;
    C_NODE *head=NULL,*p,*tail=NULL;
    while(s[i]!='\0'&&s[i]!='\n')
    {
        p=(C_NODE*)malloc(sizeof(C_NODE));
        p->data=s[i++];
        if(head==NULL)
            head=p;//首结点插入空表
        else
            tail->next=p;//其余结点插入尾部
        tail=p;//尾插法
    }
    if (tail != NULL) {
        tail->next = NULL;
    }
    *headp=head;
}

void judgePalindrome(C_NODE *head)
{
/************************************* BEGIN *******************************************/
    C_NODE *s,*t;
    int len=0;
    for(s=head;s;s=s->next) len++;
    s=head;
    if(len%2)
        for(int i=0;i<=len/2;i++)
            s=s->next;
    else
        for(int i=0;i<len/2;i++)
            s=s->next;
    t=s;
    for(int i=1,j=len/2-1;i<=len/2;i++,j--)
    {
        s=head;
        for(int m=0;m<j;m++) s=s->next;//找到对应位置
        if(s->data!=t->data)
        {
            printf("false\n");
            return;
        }
        t=t->next;
    }
    printf("true\n");

/************************************* BEGIN *******************************************/
}

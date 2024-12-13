
#include "stdio.h"
#include "string.h"
typedef struct c_node{
    char data;
    struct c_node *next;
} C_NODE;    
#include "stu.h"
int main()  
{
char s[1000],*pc=s;
int len=0;
C_NODE *head,*p;
scanf("%[^\n]",s);
createLinkList(&head,s);   
for(p=head;p;p=p->next) len++;
if (len!=strlen(s)) { printf("单链表长度不正确");return 1;}
else for(p=head;p;p=p->next)
        if (p->data!=*pc++) { printf("单链表有错误结点");return 1;}
judgePalindrome(head);//这个东西是有毛病啊？
return 1;
}





/************************************* BEGIN *******************************************/


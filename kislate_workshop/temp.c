/*任务描述
实验教材P207 程序设计 第（9）题
本关任务：
利用值栈对逆波兰表达式进行求值。逆波兰表达式从键盘输入，其中的运算符仅包含加、减、乘、除4种运算，表达式中的数都是十进制数，用换行符结束输入。由于逆波兰表达式的长度不限，所以值栈要用后进先出链表实现。

编程要求
根据题目要求，在右侧编辑器中完成程序设计。

测试说明
平台会对你编写的代码进行测试：

测试输入：
2  1  +  3  *
预期输出：
9
解释:
该算式转化为常见的中缀算术表达式为：((2 + 1) * 3) = 9

测试输入：
4  13  5  /  +
预期输出：
6
解释: 该算式转化为常见的中缀算术表达式为：(4 + (13 / 5)) = 6

开始你的任务吧，祝你成功！*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct c_node{
    char data;
    struct c_node *next;
}C_NODE;
void createLinkList(C_NODE **head,char *s);
int BolanLinkList(C_NODE *head);
int main(void)
{   
    char s[1000];
    scanf("%[^\n]",s);
    C_NODE *head,*p;
    *head = *p =NULL;
    creatLinkList(&head,s);
    BolanLinkList(head);
}

void createLinkList(C_NODE **head,char *s)
{
    C_NODE *p_new;
    C_NODE *p_mov = *head;
    while(*s != '\0')
    {
        p_new = (C_NODE*)malloc(sizeof(C_NODE));
        p_new->data = *s;
        p_new->next = NULL;
        if(*head == NULL)
        {
            *head = p_new;
        }
        else 
        {
            p_mov->next = p_new;
        }
        p_mov = p_new;//如果是p_mov = p_mov->next;的话那么在第一个节点的时候就会出现问题，
        //因为一开始p_mov是NULL;然后*head所指向的地方发生了变化，但是p_mov没有发生变化，所以在第一个节点的时候就会出现问题
        s++;
    }
}

int BolanLinkList(C_NODE *head)
{
    C_NODE *start,*p_mov,*p_mark;
    p_mov = start = head;
    
    for(p_mov = head;p_mov != NULL;p_mov = p_mov->next)
    {
        if(p_mov->data == '+')
        {
            int num1 ,num2;
            num1 = 0; num2 = 0;
            int sum =0;
            for(p_mark=head;p_mark->next !=p_mov;p_mark = p_mark->next);
            for(start = head;start->next != p_mark;start = start->next);
            num1 += start->data - '0';
            for(p_mark=head;p_mark->next !=p_mark;p_mark = p_mark->next)
        }
    }
}
//表达式的值
#include <stdio.h>
int main()
{
    char u[]="UVWXYZ",v[]="xyz";
    struct T
    {
        int x;
        char c;
        char *t;
    } a[]={{11,'A',u},{100,'B',v}},*p=a;
    int n;
    scanf("%d",&n);
    switch (n)
    {
    case 1:
        printf("%d\n",(++p)->x);
        break;
    case 2:
        p++;
        printf("%c\n",p->c);
        break;
    case 3:
        printf("%c\n",*p++->t);
        printf("%c\n",*p->t);
        break;
    case 4:
        printf("%c\n",*(++p)->t);
        break;
    case 5:
        printf("%c\n",*++p->t);
        break;
    case 6:
        printf("%c\n",++*p->t);
        break;
    default:
        break;
    }
    return 0;
}


//程序改错与调试
#include <stdio.h>
#include <stdlib.h>
struct s_list{
    int data;
    struct s_list *next;
};
void create_list(struct s_list **headp,int *p);
int main(void){
    struct s_list *head=NULL,*p;
    int s[]={1,2,3,4,5,6,7,8,0};
    create_list(&head,s);//传指针地址以改变指针的值
    p=head;
    while (p){
        printf("%d\t",p->data);
        p=p->next;
    }
    printf("\n");
    return 0;  
}
//先进先出创建链表
void create_list(struct s_list **headp,int *p)//headp是指向指针的指针，p是指向数组的指针，要改指针则应该传指针地址，故用**headp
{
    struct s_list *loc_head=NULL,*tail;
    if(p[0]==0);
    else {
        loc_head=(struct s_list *)malloc(sizeof(struct s_list));
        loc_head->data=*p++;
        tail=loc_head;
        while (*p)
        {
            tail->next=(struct s_list *)malloc(sizeof(struct s_list));
            tail=tail->next;
            tail->data=*p++;
        }
        tail->next=NULL;
        
    }
    *headp=loc_head;
}

//后进先出创建链表
void create_list(struct s_list **headp,int *p)//headp是指向指针的指针，p是指向数组的指针，要改指针则应该传指针地址，故用**headp
{
    struct s_list *loc_head=NULL,*s;
    while (*p)
    {
        s=(struct s_list *)malloc(sizeof(struct s_list));
        s->data=*p++;
        s->next=loc_head; //新结点指向原首结点
        loc_head=s;       //新节点成为首结点 
    }
    *headp=loc_head;
}

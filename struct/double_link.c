#include <stdio.h>
#include <stdlib.h>
 
//定义结点结构体
typedef struct student
{
    //数据域
    int num;		//学号
    int score;      //分数
    char name[20];  //姓名
 
    //指针域
    struct student *front;  //保存上一个结点的地址
    struct student *next;   //保存下一个结点的地址
}STU;
 
void double_link_creat_head(STU **p_head,STU *p_new)
{
    STU *p_mov=*p_head;
    if(*p_head==NULL)				//当第一次加入链表为空时，head执行p_new
    {
        *p_head = p_new;
        p_new->front = NULL;
        p_new->next = NULL;
    }
    else	//第二次及以后加入链表
    {
        while(p_mov->next!=NULL)
        {
            p_mov=p_mov->next;	//找到原有链表的最后一个节点
        }
        p_mov->next = p_new;		//将新申请的节点加入链表
        p_new->front = p_mov;
        p_new->next = NULL;
    }
}
 
 
void double_link_print(STU *head)
{
    STU *pb;
    pb=head;
    while(pb->next!=NULL)
    {
        printf("num=%d score=%d name:%s\n",pb->num,pb->score,pb->name);
        pb=pb->next;
    }
    printf("num=%d score=%d name:%s\n",pb->num,pb->score,pb->name);
 
    printf("***********************\n");
 
    while(pb!=NULL)
    {
        printf("num=%d score=%d name:%s\n",pb->num,pb->score,pb->name);
        pb=pb->front;
    }
}
 
//双向链表的删除
void double_link_delete_num(STU **p_head,int num)
{
    STU *pb,*pf;
    pb=*p_head;
    if(*p_head==NULL)//链表为空，不需要删除
    {
        printf("链表为空，没有您要删除的节点\n");
        return ;
    }
    while((pb->num != num) && (pb->next != NULL) )
    {
        pb=pb->next;
    }
    if(pb->num == num)//找到了一个节点的num和num相同，删除pb指向的节点
    {
        if(pb == *p_head)//找到的节点是头节点
        {
            if((*p_head)->next==NULL)//只有一个节点的情况
            {
                *p_head=pb->next;
            }
            else//有多个节点的情况
            {
                *p_head = pb->next;//main函数中的head指向下个节点
                (*p_head)->front=NULL;
            }
        }
        else//要删的节点是其他节点
        {
            if(pb->next!=NULL)//删除中间节点
            {
                pf=pb->front;//让pf指向找到的节点的前一个节点
                pf->next=pb->next; //前一个结点的next保存后一个结点的地址
                (pb->next)->front=pf; //后一个结点的front保存前一个结点的地址
            }
            else//删除尾节点
            {
                pf=pb->front;
                pf->next=NULL;
            }
        }
 
        free(pb);//释放找到的节点
 
    }
    else//没找到
    {
        printf("没有您要删除的节点\n");
    }
}
 
int main()
{
    STU *head=NULL,*p_new=NULL;
    int num,i;
    printf("请输入链表初始个数:\n");
    scanf("%d",&num);
    for(i=0;i<num;i++)
    {
        p_new=(STU*)malloc(sizeof(STU));//申请一个新节点
        printf("请输入学号、分数、名字:\n");	//给新节点赋值
        scanf("%d %d %s",&p_new->num,&p_new->score,p_new->name);
        double_link_creat_head(&head,p_new);	//将新节点加入链表
    }
 
    double_link_print(head);
 
    printf("请输入您要删除的节点的num\n");
    scanf("%d",&num);
    double_link_delete_num(&head,num);
    double_link_print(head);
 
}
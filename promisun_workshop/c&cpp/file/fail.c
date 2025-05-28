//文件操作失败了，不知道为什么
//。。。。。。


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Data
{
    char id[15];
    char name[10];
    int eng;
    int math;
    int phy;
    int c;
    float average;
};
typedef struct Data data;
struct student
{
    data student_data;
    struct student *next;
};
typedef struct student stu;
stu *createList(stu *phead);//输入信息
void printList(stu *phead);//输出信息
void modify(stu *phead);//修改信息
void average(stu *phead);//计算平均成绩并输出
void printNewList(stu *phead);//输出新信息
void sort1(stu *phead);
void free1(stu **phead);//释放链表
void link_creat_head(stu **p_head,stu *p_new);
FILE*fp;

int main()
{
    stu *phead=NULL;
    int n;
    scanf("%d",&n);
    while(n)
    {
        switch (n)
        {
        case 1:
            phead=createList(phead);
            break;
        case 2:
            sort1(phead);
            printList(phead);
            break;
        case 3:
            modify(phead);
            break;
        case 4:
            sort1(phead);
            average(phead);
            break;
        case 5:
            sort1(phead);
            printNewList(phead);
            break;
        case 6:
            if(!(fp=fopen("stu.dat","wb+")))
            {
                printf("Can't open file!\n");
                exit(-1);
            }
            stu *pm = phead;
            while(pm==NULL)
            {
                fwrite(pm,sizeof(stu),1,fp);
                pm = pm->next;
            }
            fclose(fp);
            fflush(stdin);
            break;
        case 7:
            if(!(fp=fopen("stu.dat","rb")))
            {
                printf("Can't open file!\n");
                exit(-1);
            }
            free1(&phead);
            stu *pn= (stu*)malloc(sizeof(stu));
            pn = (stu*)malloc(sizeof(stu));
            while(fread(pn,sizeof(stu),1,fp))
            {
                link_creat_head(&phead,pn);
                pn = (stu*)malloc(sizeof(stu));
            }
            fclose(fp);
            break;
        }
        scanf("%d",&n);
    }
    return 0;
}


stu * createList(stu *phead)
{
    stu *s=phead,*p,*tail=NULL;//s是新链头指针(其遍历是为了让其成为已输入链表的尾部，即延长的头部），p是新结点，tail是尾指针
    int n;//输入学生人数
    int flag=1;//flag记录头指针是否为空 ，0为空，1不为空
    if(!phead) flag=0;
    scanf("%d",&n);
    
    if(flag) for(;s->next!=NULL;s=s->next);//头指针不空才会有s->next 
    
    for(int i=0;i<n;i++)
    {
        p=(stu*)malloc(sizeof(stu));
        scanf(" %s %s %d %d %d %d", p->student_data.id, p->student_data.name, &p->student_data.eng, &p->student_data.math, &p->student_data.phy, &p->student_data.c);
        if(flag)//头指针不空才会有s->next ，延长链
        {
        	if(s->next==NULL)
            s->next=p;//首结点插入空表
        	else
            tail->next=p;//其余结点插入尾部
		}
		else//创建链
		{
			if(!s)
				s=p;
			else
				tail->next=p;
		}
        tail=p;//尾插法
    }
    if (tail != NULL) {
        tail->next = NULL;
    }
    if(!flag) return s;//此前无链表，返回新链表的头指针
    return phead;//此前有链表，返回原链表的头指针
}

void printList(stu *phead)
{
    stu *p=phead;
    for(;p!=NULL;p=p->next)
        printf("%s %s %d %d %d %d\n", p->student_data.id, p->student_data.name, p->student_data.eng, p->student_data.math, p->student_data.phy, p->student_data.c);
}

void modify(stu *phead)
{
    char id[15];
    int n;
    scanf("%s %d", id, &n);
    stu *p=phead;
    for(;p!=NULL;p=p->next)
    {
        if(strcmp(p->student_data.id, id)==0)
            break;
    }
    if(p==NULL)
    {
        printf("Not found!\n");
        return;
    }
    switch (n)
    {
    case 1:
        scanf("%d", &p->student_data.eng);
        break;
    case 2:
        scanf("%d", &p->student_data.math);
        break;
    case 3:
        scanf("%d", &p->student_data.phy);
        break;
    case 4:
        scanf("%d", &p->student_data.c);
        break;
    default:
        break;
    }
}

void average(stu *phead)
{
    stu *p=phead,*s=phead;
    for(;p!=NULL;p=p->next)
        p->student_data.average=1.00*(p->student_data.eng+p->student_data.math+p->student_data.phy+p->student_data.c)/4;
    for(;s!=NULL;s=s->next)
        printf("%s %s %.2f\n", s->student_data.id, s->student_data.name, s->student_data.average);
}

void printNewList(stu *phead)
{
    stu *p=phead;
    for(;p!=NULL;p=p->next)
        printf("%s %s %d %.2f\n", p->student_data.id, p->student_data.name, p->student_data.eng + p->student_data.math + p->student_data.phy + p->student_data.c, 1.00*(p->student_data.eng+p->student_data.math+p->student_data.phy+p->student_data.c)/4);
}

void sort1(stu *phead)//交换数据域进行升序排序
{
    stu *p=phead,*q;
    for(;p!=NULL;p=p->next)
    {
        for(q=p->next;q!=NULL;q=q->next)
        {
            if((p->student_data.eng + p->student_data.math + p->student_data.phy + p->student_data.c)>(q->student_data.eng + q->student_data.math + q->student_data.phy + q->student_data.c))
            {
                data temp=p->student_data;
                p->student_data=q->student_data;
                q->student_data=temp;
            }
        }
    }
}

void free1(stu **phead)
{
    stu *p=*phead;
    while(*phead!=NULL)
    {
        p=*phead;
        *phead=(*phead)->next;
        free(p);
        p=NULL;
    }
}

void link_creat_head(stu **p_head,stu *p_new)
{
    stu *p_mov = *p_head;
    if(*p_head == NULL)
    {
        *p_head = p_new;
        p_new->next = NULL;
    }
    else
    {
        while(p_mov->next!=NULL)
        {
            p_mov = p_mov->next;
        }
        p_mov->next = p_new;
        p_new->next = NULL;
    }
}

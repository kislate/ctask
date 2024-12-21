/*本关任务：
用单向链表建立一张班级成绩单，包括每个学生的学号、姓名、英语、高等数学、普通物理、C语言程序设计4门课程的成绩。
实现以下功能，并提供菜单选项：
0.退出
1.输入每个学生的各项信息
2.输出每个学生的各项信息
3.修改指定学生的指定数据项的内容：
    1.修改英语成绩
    2.修改高等数学成绩
    3.修改普通物理成绩
    4.修改C语言成绩
4.统计每个学生的平均成绩（保留2位小数）
5.输出各位学生的学号、姓名、4门课程的总成绩和平均成绩

(注意：每项功能可多次选择，例如，先选功能1，输入3个学生，后面又选功能1，输入2个学生，则此时共有5个学生，再选择功能5时，应该输出5个学生的信息。)

相关知识
为了完成本关任务，你需要掌握：1.结构体，2.链表。

编程要求
根据题目要求，在右侧编辑器完成程序设计。

测试说明
平台会对你编写的代码进行测试，输入为功能编号，：

测试输入：
依次输入功能编号1，学生数量n，每个学生的学号、姓名和成绩；功能编号2；功能编号3，指定学生的学号，修改的数据项，数据；功能编号4；功能编号5：
1    （功能编号）
4    （学生人数）
U202012345 Jack 99 100 80 96    （学号 姓名 英语 数学 物理 C语言成绩）
U202054321 Rose 89 94 85 100
U202056789 Tom 12 34 56 78
U202098765 Jerry 98 76 54 32
2    （功能编号）
3    （功能编号）
U202054321 1 66    （将学号为U202054321的同学的英语成绩修改为66）
4    （功能编号）
5    （功能编号）

预期输出：

U202012345 Jack 99 100 80 96
U202054321 Rose 89 94 85 100
U202056789 Tom 12 34 56 78
U202098765 Jerry 98 76 54 32
U202012345 Jack 93.75
U202054321 Rose 86.25
U202056789 Tom 45.00
U202098765 Jerry 65.00
U202012345 Jack 375 93.75
U202054321 Rose 345 86.25
U202056789 Tom 180 45.00
U202098765 Jerry 260 65.00

开始你的任务吧，祝你成功！*/

//(improve)增加按照平均成绩进行升序排序的函数，写出用交换结点数据域的方法升序排序的函数，排序可用选择法或冒泡法。

//(improve)进一步写出用交换结点指针域的方法升序排序的函数。
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
void sort1(stu *phead);//交换数据域进行升序排序
void sort2(stu *phead);//交换指针域进行升序排序

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
            printList(phead);
            break;
        case 3:
            modify(phead);
            break;
        case 4:
            average(phead);
            break;
        case 5:
            printNewList(phead);
            break;
        default:
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
    stu *p=phead;
    for(;p!=NULL;p=p->next)
        p->student_data.average=1.00*(p->student_data.eng+p->student_data.math+p->student_data.phy+p->student_data.c)/4;
}

void printNewList(stu *phead)
{
    stu *p=phead;
    for(;p!=NULL;p=p->next)
        printf("%s %s %d %.2f\n", p->student_data.id, p->student_data.name, p->student_data.eng + p->student_data.math + p->student_data.phy + p->student_data.c, p->student_data.average);
}

void sort1(stu *phead)//交换数据域进行升序排序
{
    stu *p=phead,*q;
    for(;p!=NULL;p=p->next)
    {
        for(q=p->next;q!=NULL;q=q->next)
        {
            if(p->student_data.average>q->student_data.average)
            {
                data temp=p->student_data;
                p->student_data=q->student_data;
                q->student_data=temp;
            }
        }
    }
}

void sort2(stu *phead)//交换指针域进行升序排序
{
    stu *p=phead,*q,*r;
    for(;p!=NULL;p=p->next)
    {
        for(q=p->next;q!=NULL;q=q->next)
        {
            if(p->student_data.average>q->student_data.average)
            {
                r=p->next;
                p->next=q->next;
                q->next=r;

                r=p;
                p=q;
                q=r;
            }
        }
    }
}//知道有问题，若pq相邻大概率会出现死循环

//机器人给的答案
void sort2(stu *phead)//交换指针域进行升序排序
{
    if (phead == NULL || phead->next == NULL) return;

    stu *sorted = NULL;
    stu *current = phead;
    while (current != NULL) {
        stu *next = current->next;
        if (sorted == NULL || sorted->student_data.average >= current->student_data.average) {
            current->next = sorted;
            sorted = current;
        } else {
            stu *temp = sorted;
            while (temp->next != NULL && temp->next->student_data.average < current->student_data.average) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    phead->next = sorted->next;
    phead->student_data = sorted->student_data;
}

//Q：**************************************************************
//原失败版本（无法延长链）why?why?why?若有原链L263的s应该为原链的尾部NULL啊，让其=p不就相当于延长了链吗？
stu * createList(stu *phead)
{
    stu *s=phead,*p,*tail=NULL;//s是新链头指针(其遍历是为了让其成为已输入链表的尾部，即延长的头部），p是新结点，tail是尾指针
    int n;//输入学生人数
    int flag=0;//flag记录头指针是否为空 ，0为空
    scanf("%d",&n);
    
    for(;s!=NULL;s=s->next,flag++);//flag=0说明headp=NULL
    
    for(int i=0;i<n;i++)
    {
        p=(stu*)malloc(sizeof(stu));
        scanf(" %s %s %d %d %d %d", p->student_data.id, p->student_data.name, &p->student_data.eng, &p->student_data.math, &p->student_data.phy, &p->student_data.c);
        if(s==NULL)
            s=p;//首结点插入空表
        else
            tail->next=p;//其余结点插入尾部
        tail=p;//尾插法
    }
    if (tail != NULL) {
        tail->next = NULL;
    }
    if(!flag) return s;//此前无链表，返回新链表的头指针
    return phead;//此前有链表，返回原链表的头指针
}

//bible头歌出个题还不按题目要求来，搞你毛线呢，搞你毛线呢，搞你毛线呢，就是说测试集里没按4，按5平均值也得算是吧
//那你设计功能4是干嘛的。。。
//把功能4加到5里面去还得又重打印一遍让我过不了，也是够恶心的。。。
//这测试集不是前后矛盾了吗

// 1
// 4
// U202054321 Rose 89 94 85 100
// U202056789 Tom 12 34 56 78
// U202012345 Jack 99 100 80 96
// U202098765 Jerry 98 76 54 32
// 2
// 3
// U202054321 1 66
// 4
// 5
// 0
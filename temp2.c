/*任务描述
实验教材P207 程序设计 第（2）题
本关任务：
用单向链表建立一张班级成绩单，包括每个学生的学号、姓名、英语、高等数学、普通物理、C语言程序设计4门课程的成绩。实现以下功能，并提供菜单选项：
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

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct score_list{
    int english;
    int math;
    int physics;
    int c_language;
    float avg;
}SCR;

typedef struct student{
    char num[20];
    char name[20];
    SCR score;
    struct student *next;
}STU;

void link_creat_head(STU **p_head,STU *p_new);
void link_print_all(STU *head);
void link_print_short(STU *head);
void avg_score(STU *head);
void modify_score(STU *head,char *num,int course,int score);
void link_sort(STU **head);
int main(void)
{
    int state;
    STU *head = NULL;
    STU *p_new = NULL;
    char num[20];
    int course,score;
    int n=0;
    while(1)
    {
        scanf("%d",&state);
        switch(state)
        {
            case 0:
                return 0;
            case 1: 
                scanf("%d",&n);
                for(int i=0;i<n;i++)
                {
                    p_new=(STU*)malloc(sizeof(STU));
                    scanf("%s %s %d %d %d %d",p_new->num,p_new->name,&p_new->score.english,&p_new->score.math,&p_new->score.physics,&p_new->score.c_language);
                    link_creat_head(&head,p_new);
                }
                link_sort(&head);
                break;
            case 2:
                link_sort(&head);
                link_print_all(head);
                break;
            case 3:
                scanf("%s %d %d",&num,&course,&score);
                modify_score(head,num,course,score);
                link_sort(&head);
                break;
            case 4:
                avg_score(head);
                break;
            case 5:
                link_print_short(head);
                break;
        }
    }
    return 0;
}
void link_creat_head(STU **p_head,STU *p_new)
{
    STU *p_mov = *p_head;
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

void link_print_all(STU *head)
{
    STU *p_mov = head;
    while(p_mov!=NULL)
    {
        printf("%s %s %d %d %d %d\n",p_mov->num,p_mov->name,p_mov->score.english,p_mov->score.math,p_mov->score.physics,p_mov->score.c_language);
        p_mov = p_mov->next;
    }
}

void link_print_short(STU *head)
{
    STU *p_mov = head;
    while(p_mov!=NULL)
    {
        p_mov->score.avg = (p_mov->score.english+p_mov->score.math+p_mov->score.physics+p_mov->score.c_language)/4.0;
        int sum=p_mov->score.english+p_mov->score.math+p_mov->score.physics+p_mov->score.c_language;
        printf("%s %s %d %.2f\n",p_mov->num,p_mov->name,sum,p_mov->score.avg);
        p_mov=p_mov->next;
    }
}

void avg_score(STU *head)
{
    STU *p_mov = head;
    link_sort(&head);
    while(p_mov!=NULL)
    {
        p_mov->score.avg = (p_mov->score.english+p_mov->score.math+p_mov->score.physics+p_mov->score.c_language)/4.0;
        printf("%s %s %.2f\n",p_mov->num,p_mov->name,p_mov->score.avg);
        p_mov = p_mov->next;
    }
}

void modify_score(STU *head,char *num,int course,int score)
{
    STU *p_mov = head;
    while(p_mov!=NULL)
    {
        if(strcmp(p_mov->num,num)==0)
        {
            switch(course)
            {
                case 1:
                    p_mov->score.english = score;
                    break;
                case 2:
                    p_mov->score.math = score;
                    break;
                case 3:
                    p_mov->score.physics = score;
                    break;
                case 4:
                    p_mov->score.c_language = score;
                    break;
            }
        }
        p_mov = p_mov->next;
    }
}

void link_sort(STU **head)
{
    STU *pb,*pf,temp;
    pb = pf =*head;
    if(*head == NULL || pb->next == NULL)
    {
        return ;
    }
    while(pf->next != NULL)
    {
        pb = pf->next;
        while(pb != NULL)
        {
            if(pf->score.avg > pb->score.avg)
            {
                temp = *pb;
                *pb = *pf;
                *pf = temp;

                temp.next = pb->next;
                pb->next = pf->next;
                pf->next = temp.next;
            }
            pb = pb->next;
        }
        pf = pf->next;
    }
}


/*
任务描述
实验教材P207 程序设计 第（3）题
本关任务：
对程序设计的第二题增加按照平均成绩进行升序排序的函数，写出用交换结点数据域的方法升序排序的函数，排序可用选择法或冒泡法。菜单选项：

退出
输入每个学生的各项信息
输出每个学生的各项信息，结果按平均成绩升序排序
修改指定学生的指定数据项的内容：
修改英语成绩
修改高等数学成绩
修改普通物理成绩
修改C语言成绩
统计每个学生的平均成绩，结果按平均成绩升序排序（保留2位小数）
输出各位学生的学号、姓名、4门课程的总成绩和平均成绩，结果平均成绩升序排序
相关知识
为了完成本关任务，你需要掌握：1.排序，2.链表。

编程要求
根据题目要求，在右侧编辑器完成程序设计。

测试说明
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
U202098765 Jerry 98 76 54 32
U202056789 Tom 12 34 56 78
U202012345 Jack 93.75
U202054321 Rose 86.25
U202098765 Jerry 65.00
U202056789 Tom 45.00
U202012345 Jack 375 93.75
U202054321 Rose 345 86.25
U202098765 Jerry 260 65.00
U202056789 Tom 180 45.00

开始你的任务吧，祝你成功！*/

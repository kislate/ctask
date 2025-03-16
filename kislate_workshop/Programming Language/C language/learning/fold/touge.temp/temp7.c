/*
任务描述
本关任务：对实验七程序设计第2题的程序，增加文件保存和文件打开的功能选项，用函数实现这两个功能。在原有功能选项的基础上，增加6、7两项功能。
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
6.文件保存功能：将链表结点中学生的各项信息保存到二进制文件stu.dat
7.文件打开功能：从文件stu.dat中读取学生信息到内存建立链表。

可以选择原题中的输出功能将这些信息显示在平面上，以验证读写操作的正确性。

编程要求
根据提示，在右侧编辑器补充代码。

测试说明
平台会对你编写的代码进行测试，输入为功能编号，：

测试输入：
依次输入功能编号1，学生数量n，每个学生的学号、姓名和成绩；功能编号3，指定学生的学号，修改的数据项，数据；功能编号6，保存文件；功能编号7，从文件中读数据；功能编号4；功能编号5：
1    （功能编号）
4    （学生人数）
U202012345 Jack 99 100 80 96    （学号 姓名 英语 数学 物理 C语言成绩）
U202054321 Rose 89 94 85 100
U202056789 Tom 12 34 56 78
U202098765 Jerry 98 76 54 32
3    （功能编号）
U202054321 1 66    （将学号为U202054321的同学的英语成绩修改为66）
6    （功能编号）
7    （功能编号）
4    （功能编号）
5    （功能编号）

预期输出：

U202012345 Jack 93.75
U202054321 Rose 86.25
U202056789 Tom 45.00
U202098765 Jerry 65.00
U202012345 Jack 375 93.75
U202054321 Rose 345 86.25
U202056789 Tom 180 45.00
U202098765 Jerry 260 65.00

开始你的任务吧，祝你成功！
*/
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
void link_free(STU **p_head);
FILE *fp;

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
                break;
            case 2:
                link_print_all(head);
                break;
            case 3:
                scanf("%s %d %d",&num,&course,&score);
                modify_score(head,num,course,score);
                break;
            case 4:
                avg_score(head);
                break;
            case 5:
                link_print_short(head);
                break;
            case 6:
                if(!(fp = fopen("stu.dat","wb+")))
                {
                    printf("Can't open file!\n");
                    exit(-1);
                }
                STU *p_mov = head;
                while(p_mov!=NULL)
                {
                    fwrite(p_mov,sizeof(STU),1,fp);
                    p_mov = p_mov->next;
                }
                fclose(fp);
                fflush(stdin);
                break;
            case 7:
                if(!(fp = fopen("stu.dat","rb")))
                {
                    printf("Can't open file!\n");
                    exit(-1);
                }
                link_free(&head);
                STU *p_new = (STU*)malloc(sizeof(STU));
                p_new = (STU*)malloc(sizeof(STU));
                while(fread(p_new,sizeof(STU),1,fp))
                {
                    link_creat_head(&head,p_new);
                    p_new = (STU*)malloc(sizeof(STU));
                }
                fclose(fp);
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

 //链表的释放
 void link_free(STU **p_head)//之所以不用STU *head是因为这里要改变head的值，所以要用二级指针
 //如果直接传递的话这个指针不能在函数中改变，所以在函数中想改变某个值的时候都不要直接传递，而是传递这个值的地址
 {
   //定义一个指针变量保存头结点的地址
   STU *pb=*p_head;
 
  while(*p_head!=NULL)
  {
   //先保存p_head指向的结点的地址
   //如果没有保存，释放后就找不到下一个结点了
   pb=*p_head;
   //p_head保存下一个结点地址

   *p_head=(*p_head)->next;
   //p_head指向下一个节点,这时候下一个地址就是新的头指针；
   
   free(pb);
   //释放结点并防止野指针
   pb = NULL;
  }

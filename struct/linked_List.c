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
    struct student *next;
}STU;


//链表的遍历
void link_print(STU *head)
{
    STU *p_mov;
    //定义新的指针保存链表的首地址，防止使用head改变原本链表
    p_mov = head;
    //当指针保存最后一个结点的指针域为NULL时，循环结束
    while(p_mov!=NULL)//这里和下面那个函数出循环的条件不一样，是因为这里是遍历链表，所以是遍历到最后一个节点
    //而下面那个函数是插入节点，判断条件是当前节点的下一个节点是否为空
    {
        //先打印当前指针保存结点的指针域
        printf("num=%d score=%d name:%s\n",p_mov->num,\
               p_mov->score,p_mov->name);
 
        //指针后移，保存下一个结点的地址
        p_mov = p_mov->next;
    }
}
 
void link_creat_head(STU **p_head,STU *p_new)
{
    STU *p_mov = *p_head;
    if(*p_head == NULL)	//当第一次加入链表为空时，head执行p_new
    {
        *p_head = p_new;
        p_new->next=NULL;
    }//这里就是给这个头指针赋值；
    //后面就可以通过这个头指针来访问链表
    //所以在外部，我们没有在这个链表中放任何的节点，但是可以直接使用这个创建链表的函数


    else //第二次及以后加入链表
    //这里的链表是头插法，所以每次加入的节点都是链表的第一个节点
    {
        while(p_mov->next!=NULL)
        {
            p_mov=p_mov->next;	//找到原有链表的最后一个节点
            //就是说每次p_mov向后移动，直到p_mov->next为空
            //地址从head开始，一直被赋值到最后一个节点
        }
        //此时出了while循环，p_mov指向最后一个节点，这个节点的next是NULL

        p_mov->next = p_new;	//将新申请的节点加入链表
        p_new->next = NULL;     //所以这里是将new节点加入到最后一个节点的后面
        //所以这个
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
 }
 

 
//链表的查找
//按照学号查找
STU * link_search_num(STU *head,int num)
{
    STU *p_mov;

    //定义的指针变量保存第一个结点的地址
    p_mov=head;

    //当没有到达最后一个结点的指针域时循环继续
    while(p_mov!=NULL)
    {

        //如果找到是当前结点的数据，则返回当前结点的地址
        if(p_mov->num == num)//找到了
        {
            return p_mov;
        }

        //如果没有找到，则继续对比下一个结点的指针域
        p_mov=p_mov->next;
    }
 
    //当循环结束的时候还没有找到，说明要查找的数据不存在，返回NULL进行标识
    return NULL;//没有找到
}
 
//按照姓名查找
STU * link_search_name(STU *head,char *name)
{
    STU *p_mov;//结构体名本身就是一个指针，不加*的话你就不能改变这个指针的位置了

    p_mov=head;

    while(p_mov!=NULL)
    {
        if(strcmp(p_mov->name,name)==0)//找到了
        {
            return p_mov;
        }
        p_mov=p_mov->next;
    }
    return NULL;//没有找到
}

//链表结点的删除
void link_delete_num(STU **p_head,int num)
{
    STU *pb,*pf;
    pb=pf=*p_head;
    if(*p_head == NULL)//链表为空，不用删
    {
        printf("链表为空，没有您要删的节点");\
        return ;
    }

    while(pb->num != num && pb->next !=NULL)//循环找，要删除的节点
    {
        pf=pb;
        pb=pb->next;
    }

//判断是否找到，分为两种情况
    if(pb->num == num)//找到了一个节点的num和num相同
    {
        if(pb == *p_head)//要删除的节点是头节点
        {
            //让保存头结点的指针保存后一个结点的地址
            *p_head = pb->next;
            //这时候这个头指针就指向了第二个节点，也就是指这个链表的第一个节点变为了原来的第二个节点
        }

        else
        {
            //前一个结点的指针域保存要删除的后一个结点的地址
            pf->next = pb->next;//其实就是让其上一个节点，绕过此节点，直接指向下一个节点
        }
 
        //释放空间
        free(pb);//把这块内存释放掉
        pb = NULL;//帅啊，指针直接向NULL，这样就不会出现野指针了；
    }

    else//没有找到
    {
        printf("没有您要删除的节点\n");
    }
}

//链表的插入：按照学号的顺序插入
void link_insert_num(STU **p_head,STU *p_new)
{
    STU *pb,*pf;
    pb=pf=*p_head;
    if(*p_head ==NULL)// 链表为空链表
    {
        *p_head = p_new;
        p_new->next=NULL;
        return ;
    }

    while((p_new->num >= pb->num)  && (pb->next !=NULL) )//新节点比原来的大的时候，继续找
    {
        pf=pb;
        pb=pb->next;
    }
 
    if(p_new->num < pb->num)//找到一个节点的num比新来的节点num大，插在pb的前面
    {
        if(pb== *p_head)//找到的节点是头节点，插在最前面
        {
            p_new->next= *p_head;//将原头节点设置为新节点的下一个节点
            *p_head =p_new;//将头节点设置为新节点
            //这里就是一个顺序问题，先让新节点指向原来的头节点，然后再让头节点指向新节点
            //*p_head是第一个节点的地址，所以把第一个节点的地址给到了新节点的next
            //而然后又把p_new的地址给到了p_head;
        }

        else
        {
            pf->next=p_new;
            p_new->next = pb;
        }
    }

    else//没有找到pb的num比p_new->num大的节点，插在最后
    {
        pb->next =p_new;
        p_new->next =NULL;
    }
}

//链表的排序
void link_order(STU *head)
{
    STU *pb,*pf,temp;//这里的temp不需要移动，所以不用指针
    pf=head;
 
    if(head==NULL)
    {
        printf("链表为空,不用排序\n");
        return ;
    }
 
    if(head->next ==NULL)
    {
        printf("只有一个节点，不用排序\n");
        return ;
    }
 
    while(pf->next !=NULL)//以pf指向的节点为基准节点，
    {
        pb=pf->next;//pb从基准元素的下个元素开始
        //pb在前，pf在后



        //这个循环就是类似于冒泡排序，把最大的放在最后；
        while(pb!=NULL)
        {
            if(pf->num > pb->num)//如果基准元素的num比pb的num大，交换两个节点的数据
            {
                temp=*pb;
                *pb=*pf;
                *pf=temp;//这一处直接交换了所有的数据，同时交换了next指针，所以还要把next给换回去；
                //这里是pf的下一个比它小，所以交换两个节点的数据，就是把大的放在前面
                //交换所指向的节点的数据，而不是交换指针的指向；
 
                //这里就是把next给换回去
                temp.next=pb->next;
                pb->next=pf->next;
                pf->next=temp.next;
            }
            //从开始到最后pf和pb所指向的地址都不会变，只是里面的数据变了
            
            //pb向后移
            pb=pb->next;
        }
        /*
        // pf: 1 -> 3 -> 2 -> 4
        // pb:      ^
        // temp:    3

        // After swapping:
        // pf: 1 -> 2 -> 3 -> 4
        // pb:      ^
        // temp:    3
        */



        pf=pf->next;
    }
}



int main()
{
    STU *head = NULL,*p_new = NULL;//定义头指针和新节点指针，初始化为空
    int num,i;
    printf("请输入链表初始个数:\n");
    scanf("%d",&num);
    for(i = 0; i < num;i++)
    {
        p_new = (STU*)malloc(sizeof(STU));//申请一个新节点
        //这个节点如果不free的话，会一直存在，直到程序结束
        
        printf("请输入学号、分数、名字:\n"); //给新节点赋值
        scanf("%d %d %s",&p_new->num,&p_new->score,p_new->name);
 
        link_creat_head(&head,p_new);	//将新节点加入链表
    }
}
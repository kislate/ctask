//线性表的管理系统
//实现了线性表的基本操作，线性表的管理表操作，线性表的文件操作
//单链表操作为主函数，多链表操作为子函数（并在对单链操作的时候调用主函数）
//vscode不知为何报错，devc++编译运行均通过
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType; //数据元素类型定义

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10

typedef struct{  //顺序表（顺序结构）的定义
	      ElemType * elem;
	      int length;
	      int listsize;
         }SqList;
typedef struct{  //线性表的管理表定义
        struct { char name[30];
                    SqList L;	
            } elem[10];
            int length;
            int listsize;
        }LISTS;
status InitList(SqList &L);
status DestroyList(SqList &L);
status ClearList(SqList &L);
status ListEmpty(SqList L);
status ListLength(SqList L);
status GetElem(SqList L,int i,ElemType &e);
status LocateElem(SqList L,ElemType e);
status PriorElem(SqList L,ElemType e,ElemType &pre);
status NextElem(SqList L,ElemType e,ElemType &next);
status ListInsert(SqList &L,int i,ElemType e);
status ListDelete(SqList &L,int i,ElemType &e);
status ListTraverse(SqList L);
status Maxline(SqList L);
status KLines(SqList L,int k);
status LSort(SqList &L);
status SaveList(SqList L,char FileName[]);
status LoadList(SqList &L,char FileName[]);
status ListsManage(LISTS &L); //线性表的管理表操作函数
status AddList(LISTS &Lists,char ListName[]);
status RemoveList(LISTS &Lists,char ListName[]);
status LocateList(LISTS Lists,char ListName[]);

int mood=0; //mood=0表示单线性表操作，mood=1表示多线性表操作
SqList L;
char Lname[30];//匹配多线性表的名称

int main(){
SetConsoleOutputCP(65001); // 设置为UTF-8编码
int op=1;

LISTS Lists;
int n,e;
char name[30];
Lists.length=0;

char FileName[30];

while(op){
    system("cls");	printf("\n\n");
    printf("      Menu for Linear Table On Sequence Structure \n");
    printf("-------------------------------------------------\n");
    printf("    	  1. InitList/Putdata       9. NextElem\n");
    printf("    	  2. DestroyList            10. ListInsert\n");
    printf("    	  3. ClearList              11. ListDelete\n");
    printf("    	  4. ListEmpty              12. ListTrabverse\n");
    printf("    	  5. ListLength             13. Maxline\n");
    printf("    	  6. GetElem                14. KLines\n");
    printf("    	  7. LocateElem             15. LSort\n");
    printf("    	  8. PriorElem              16. File\n");
    printf("    	  0. Exit                   17. ListsManage\n");
    printf("-------------------------------------------------\n");
    printf("    请选择你的操作[0~17]:");
    scanf("%d",&op);
    switch(op){
        case 1:
            if(InitList(L)==OK) 
				printf("线性表创建成功！\n");
	      	else printf("线性表已存在，无法再次创建！\n");
              printf("输入线性表的元素？（1/0）\n");
              int choice;
              scanf("%d",&choice);
              if(choice==1) {
                  printf("请输入线性表的元素（以0结束）：\n");
                  ElemType data;
                  scanf("%d",&data); 
                  while (data)
                  {
                      ListInsert(L,L.length+1,data);
                      scanf("%d",&data);
                  }
              }
            getchar();getchar();
            break;
        case 2:
            if(DestroyList(L)==OK) printf("线性表销毁成功！\n");
                else printf("线性表不存在，无法销毁！\n");
            getchar();getchar();
            break;
        case 3:
            if(ClearList(L)==OK) printf("线性表已清空！\n");
                else printf("线性表不存在，无法清空！\n");
            getchar();getchar();
            break;
        case 4:
            if(ListEmpty(L)==INFEASIBLE) printf("线性表不存在！\n");
                else if(ListEmpty(L)==OK) printf("线性表为空！\n");
					else printf("线性表非空！\n");
            getchar();getchar();
            break;
        case 5:
            if(ListLength(L)==INFEASIBLE) printf("线性表不存在！\n");
                else printf("该线性表长度为%d",ListLength(L));
            getchar();getchar();
            break;
        case 6:
            printf("请输入要获取的元素位置：\n");
            int i;
            ElemType e;
            scanf("%d",&i);
            if(GetElem(L,i,e)==OK) printf("获取元素成功，该元素为%d！\n",e);
                else if(GetElem(L,i,e)==ERROR) printf("获取元素不在该线性表范围之内！\n");
                    else printf("线性表不存在，无法获取元素！\n");
            getchar();getchar();
            break;
        case 7:
            printf("请输入要查找的元素：\n");
            ElemType a;
            scanf("%d",&a);
            if(LocateElem(L,a)==INFEASIBLE) printf("线性表不存在！\n");
                else if(LocateElem(L,a)==0) printf("没找到元素%d！\n",a);
                    else printf("元素%d在第%d个位置！\n",a,LocateElem(L,a));
            getchar();getchar();
            break;
        case 8:
            printf("请输入要查找前驱的元素：\n");
            ElemType b,pre;
            scanf("%d",&b);
            if(PriorElem(L,b,pre)==INFEASIBLE) printf("线性表不存在！\n");
                else if(PriorElem(L,b,pre)==ERROR) printf("前驱不存在！\n");
                    else if(PriorElem(L,b,pre)==-3) printf("元素不存在！\n");
                        else printf("元素%d的前驱为%d！\n",b,pre);
            getchar();getchar();
            break;
        case 9:
            printf("请输入要查找后继的元素：\n");
            ElemType c,next;
            scanf("%d",&c);
            if(NextElem(L,c,next)==INFEASIBLE) printf("线性表不存在！\n");
                else if(NextElem(L,c,next)==ERROR) printf("后继不存在！\n");
                    else if(NextElem(L,c,next)==-3) printf("元素不存在！\n");
                        else printf("元素%d的后继为%d！\n",c,next);
            getchar();getchar();
            break;
        case 10:
        	printf("在何处插入何元素:"); 
			int j;
			ElemType d; 
			scanf("%d %d",&j,&d);
            if(ListInsert(L,j,d)==OK) printf("插入成功！");
				else if(ListInsert(L,j,d)==INFEASIBLE) printf("线性表不存在！\n");
				   else printf("插入位置选取有误！\n");
            getchar();getchar();
            break;
        case 11:
            printf("在何处删除元素:"); 
			int k;
			ElemType f; 
			scanf("%d",&k);
            if(ListDelete(L,k,f)==OK) printf("删除成功，删除的元素为%d！",f);
				else if(ListDelete(L,k,f)==INFEASIBLE) printf("线性表不存在！\n");
				   else printf("删除位置选取有误！\n");
            getchar();getchar();
            break;
        case 12:
           	if(ListTraverse(L)==INFEASIBLE) printf("线性表不存在！\n");
        	getchar();getchar();
            break;
        case 13:
            if(Maxline(L)==INFEASIBLE) printf("线性表不存在或者线性表为空！\n");
            else printf("最大子序列和为：%d\n",Maxline(L));
            getchar();getchar();
            break;
        case 14:
            int ksum;
            printf("请输入k的值：");
            scanf("%d",&ksum);
            if(KLines(L,ksum)==INFEASIBLE) printf("线性表不存在或者线性表为空！\n");
            else printf("和为k的子序列有%d个\n",KLines(L,ksum));
            getchar();getchar();
            break;
        case 15:
            if(LSort(L)==INFEASIBLE) printf("线性表不存在！\n");
                else printf("排序成功！\n");
            getchar();getchar();
            break;
        case 16://文件操作
            printf("请选择：\n");
            printf("1.保存线性表到文件\n");
            printf("2.从文件中读取线性表\n");
            int choice1;
            scanf("%d",&choice1);
            printf("请输入文件名：\n");
            scanf("%s",FileName);
            if(choice1==1) {
                if(SaveList(L,FileName)==OK) printf("保存成功！\n");
                    else printf("线性表不存在，无法保存！\n");
            }
            else if(choice1==2) {
                if(LoadList(L,FileName)==OK) printf("读取成功！\n");
                    else printf("线性表已存在，无法读取！\n");
            }
            else printf("输入有误！\n");
            getchar();getchar();
            break;
        case 17:
            mood=1;
            ListsManage(Lists);
            getchar();getchar();
            break;
    case 0:
        break;
    }//end of switch
}//end of while
printf("欢迎下次再使用本系统！\n");
}



//18.线性表的管理表操作函数
status ListsManage(LISTS &Lists)
{
    int op=1;
    char ListName[30];
    while(op){
        system("cls");	printf("\n\n");
        printf("      Menu for Linear Table Management \n");
        printf("-------------------------------------------------\n");
        printf("    	  1. AddList        2. RemoveList \n");
        printf("    	  0. Exit   		3. LocateList\n");
        printf("          4. More           5. ListsTrabverse\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~5]:");
        scanf("%d",&op);
        switch(op){
            case 1:
            	char c;
                do{
                    printf("请输入线性表名称：\n");
                    scanf("%s", ListName);
                    if(AddList(Lists, ListName) == OK) 
                        {
                            printf("线性表创建成功！\n");
                            printf("请输入线性表的元素（以0结束）：\n");
                            ElemType data;
                            scanf("%d",&data); 
                            while (data)
                            {
                                ListInsert(Lists.elem[Lists.length-1].L,Lists.elem[Lists.length-1].L.length+1,data);
                                scanf("%d",&data);
                            }
                        }
                    else 
                        printf("空间已满，无法再创建线性表！\n");
                	printf("是否继续？（1/0）\n");
                	scanf("%d",&c);
                }while(c);  
                getchar();getchar();
                break;
            case 2:
                printf("请输入要删除的线性表名称：\n");
                scanf("%s", ListName);
                if(RemoveList(Lists, ListName) == OK) 
                    printf("该线性表删除成功！\n");
                else 
                    printf("未找到该线性表，无法删除！\n");
                getchar();getchar();
                break;
            case 3:
                printf("请输入要查找的线性表名称：\n");
                scanf("%s", ListName);
                int x;
                x = LocateList(Lists, ListName);
                if(x > 0) {
                    printf("线性表 %s 的逻辑序号为：%d\n", ListName, x);
                } else {
                    printf("未找到该线性表！\n");
                }
                getchar();getchar();
                break;
            case 4:
                printf("对哪一个表展开更多单一操作（输入逻辑编号即可）？\n");
                int index3;
                scanf("%d", &index3);
                if(index3 < 1 || index3 > Lists.length) {
                    printf("输入的逻辑编号不合法！\n");
                    getchar();getchar();
                    break;
                }
                printf("对线性表 %s 进行操作：\n", Lists.elem[index3-1].name);
                strcpy(Lname,Lists.elem[index3-1].name);
                L=Lists.elem[index3-1].L;
                main();//调用主函数以对单线性表进行操作
                Lists.elem[index3-1].L=L;
                break;
            case 5:
                for(int i=0;i<Lists.length;i++)
                    {
                        printf("%s ",Lists.elem[i].name);
                        for(int j=0;j<Lists.elem[i].L.length;j++)
                            printf("%d ",Lists.elem[i].L.elem[j]);
                        printf("\n");
                    }
                getchar();getchar();
                break;
            case 0:
                mood=0;
                getchar();getchar();
                break;
            }
    }
    main();
}
status AddList(LISTS &Lists,char ListName[])
{
    if (Lists.length >= 10) //判断是否超过最大线性表数量
        return ERROR;
    strcpy(Lists.elem[Lists.length].name, ListName);
    Lists.elem[Lists.length].L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType)); //分配空间
    Lists.elem[Lists.length].L.length = 0; 
    Lists.elem[Lists.length].L.listsize = LIST_INIT_SIZE; 
    Lists.length++; 
    return OK;
}

status RemoveList(LISTS &Lists,char ListName[])
// Lists中删除一个名称为ListName的线性表
{
    for(int i=0;i<Lists.length;i++)
    {
        if(strcmp(Lists.elem[i].name, ListName)==0)
        {
            for(;i<Lists.length-1;i++)
                Lists.elem[i]=Lists.elem[i+1];
            Lists.elem[i].L.elem = NULL; 
            Lists.elem[i].L.length = 0; 
            Lists.elem[i].L.listsize = 0; 
            free(Lists.elem[i].L.elem);
            Lists.length--;
            return OK;
        }
    }
    return ERROR;
}

status LocateList(LISTS Lists,char ListName[])
// 在Lists中查找一个名称为ListName的线性表，成功返回逻辑序号，否则返回0
{
    for(int i=0;i<Lists.length;i++)
    {
        if(strcmp(Lists.elem[i].name, ListName)==0)
            return i+1;
    }
    return 0;
}


//1.创建线性表
status InitList(SqList &L)
{
    if (L.elem != NULL) //如果线性表已经存在，返回INFEASIBLE
        return INFEASIBLE;
    L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType)); //分配空间
    L.length = 0; //设置元素个数初始值
    L.listsize = LIST_INIT_SIZE; //设置元素空间容量
    return OK; 
}

//2.销毁线性表
status DestroyList(SqList &L)
{
    if (L.elem == NULL) //如果线性表不存在，返回INFEASIBLE
        return INFEASIBLE;
    L.elem = NULL; 
    L.length = 0; 
    L.listsize = 0; 
    free(L.elem); //释放线性表的元素空间
    return OK;
}

//3.清空线性表
status ClearList(SqList &L)
{
    if(L.elem == NULL) //如果线性表不存在，返回INFEASIBLE
        return INFEASIBLE;
    for(int i = 0; i < L.length; i++) 
        L.elem[i] = 0; 
    L.length = 0;
    return OK;
}

//4.判断线性表是否为空
status ListEmpty(SqList L)
{
    if (L.elem == NULL) 
        return INFEASIBLE;
    if (L.length == 0)
        return TRUE; //线性表为空
    else
        return FALSE; //线性表不为空
}

//5.求线性表的长度
status ListLength(SqList L)
{
    if(L.elem==NULL)
        return INFEASIBLE;
    else 
        return L.length;
}

//6.获取元素
status GetElem(SqList L,int i,ElemType &e)
{
    if (L.elem == NULL) 
        return INFEASIBLE;
    if (i < 1 || i > L.length) 
        return ERROR;
    e = L.elem[i - 1]; 
    return OK;
}

//7.定位元素
status LocateElem(SqList L,ElemType e)
{
    if(L.elem == NULL) 
        return INFEASIBLE;
    for(int i = 0; i < L.length; i++) { 
        if(L.elem[i] == e) 
            return i + 1; 
    }
    return 0; //元素e不存在
}

//8.获取前驱
status PriorElem(SqList L,ElemType e,ElemType &pre)
{
    if(L.elem == NULL) 
        return INFEASIBLE;
    if(L.length == 0) 
        return ERROR; //线性表为空，没有前驱
    for(int i = 0; i < L.length; i++) { 
        if(L.elem[i] == e) {
            if(i == 0) 
                return ERROR; //没有前驱
            pre = L.elem[i - 1]; 
            return OK;
        }
    }
    return -3; //元素e不存在
}
//9.获取后继
status NextElem(SqList L,ElemType e,ElemType &next)
{
    if(L.elem == NULL) 
        return INFEASIBLE;
    if(L.length == 0) 
        return ERROR; //线性表为空，没有后继
    for(int i = 0; i < L.length; i++) { 
        if(L.elem[i] == e) {
            if(i == L.length - 1) 
                return ERROR; //没有后继
            next = L.elem[i + 1]; 
            return OK;
        }
    }
    return -3;
}

//10.插入元素
status ListInsert(SqList &L,int i,ElemType e)
{
    if(L.elem == NULL) 
        return INFEASIBLE;
    if(i < 1 || i > L.length + 1)
        return ERROR; 
    if(L.length >= L.listsize) {
        ElemType *newbase = (ElemType *)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType)); //扩展空间
        L.elem = newbase; 
        L.listsize += LISTINCREMENT; 
    }
    for(int j = L.length; j >= i; j--) 
        L.elem[j] = L.elem[j - 1]; //后移
    L.elem[i - 1] = e; //插入元素
    L.length++; //表长加1
    return OK; 
}

//11.删除元素
status ListDelete(SqList &L,int i,ElemType &e)
{
    if(L.elem == NULL) 
        return INFEASIBLE;
    if(i < 1 || i > L.length )
        return ERROR; 
    e=L.elem[i - 1]; //保存删除的元素
    for(int j = i-1; j < L.length-1; j++) 
        L.elem[j] = L.elem[j + 1]; //前移
    L.elem[L.length - 1] = 0; //清空最后一个元素
    L.length--; //表长减1
    return OK;
}

//12.遍历线性表
status ListTraverse(SqList L)
{
    if(L.elem == NULL) 
        return INFEASIBLE;
    if(L.length == 0)
        return OK; //线性表为空
    if(mood) printf("%s ",Lname); //多线性表操作时对单表输出表名;
    for(int i = 0; i < L.length; i++) {
        printf("%d ", L.elem[i]); //输出
    }
        return OK;
}

//13.最大子序列和
status Maxline(SqList L)
{
    if(L.length >=1){
        int maxsum=0,temp=0;
        for(int i=0;i<L.length;i++)
        {
            temp+=L.elem[i];
            if(temp<0) temp=0;
            if(temp>maxsum) maxsum=temp;
        }
        return maxsum;
    }
    else return INFEASIBLE;
}

//14.和为k的子列个数
status KLines(SqList L,int k)
{
    if(L.length >=1){
        int count=0,temp=0,left=0;
        for(int i=0;i<L.length;i++)
        {
            temp+=L.elem[i];
            if(temp==k) count++;
            if(temp>k) 
            {
                while(temp>k && left<=i)
                {
                    temp-=L.elem[left++];
                    if(temp==k) count++;
                }
            }
        }
        return count;
    }
    else return INFEASIBLE;
}

//15.排序
status LSort(SqList &L)
// 将线性表L的元素按从小到大的顺序排列
{
    if(L.elem == NULL) 
        return INFEASIBLE;
    for(int i = 0; i < L.length - 1; i++) {
        for(int j = 0; j < L.length - i - 1; j++) {
            if(L.elem[j] > L.elem[j + 1]) {
                ElemType temp = L.elem[j]; 
                L.elem[j] = L.elem[j + 1]; 
                L.elem[j + 1] = temp; 
            }
        }
    }
    return OK;
}

//16.将线性表保存到文件
status  SaveList(SqList L,char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    if(L.elem == NULL) 
        return INFEASIBLE;
    FILE *fp = fopen(FileName, "w"); 
    for(int i = 0; i < L.length; i++) {
        fprintf(fp, "%d ", L.elem[i]); 
    }
    fclose(fp); 
    return OK; 
}

//17.从文件中读取线性表
status  LoadList(SqList &L,char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
    if(L.elem != NULL) 
        return INFEASIBLE;
    FILE *fp = fopen(FileName, "r"); 
    L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    while (fscanf(fp, "%d", &L.elem[L.length++]) != EOF) {
        if (L.length >= L.listsize) {
            L.elem = (ElemType *)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType)); 
            L.listsize += LISTINCREMENT; 
        }
    }
    fclose(fp);
    L.length--;
    return OK;
}
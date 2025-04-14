#include <stdio.h>
#include <stdlib.h>
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
typedef int ElemType;
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

 // 01
 status InitList(SqList& L)
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L.elem != NULL) return INFEASIBLE;
    L.elem = (ElemType *)malloc(sizeof(ElemType) * LIST_INIT_SIZE);
    if(L.elem == NULL) return OVERFLOW;
    L.listsize = LIST_INIT_SIZE;
    L.length = 0;
    return OK;
    /********** End **********/
}

// 10
status ListInsert(SqList &L,int i,ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L.elem == NULL) return INFEASIBLE;
    if(i < 1 || i > L.length + 1) return ERROR;
    // if(L.length >= L.listsize)
    // {
    //     size_t newSize = (L.listsize + LISTINCREMENT) * sizeof(ElemType);// 避免溢出;
    //     if(newSize <= 0) return OVERFLOW;
    //     ElemType * newbase = (ElemType *)realloc(L.elem, newSize);
    //     if(!newbase) return OVERFLOW;
    //     L.elem = newbase;
    //     L.listsize += LISTINCREMENT;
    // }
    
    for(int j = L.length; j >= i; j--) L.elem[j] = L.elem[j-1];
    L.elem[i-1] = e;
    L.length++;
    return OK;
    /********** End **********/
}

// 12:
status ListTraverse(SqList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L.elem == NULL) return -1;
    for(int i = 0; i < L.length; i++) printf("%d ", L.elem[i]);
    return 1;
    /********** End **********/
}


// 14
#include<string.h>
status AddList(LISTS &Lists,char ListName[])
// 只需要在Lists中增加一个名称为ListName的空线性表，线性表数据又后台测试程序插入。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
   if(Lists.length >= 10){
       return ERROR;
   }
   printf("1:%d\n",Lists.length);
   strcpy(Lists.elem[Lists.length].name, ListName);
   printf("1.5:%s\n",Lists.elem[Lists.length].name);
   Lists.elem[Lists.length].L.elem = (ElemType *)malloc(sizeof(ElemType) * LIST_INIT_SIZE);
    if(Lists.elem[Lists.length].L.elem == NULL) return OVERFLOW;
    Lists.elem[Lists.length].L.listsize = LIST_INIT_SIZE;
    Lists.elem[Lists.length].L.length = 0;
   printf("2:%d\n",Lists.length);
   Lists.length++;
    printf("3:%d\n",Lists.length);
   return OK;

    /********** End **********/
} 


int main() {
   LISTS Lists;
   int n,e;
   char name[30];
   Lists.length=0;
	scanf("%d", &n);
	while(n--)
   {
    	scanf("%s",name);
   		AddList(Lists,name);
        printf("%s\n",Lists.elem[Lists.length-1].name);
      scanf("%d",&e);
      while (e)
      {
      		ListInsert(Lists.elem[Lists.length-1].L,Lists.elem[Lists.length-1].L.length+1,e);
      		scanf("%d",&e);
      }
   }
   for(n=0;n<Lists.length;n++)
   {
   		printf("%s ",Lists.elem[n].name);
   		ListTraverse(Lists.elem[n].L);
        putchar('\n');
   }
return 1;
}
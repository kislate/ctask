// 已知顺序表L中的数据元素递增有序，数据元素类型为int。相关定义如下：
// #define LIST_INIT_SIZE 20
// #define LISTINCREMENT 10
// typedef int ElemType;
// typedef struct
//    { ElemType *elem;
//      int length;
//      int listsize;
//     } SqList;
// 试写一算法，将x插入到顺序表的适当位置上，以保持该表的有序性。
// 函数原型：int insert(SqList &L,ElemType x);

// 相关知识
// 为了完成本关任务，你需要掌握：1.线性表的物理结构，2.线性表的运算。

// 编程要求
// 根据提示，在右侧编辑器补充代码，写出函数 int insert(SqList &L,ElemType x) 的定义。

// 测试说明
// 平台会自动读取输入数据，对你编写的代码进行测试，并输出结果。

// 测试输入：0 1 
// 预期输出：   1

// 测试输入：1 3 5 7 9 0 6
// 预期输出：   1   3   5   6   7   9
#include<stdio.h>
#include<stdlib.h>
#define LIST_INIT_SIZE 20
#define LISTINCREMENT 10
typedef int ElemType;
typedef struct
   { ElemType *elem;
     int length;
     int listsize;
    } SqList;
    
int insert(SqList *L, ElemType x)
{
/**********begin**********/
if (L->length >= L->listsize) {
    // 线性表已满，需要扩容
    ElemType *newBase = (ElemType *)realloc(L->elem, (L->listsize + LISTINCREMENT) * sizeof(ElemType));
    if (!newBase) return -1; // 扩容失败
    L->elem = newBase;
    L->listsize += LISTINCREMENT;
}

int flag=0,temp1=x,temp2=0;//temp1用于存储插入的元素（让其=x是为了考虑其最大的情况），temp2用于存储后移的元素
//初判，针对x小于等于第一个元素的情况
if(x<=L->elem[0]){
    temp1 = L->elem[0];
    L->elem[0] = x;
    flag=1;
}

for(int i=1; i < L->length; i++)
{
    //后移
    if(flag){
        temp2 = L->elem[i];
        L->elem[i] = temp1;
        temp1=temp2;
    }
    //插入
    if(x > L->elem[i-1] && x <= L->elem[i]){ //用i-1比i+1更好，不会越界
        temp1 = L->elem[i];
        L->elem[i] = x;
        flag=1;
    }	
}
L->elem[L->length++] = temp1;

/**********end**********/
}

int main()
{
    SqList L;
    ElemType x;
    int i;
    L.elem=(ElemType *)malloc(sizeof(ElemType)*LIST_INIT_SIZE);
    L.length=0;
    L.listsize=LIST_INIT_SIZE;
    scanf("%d",&x);
    while (x)
    {
        L.elem[L.length++]=x;
        scanf("%d",&x);
    }
    scanf("%d",&x);
    insert(&L,x);
    for(i=0;i<L.length;i++)
        printf("%8d",L.elem[i]);
    if (L.length>L.listsize) printf("\n程序未处理溢出");

	return 0;
}

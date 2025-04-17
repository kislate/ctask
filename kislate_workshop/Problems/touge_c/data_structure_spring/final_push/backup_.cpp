/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
//#include <windows.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType;

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct{
    ElemType *elem;
    int length;
    int listsize;
}SqList;

status InitList(SqList& L);
status DestroyList(SqList& L);
status ClearList(SqList& L);
status ListEmpty(SqList L);
status ListLength(SqList L);
status GetElem(SqList L, int i, ElemType& e);
int LocateElem(SqList L, ElemType e);
status PriorElem(SqList L, ElemType cur, ElemType& pre_e);
status NextElem(SqList L, ElemType cur, ElemType& next_e);
status ListInsert(SqList& L, int i, ElemType e);
status ListDelete(SqList& L, int i, ElemType& e);
status ListTrabverse(SqList L);
status ListInsertFast(SqList& L);

int main(void){
    // 防止输出乱码
    //SetConsoleOutputCP(65001); // 设置输出为UTF-8
    //SetConsoleCP(65001);       // 设置输入为UTF-8
    SqList L;
    int op=1;
    ElemType e, pre, next;
    int pos, loc;
    status result;
    while(op){
        system("cls"); printf("\n\n");
        printf("      Menu for Linear Table On Sequence Structure \n");
        printf("-------------------------------------------------\n");
        printf("      1. InitList          7. LocateElem\n");
        printf("      2. DestroyList       8. PriorElem\n");
        printf("      3. ClearList         9. NextElem \n");
        printf("      4. ListEmpty        10. ListInsert\n");
        printf("      5. ListLength       11. ListDelete\n");
        printf("      6. GetElem          12. ListTrabverse\n");
        printf("      13.ListInsertFast    0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("      请选择你的操作[0~13]:");
        scanf("%d",&op);
        switch(op) {
        case 1:
            if(InitList(L)==OK) printf("      线性表创建成功！\n");
            else printf("      线性表创建失败！\n");
            getchar(); getchar();
            break;
        case 2:
            if(DestroyList(L)==OK) printf("      线性表销毁成功！\n");
            else printf("      线性表销毁失败！\n");
            getchar();getchar();
            break;
        case 3:
            if(ClearList(L)==OK) printf("      线性表清空成功！\n");
            else printf("      线性表清空失败！\n");
            getchar();getchar();
            break;
        case 4:
            result = ListEmpty(L);
            if(result == INFEASIBLE) printf("      线性表不存在！\n");
            else if(result == TRUE) printf("      线性表为空！\n");
            else printf("      线性表不为空！\n");
            getchar();
            printf("      按任意键继续...\n");
            getchar();
            break;
        case 5:
            result = ListLength(L);
            if(result == INFEASIBLE) printf("      线性表不存在！\n");
            else printf("      线性表长度为%d\n", result);
            getchar();
            printf("      按任意键继续...\n");
            getchar();
            break;
        case 6:
            printf("      请输入要获取的元素位置：");
            scanf("%d", &pos);
            result = GetElem(L, pos, e);
            if(result == INFEASIBLE) printf("      线性表不存在！\n");
            else if(result == ERROR) printf("      位置不合法！\n");
            else printf("      第%d个元素为：%d\n", pos, e);
            getchar();
            printf("      按任意键继续...\n");
            getchar();
            break;
        case 7:
            printf("      请输入要查找的元素值：");
            scanf("%d", &e);
            loc = LocateElem(L, e);
            if(loc == INFEASIBLE) printf("      线性表不存在！\n");
            else if(loc == 0) printf("      未找到该元素！\n");
            else printf("      元素%d的位置为：%d\n", e, loc);
            getchar();
            printf("      按任意键继续...\n");
            getchar();
            break;
        case 8:
            printf("      请输入要查找前驱的元素值：");
            scanf("%d", &e);
            result = PriorElem(L, e, pre);
            if(result == INFEASIBLE) printf("      线性表不存在！\n");
            else if(result == ERROR) printf("      元素不存在或无前驱！\n");
            else printf("      元素%d的前驱为：%d\n", e, pre);
            getchar();
            printf("      按任意键继续...\n");
            getchar();
            break;
        case 9:
            printf("      请输入要查找后继的元素值：");
            scanf("%d", &e);
            result = NextElem(L, e, next);
            if(result == INFEASIBLE) printf("      线性表不存在！\n");
            else if(result == ERROR) printf("      元素不存在或无后继！\n");
            else printf("      元素%d的后继为：%d\n", e, next);
            getchar();
            printf("      按任意键继续...\n");
            getchar();
            break;
        case 10:
            printf("      请输入插入位置和元素值：");
            scanf("%d %d", &pos, &e);
            result = ListInsert(L, pos, e);
            if(result == INFEASIBLE) printf("      线性表不存在！\n");
            else if(result == ERROR) printf("      位置不合法或内存不足！\n");
            else printf("      插入成功！\n");
            getchar();
            printf("      按任意键继续...\n");
            getchar();
            break;
        case 11:
            printf("      请输入删除位置：");
            scanf("%d", &pos);
            result = ListDelete(L, pos, e);
            if(result == INFEASIBLE) printf("      线性表不存在！\n");
            else if(result == ERROR) printf("      位置不合法！\n");
            else printf("      删除的元素为：%d\n", e);
            getchar();
            printf("      按任意键继续...\n");
            getchar();
            break;
        case 12:
            if(!ListTrabverse(L)) printf("      线性表是空表！\n");
            getchar();
            printf("      按任意键继续...\n");
            getchar();
            break;
        case 13:
            if(ListInsertFast(L) == OK) printf("      快速插入成功！\n");
            else printf("      快速插入失败！\n");
            getchar();
            printf("      按任意键继续...\n");
            getchar();
            break;
        case 0:
            break;
        default:
            printf("      无效的操作编号，请重新输入！\n");
            getchar();
            printf("      按任意键继续...\n");
            getchar();
            break;
        }
    }
    printf("欢迎下次再使用本系统！\n");
    return 0;
}

// 1:初始化线性表
status InitList(SqList& L)
{
    if(L.elem)
    {
        printf("      线性表已存在！\n");
        return INFEASIBLE; // 线性表已存在
    }
    L.elem = (ElemType *)malloc(sizeof(ElemType) * LIST_INIT_SIZE);
    if(!L.elem) return OVERFLOW;// 内存分配失败
    L.listsize = LIST_INIT_SIZE;
    L.length = 0;
    return OK;
}

// 2:销毁线性表
status DestroyList(SqList& L)
{
    if(L.elem == NULL)
    {
        printf("      线性表不存在！\n");
        return -1; // 线性表不存在
    }
    free(L.elem);
    L.elem = NULL;// 防止野指针
    L.length = 0;
    L.listsize = 0;
    return 1;
}

// 3:清空线性表
status ClearList(SqList& L)
{
    if(L.elem == NULL)
    {
        printf("      线性表不存在！\n");
        return -1; // 线性表不存在
    }
    L.length = 0;
    return 1;
}

// 4:判断线性表是否为空
status ListEmpty(SqList L)
{
    if(L.elem == NULL)
    {
        printf("      线性表不存在！\n");
        return INFEASIBLE; // 线性表不存在
    }
    if(L.length == 0) return TRUE;
    else return FALSE;
}

// 5:返回线性表长度
status ListLength(SqList L)
{
    if(L.elem == NULL)
    {
        printf("      线性表不存在！\n");
        return INFEASIBLE; // 线性表不存在
    }
    return L.length;
}

// 6:获取第i个元素
status GetElem(SqList L, int i, ElemType &e)
{
    if(L.elem == NULL)
    {
        printf("      线性表不存在！\n");
        return INFEASIBLE; // 线性表不存在
    }
    if(i < 1 || i > L.length)
    {
        printf("      位置不合法！\n");
        return ERROR; // 位置不合法
    }
    e = L.elem[i-1];
    return 1;
}

// 7:查找元素e的位置
int LocateElem(SqList L, ElemType e)
{
    if(L.elem == NULL)
    {
        printf("      线性表不存在！\n");
        return INFEASIBLE; // 线性表不存在
    }
    for(int i = 0; i < L.length; i++) if(L.elem[i] == e) return i+1;
    return 0; // 未找到该元素
}

// 8:获取元素e的前驱
status PriorElem(SqList L, ElemType e, ElemType &pre)
{
    if(L.elem == NULL) return -1;
    int flag = 0;
    for(int i = 0; i < L.length; i++)
    {
        if(e == L.elem[i])
        {
            if(i == 0) return 0;
            else pre = L.elem[i-1], flag = 1;
        }
    }
    if(flag) return 1;
    else return 0;
}

// 9:获取元素e的后继
status NextElem(SqList L, ElemType e, ElemType &next)
{
    if(L.elem == NULL) return -1;
    int flag = 0;
    for(int i = 0; i < L.length; i++)
    {
        if(e == L.elem[i])
        {
            if(i == L.length-1) return 0;
            else next = L.elem[i+1], flag = 1;
        }
    }
    if(flag) return 1;
    else return 0;
}

// 10:插入元素e到第i个位置
status ListInsert(SqList &L, int i, ElemType e)
{
    if(L.elem == NULL) return -1;
    if(L.length == L.listsize)
    {
        L.elem = (ElemType*) realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
        if(!L.elem) return 0;
        L.listsize += LISTINCREMENT;
    }
    if(i > L.length+1 || i == 0) return 0;
    for(int j = L.length; j >= i; j--) L.elem[j] = L.elem[j-1];
    L.elem[i-1] = e;
    L.length++;
    return 1;
}

// 11:删除第i个元素
status ListDelete(SqList &L, int i, ElemType &e)
{
    if(L.elem == NULL)
    {
        printf("      线性表不存在！\n");
        return -1; // 线性表不存在
    }
    if(L.length < i || i < 1 ) return 0;
    e = L.elem[i-1];
    L.length--;
    for(int j = i-1; j < L.length; j++)
    {
        L.elem[j] = L.elem[j+1];
    }
    return 1;
}

// 12:遍历线性表并输出
status ListTrabverse(SqList L)
{
    if(L.elem == NULL)
    {
        printf("      线性表不存在！\n");
        return 0; // 线性表不存在
    }
    printf("      是否详细显示？(1:是 0:否):");
    int showIndex;
    scanf("%d", &showIndex);
    if(showIndex)
    {
        printf("      线性表的长度为%d：\n" , L.length);
        printf("      ");
        for(int i = 0; i < L.length; i++)
        {
            printf("%d:%d", i, L.elem[i]);
            if(i != L.length - 1) putchar(' ');
        }
        putchar('\n');
    }
    else{
        printf("      线性表的元素为：\n");
        printf("      ");
        for(int i = 0; i < L.length; i++)
        {
            printf("%d", L.elem[i]);
            if(i != L.length - 1) putchar(' ');
        }
        putchar('\n');
    }
    return 1;
}

// 13: 快速插入线性表:
status ListInsertFast(SqList &L)
{
    if(L.elem == NULL)
    {
        printf("      线性表不存在！\n");
        return 0; // 线性表不存在
    }
    ElemType e;
    printf("      当前线性表长度为%d\n", L.length);
    printf("      请输入插入元素(非数字结束):");
    while(scanf("%d", &e) == 1)
    {
        putchar('\n');
        // 引用ListInsert函数插入元素
        if(ListInsert(L, L.length+1, e) == 0)
        {
            printf("      插入失败！\n");
            return 0;
        }
        printf("      插入成功！当前线性表长度为:%d\n", L.length);
        printf("      请输入插入元素(非数字结束):");
    }
    return OK;
}
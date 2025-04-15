/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

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
    ElemType *elem = NULL;
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


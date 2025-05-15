#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

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
typedef struct {
    ElemType* elem;
    int length;
    int listsize;
}SqList;

status InitList(SqList& L) {
    if (L.elem != NULL)
        return INFEASIBLE;
    L.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    return OK;
}

status DestroyList(SqList& L) {
    if (L.elem != NULL) {
        free(L.elem);
        L.length = 0;
        L.listsize = LIST_INIT_SIZE;
        L.elem = NULL;
        return OK;
    }
    return INFEASIBLE;
}

status ClearList(SqList& L) {
    if (L.elem != NULL) {
        L.length = 0;
        return OK;
    }
    return INFEASIBLE;
}

status ListEmpty(SqList L) {
    if (L.elem != NULL) {
        if (L.length == 0) return TRUE;
        return FALSE;
    }
    return INFEASIBLE;
}

status ListLength(SqList L) {
    if (L.elem != NULL)
        return L.length;
    return INFEASIBLE;
}

status GetElem(SqList L, int i, ElemType& e) {
    if (L.elem != NULL) {
        if (i > 0 && i <= L.length) {
            e = L.elem[i - 1];
            return OK;
        }
        return ERROR;
    }
    return INFEASIBLE;
}

int LocateElem(SqList L, ElemType e) {
    if (L.elem != NULL) {
        for (int i = 0; i < L.length; i++) {
            if (L.elem[i] == e) return i + 1;
        }
        return 0;
    }
    return INFEASIBLE;
}

status PriorElem(SqList L, ElemType e, ElemType& pre) {
    if (L.elem != NULL) {
        for (int i = 0; i < L.length; i++) {
            if (L.elem[i] == e) {
                if (i == 0) return ERROR;
                pre = L.elem[i - 1];
                return OK;
            }
        }
        return ERROR;
    }
    return INFEASIBLE;
}

status NextElem(SqList L, ElemType e, ElemType& next) {
    if (L.elem != NULL) {
        for (int i = 0; i < L.length; i++) {
            if (L.elem[i] == e) {
                if (i == L.length || i == L.length - 1) return ERROR;
                next = L.elem[i + 1];
                return OK;
            }
        }
        return ERROR;
    }
    return INFEASIBLE;
}

status ListInsert(SqList& L, int i, ElemType e) {
    if (L.elem == NULL)
        return INFEASIBLE;
    if (i < 1 || i > L.length + 1)
        return ERROR;
    if (L.length >= L.listsize) {
        int newSize = L.listsize + LISTINCREMENT;
        ElemType* newBase = (ElemType*)realloc(L.elem, newSize * sizeof(ElemType));
        if (!newBase)
            return ERROR;
        L.elem = newBase;
        L.listsize = newSize;
    }
    for (int j = L.length; j >= i; j--)
        L.elem[j] = L.elem[j - 1];
    L.elem[i - 1] = e;
    L.length++;
    return OK;
}

status ListDelete(SqList& L, int i, ElemType& e) {
    if (L.elem == NULL)
        return INFEASIBLE;
    if (i < 1 || i > L.length)
        return ERROR;
    e = L.elem[i - 1];
    for (int j = i - 1; j < L.length - 1; j++)
        L.elem[j] = L.elem[j + 1];
    L.length--;
    return OK;
}

status ListTrabverse(SqList L) {
    if (L.elem == NULL)
        return INFEASIBLE;
    for (int i = 0; i < L.length; i++) {
        if (i > 0)
            printf(" ");
        printf("%d", L.elem[i]);
    }
    return OK;
}

//附加功能1
status MaxSubArray(SqList L, ElemType& maxSum) {
    if (L.elem == NULL || L.length == 0) return INFEASIBLE;
    maxSum = L.elem[0];
    ElemType currentSum = 0;
    for (int i = 0; i < L.length; i++) {
        currentSum = (currentSum > 0) ? currentSum + L.elem[i] : L.elem[i];
        if (currentSum > maxSum) maxSum = currentSum;
    }
    return OK;
}

//附加功能2
status SubArrayNum(SqList L, ElemType k, int& count) {
    if (L.elem == NULL || L.length == 0) return INFEASIBLE;
    count = 0;
    for (int i = 0; i < L.length; i++) {
        ElemType sum = 0;
        for (int j = i; j < L.length; j++) {
            sum += L.elem[j];
            if (sum == k) count++;
        }
    }
    return OK;
}

//附加功能3
status sortList(SqList& L) {
    if (L.elem == NULL || L.length == 0) return INFEASIBLE;
    for (int i = 0; i < L.length - 1; i++) {
        for (int j = 0; j < L.length - i - 1; j++) {
            if (L.elem[j] > L.elem[j + 1]) {
                ElemType temp = L.elem[j];
                L.elem[j] = L.elem[j + 1];
                L.elem[j + 1] = temp;
            }
        }
    }
    return OK;
}

//附加功能4
status SaveListToFile(SqList L, const char* filename) {
    if (L.elem == NULL) return INFEASIBLE;
    FILE* file = fopen(filename, "wb");
    if (!file) return ERROR;
    fwrite(&L.length, sizeof(int), 1, file);
    fwrite(L.elem, sizeof(ElemType), L.length, file);
    fclose(file);
    return OK;
}

status LoadListFromFile(SqList& L, const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) return ERROR;
    int length;
    fread(&length, sizeof(int), 1, file);
    ElemType* data = (ElemType*)malloc(length * sizeof(ElemType));
    if (!data) {
        fclose(file);
        return OVERFLOW;
    }
    fread(data, sizeof(ElemType), length, file);
    fclose(file);
    if (L.elem != NULL) free(L.elem);
    L.elem = data;
    L.length = length;
    L.listsize = length;
    return OK;
}

//附加功能5
typedef struct {
    char name[20];
    SqList L;
} NamedList;

typedef struct {
    NamedList elem[10];
    int length;
} LISTS;

status AddList(LISTS& Lists, char ListName[]) {
    if (Lists.length >= 10) return ERROR;

    int i = 0;
    while (ListName[i] != '\0') {
        Lists.elem[Lists.length].name[i] = ListName[i];
        i++;
    }
    Lists.elem[Lists.length].name[i] = '\0';

    if (Lists.elem[Lists.length].L.elem != NULL) {
        DestroyList(Lists.elem[Lists.length].L);
    }

    if (InitList(Lists.elem[Lists.length].L) != OK) return ERROR;
    Lists.length++;
    return OK;
}

status RemoveList(LISTS& Lists, char ListName[]) {
    int index = -1;
    for (int i = 0; i < Lists.length; i++) {
        if (strcmp(Lists.elem[i].name, ListName) == 0) {
            index = i;
            break;
        }
    }
    if (index == -1) return ERROR;

    // 销毁线性表，释放内存
    DestroyList(Lists.elem[index].L);

    for (int j = index; j < Lists.length - 1; j++) {
        Lists.elem[j] = Lists.elem[j + 1];
    }
    Lists.length--;
    return OK;
}

int LocateList(LISTS Lists, char ListName[]) {
    for (int i = 0; i < Lists.length; i++) {
        if (strcmp(Lists.elem[i].name, ListName) == 0) return i + 1;
    }
    return 0;
}

void main(void) {
    SqList L = { NULL, 0, 0 };
    LISTS Lists = { 0 };
    int currentListIndex = -1;
    char Lname[30];
    int op = 1;
    while (op) {
        system("cls");
        printf("\n\n");
        printf("      Menu for Linear Table On Sequence Structure \n");
        printf("-------------------------------------------------\n");
        printf("          1. InitList       11. ListDelete\n");
        printf("    	  2. DestroyList    12. ListTrabverse\n");
        printf("    	  3. ClearList      13. MaxSubArray\n");
        printf("    	  4. ListEmpty      14. SubArrayNum\n");
        printf("    	  5. ListLength     15. sortList\n");
        printf("    	  6. GetElem        16. SaveListToFile\n");
        printf("    	  7. LocateElem     17. LoadListFromFile\n");
        printf("    	  8. PriorElem      18. AddList\n");
        printf("    	  9. NextElem       19. RemoveList\n");
        printf("    	  10. ListInsert    20. LocateList\n");
        printf("    	  21. SwitchList\n");
        printf("    	  0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~21]:");
        scanf("%d", &op);
        switch (op) {
        case 1:
            if (InitList(L) == OK) {
                printf("线性表创建成功！\n");
                Lists.elem[currentListIndex].L = L;
            }
            else {
                printf("线性表已存在，无法再次创建！\n");
            }
            getchar(); getchar();
            break;
        case 2:
            if (DestroyList(L) == OK) printf("线性表销毁成功！\n");
            else printf("线性表销毁失败！\n");
            getchar(); getchar();
            break;
        case 3:
            if (ClearList(L) == OK) printf("线性表清空成功！\n");
            else printf("线性表清空失败！\n");
            getchar(); getchar();
            break;
        case 4:
            if (ListEmpty(L) == TRUE) printf("线性表为空！\n");
            else printf("线性表不为空！\n");
            getchar(); getchar();
            break;
        case 5:
            printf("线性表长度为：%d\n", ListLength(L));
            getchar(); getchar();
            break;
        case 6: {
            int i;
            ElemType e;
            printf("请输入要获取的元素位置：");
            scanf("%d", &i);
            if (GetElem(L, i, e) == OK) printf("第%d个元素为：%d\n", i, e);
            else printf("获取元素失败！\n");
            getchar(); getchar();
            break;
        }
        case 7: {
            ElemType e;
            printf("请输入要查找的元素值：");
            scanf("%d", &e);
            int pos = LocateElem(L, e);
            if (pos > 0) printf("元素%d的位置为：%d\n", e, pos);
            else printf("元素不存在！\n");
            getchar(); getchar();
            break;
        }
        case 8: {
            ElemType e, pre;
            printf("请输入要查找前驱的元素值：");
            scanf("%d", &e);
            if (PriorElem(L, e, pre) == OK) printf("元素%d的前驱为：%d\n", e, pre);
            else printf("获取前驱失败！\n");
            getchar(); getchar();
            break;
        }
        case 9: {
            ElemType e, next;
            printf("请输入要查找后继的元素值：");
            scanf("%d", &e);
            if (NextElem(L, e, next) == OK) printf("元素%d的后继为：%d\n", e, next);
            else printf("获取后继失败！\n");
            getchar(); getchar();
            break;
        }
        case 10: {
            printf("在何处插入何元素:");
            int j;
            ElemType d;
            scanf("%d %d", &j, &d);
            if (ListInsert(L, j, d) == OK) {
                printf("插入成功！");
                Lists.elem[currentListIndex].L = L;
            }
            else if (ListInsert(L, j, d) == INFEASIBLE) {
                printf("线性表不存在！\n");
            }
            else {
                printf("插入位置选取有误！\n");
            }
            getchar(); getchar();
            break;
        }
        case 11: {
            int i;
            ElemType e;
            printf("请输入删除位置：");
            scanf("%d", &i);
            if (ListDelete(L, i, e) == OK) printf("删除成功，删除的元素为：%d\n", e);
            else printf("删除失败！\n");
            getchar(); getchar();
            break;
        }
        case 12:
            if (ListTrabverse(L) == INFEASIBLE) printf("线性表是空表！\n");
            getchar(); getchar();
            break;
        case 13: {
            ElemType maxSum;
            if (MaxSubArray(L, maxSum) == OK) printf("最大连续子数组和为：%d\n", maxSum);
            else printf("操作失败！\n");
            getchar(); getchar();
            break;
        }
        case 14: {
            ElemType k;
            int count;
            printf("请输入目标和k：");
            scanf("%d", &k);
            if (SubArrayNum(L, k, count) == OK) printf("和为%d的子数组个数为：%d\n", k, count);
            else printf("操作失败！\n");
            getchar(); getchar();
            break;
        }
        case 15:
            if (sortList(L) == OK) printf("排序成功！\n");
            else printf("排序失败！\n");
            getchar(); getchar();
            break;
        case 16: {
            char filename[50];
            printf("请输入保存文件名：");
            scanf("%s", filename);
            if (SaveListToFile(L, filename) == OK) printf("保存成功！\n");
            else printf("保存失败！\n");
            getchar(); getchar();
            break;
        }
        case 17: {
            char filename[50];
            printf("请输入加载文件名：");
            scanf("%s", filename);
            if (LoadListFromFile(L, filename) == OK) printf("加载成功！\n");
            else printf("加载失败！\n");
            getchar(); getchar();
            break;
        }
        case 18: {
            char name[20];
            printf("请输入新线性表名称：");
            scanf("%s", name);
            if (AddList(Lists, name) == OK) {
                printf("添加成功！\n");
            }
            else printf("添加失败！\n");
            getchar(); getchar();
            break;
        }
        case 19: {
            char name[20];
            printf("请输入要移除的线性表名称：");
            scanf("%s", name);
            if (RemoveList(Lists, name) == OK) printf("移除成功！\n");
            else printf("移除失败！\n");
            getchar(); getchar();
            break;
        }
        case 20: {
            char name[20];
            printf("请输入要查找的线性表名称：");
            scanf("%s", name);
            int pos = LocateList(Lists, name);
            if (pos > 0) printf("线性表位置为：%d\n", pos);
            else printf("线性表不存在！\n");
            getchar(); getchar();
            break;
        }
        case 21: {
            printf("请输入要切换的线性表名称：\n");
            char name[30];
            scanf("%s", name);

            int pos = LocateList(Lists, name);
            if (pos > 0) {
                currentListIndex = pos - 1;
                strcpy(Lname, Lists.elem[currentListIndex].name);
                L = Lists.elem[currentListIndex].L;
                printf("已切换到线性表：%s\n", Lname);
            }
            else {
                printf("线性表不存在！\n");
            }
            getchar(); getchar();
            break;
        }
        case 0:
            break;
        }
    }
    printf("欢迎下次再使用本系统！\n");
}
#include <stdio.h>
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

typedef struct LNode {
    ElemType data;
    struct LNode* next;
} LNode, * LinkList;

typedef struct {
    char name[30];
    LinkList L;
} NamedList;

typedef struct {
    NamedList lists[10];
    int count;
} ListManager;

status InitList(LinkList& L) {
    if (L != NULL) return INFEASIBLE;
    L = new LNode();
    L->next = NULL;
    return OK;
}

status DestroyList(LinkList& L) {
    if (L == NULL) return INFEASIBLE;
    LNode* p = L;
    while (p != NULL) {
        LNode* temp = p;
        p = p->next;
        free(temp);
    }
    L = NULL;
    return OK;
}

status ClearList(LinkList& L) {
    if (L == NULL) return INFEASIBLE;
    LNode* p = L->next;
    while (p != NULL) {
        LNode* temp = p;
        p = p->next;
        free(temp);
    }
    L->next = NULL;
    return OK;
}

status ListEmpty(LinkList L) {
    if (L == NULL) return INFEASIBLE;
    return L->next == NULL ? TRUE : FALSE;
}

int ListLength(LinkList L) {
    if (L == NULL) return INFEASIBLE;
    int length = 0;
    LNode* p = L->next;
    while (p != NULL) {
        length++;
        p = p->next;
    }
    return length;
}

status GetElem(LinkList L, int i, ElemType& e) {
    if (L == NULL) return INFEASIBLE;
    if (i < 1) return ERROR;
    LNode* p = L->next;
    int index = 1;
    while (p != NULL && index < i) {
        p = p->next;
        index++;
    }
    if (p == NULL || index > i) return ERROR;
    e = p->data;
    return OK;
}

status LocateElem(LinkList L, ElemType e) {
    if (L == NULL) return INFEASIBLE;
    LNode* p = L->next;
    int index = 1;
    while (p != NULL) {
        if (p->data == e) return index;
        p = p->next;
        index++;
    }
    return ERROR;
}

status PriorElem(LinkList L, ElemType e, ElemType& pre) {
    if (L == NULL) return INFEASIBLE;
    LNode* p = L->next;
    while (p != NULL && p->next != NULL) {
        if (p->next->data == e) {
            pre = p->data;
            return OK;
        }
        p = p->next;
    }
    return ERROR;
}

status NextElem(LinkList L, ElemType e, ElemType& next) {
    if (L == NULL) return INFEASIBLE;
    LNode* p = L->next;
    while (p != NULL) {
        if (p->data == e && p->next != NULL) {
            next = p->next->data;
            return OK;
        }
        p = p->next;
    }
    return ERROR;
}

status ListInsert(LinkList& L, int i, ElemType e) {
    if (L == NULL) return INFEASIBLE;
    if (i < 1) return ERROR;
    LNode* p = L;
    int index = 0;
    while (p != NULL && index < i - 1) {
        p = p->next;
        index++;
    }
    if (p == NULL) return ERROR;
    LNode* newNode = (LNode*)malloc(sizeof(LNode));
    if (newNode == NULL) return ERROR;
    newNode->data = e;
    newNode->next = p->next;
    p->next = newNode;
    return OK;
}

status ListDelete(LinkList& L, int i, ElemType& e) {
    if (L == NULL) return INFEASIBLE;
    if (i < 1) return ERROR;
    LNode* p = L;
    int index = 0;
    while (p->next != NULL && index < i - 1) {
        p = p->next;
        index++;
    }
    if (p->next == NULL || index > i - 1) return ERROR;
    LNode* q = p->next;
    e = q->data;
    p->next = q->next;
    free(q);
    return OK;
}

status ListTraverse(LinkList L) {
    if (L == NULL) return INFEASIBLE;
    LNode* p = L->next;
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}

status reverseList(LinkList& L) {
    if (L == NULL || L->next == NULL) return INFEASIBLE;
    LNode* prev = NULL, * curr = L->next, * next = NULL;
    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    L->next = prev;
    return OK;
}

status RemoveNthFromEnd(LinkList& L, int n) {
    if (L == NULL || n < 1) return INFEASIBLE;
    LNode* dummy = new LNode();
    dummy->next = L->next;
    LNode* fast = dummy, * slow = dummy;
    for (int i = 0; i <= n; i++) {
        if (fast == NULL) return ERROR;
        fast = fast->next;
    }
    while (fast != NULL) {
        fast = fast->next;
        slow = slow->next;
    }
    LNode* toDelete = slow->next;
    slow->next = toDelete->next;
    free(toDelete);
    L->next = dummy->next;
    delete dummy;
    return OK;
}

status sortList(LinkList& L) {
    if (L == NULL || L->next == NULL) return INFEASIBLE;
    for (LNode* i = L->next; i != NULL; i = i->next) {
        for (LNode* j = i->next; j != NULL; j = j->next) {
            if (i->data > j->data) {
                ElemType temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
    return OK;
}

status SaveList(LinkList L, const char* filename) {
    if (L == NULL) return INFEASIBLE;
    FILE* file = fopen(filename, "w");
    if (!file) return ERROR;
    LNode* p = L->next;
    while (p != NULL) {
        fprintf(file, "%d ", p->data);
        p = p->next;
    }
    fclose(file);
    return OK;
}

status LoadList(LinkList& L, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return ERROR;
    DestroyList(L);
    InitList(L);
    ElemType e;
    while (fscanf(file, "%d", &e) != EOF) {
        ListInsert(L, ListLength(L) + 1, e);
    }
    fclose(file);
    return OK;
}

status AddList(ListManager& manager, const char* name) {
    if (manager.count >= 10) return ERROR;
    for (int i = 0; i < manager.count; i++) {
        if (strcmp(manager.lists[i].name, name) == 0) return ERROR;
    }
    strcpy(manager.lists[manager.count].name, name);
    InitList(manager.lists[manager.count].L);
    manager.count++;
    return OK;
}

status RemoveList(ListManager& manager, const char* name) {
    int index = -1;
    for (int i = 0; i < manager.count; i++) {
        if (strcmp(manager.lists[i].name, name) == 0) {
            index = i;
            break;
        }
    }
    if (index == -1) return ERROR;
    DestroyList(manager.lists[index].L);
    for (int i = index; i < manager.count - 1; i++) {
        manager.lists[i] = manager.lists[i + 1];
    }
    manager.count--;
    return OK;
}

status SwitchList(ListManager& manager, const char* name, LinkList& currentList) {
    for (int i = 0; i < manager.count; i++) {
        if (strcmp(manager.lists[i].name, name) == 0) {
            currentList = manager.lists[i].L;
            return OK;
        }
    }
    return ERROR;
}

void main(void) {
    ListManager manager = { 0 };
    LinkList currentList = NULL;
    int op = 1;
    while (op) {
        system("cls");
        printf("\n\n");
        printf("      Menu for Linear Table On Linked Structure \n");
        printf("-------------------------------------------------\n");
        printf("    	  1. InitList       2. DestroyList\n");
        printf("    	  3. ClearList      4. ListEmpty\n");
        printf("    	  5. ListLength     6. GetElem \n");
        printf("    	  7. LocateElem     8. PriorElem\n");
        printf("    	  9. NextElem       10. ListInsert\n");
        printf("    	  11. ListDelete    12. ListTraverse\n");
        printf("    	  13. ReverseList   14. RemoveNthFromEnd\n");
        printf("    	  15. SortList      16. SaveList\n");
        printf("    	  17. LoadList      18. AddList\n");
        printf("    	  19. RemoveList    20. SwitchList\n");
        printf("    	  0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~20]:");
        scanf("%d", &op);
        switch (op) {
        case 1:
            if (InitList(currentList) == OK) printf("线性表创建成功！\n");
            else printf("线性表创建失败！\n");
            getchar(); getchar();
            break;
        case 2:
            if (DestroyList(currentList) == OK) printf("线性表销毁成功！\n");
            else printf("线性表销毁失败！\n");
            getchar(); getchar();
            break;
        case 3:
            if (ClearList(currentList) == OK) printf("线性表清空成功！\n");
            else printf("线性表清空失败！\n");
            getchar(); getchar();
            break;
        case 4:
            if (ListEmpty(currentList) == TRUE) printf("线性表为空！\n");
            else if (ListEmpty(currentList) == FALSE) printf("线性表不为空！\n");
            else printf("线性表不存在！\n");
            getchar(); getchar();
            break;
        case 5:
            int len;
            len = ListLength(currentList);
            if (len != INFEASIBLE) printf("线性表长度为：%d\n", len);
            else printf("线性表不存在！\n");
            getchar(); getchar();
            break;
        case 6: {
            int i;
            ElemType e;
            printf("请输入要获取的元素位置：");
            scanf("%d", &i);
            if (GetElem(currentList, i, e) == OK) printf("第%d个元素为：%d\n", i, e);
            else printf("获取元素失败！\n");
            getchar(); getchar();
            break;
        }
        case 7: {
            ElemType e;
            printf("请输入要查找的元素值：");
            scanf("%d", &e);
            int pos = LocateElem(currentList, e);
            if (pos > 0) printf("元素%d的位置为：%d\n", e, pos);
            else printf("元素不存在！\n");
            getchar(); getchar();
            break;
        }
        case 8: {
            ElemType cur, pre;
            printf("请输入要查找前驱的元素值：");
            scanf("%d", &cur);
            if (PriorElem(currentList, cur, pre) == OK) printf("元素%d的前驱为：%d\n", cur, pre);
            else printf("获取前驱失败！\n");
            getchar(); getchar();
            break;
        }
        case 9: {
            ElemType cur, next;
            printf("请输入要查找后继的元素值：");
            scanf("%d", &cur);
            if (NextElem(currentList, cur, next) == OK) printf("元素%d的后继为：%d\n", cur, next);
            else printf("获取后继失败！\n");
            getchar(); getchar();
            break;
        }
        case 10: {
            int i;
            ElemType e;
            printf("请输入插入位置和元素值：");
            scanf("%d %d", &i, &e);
            if (ListInsert(currentList, i, e) == OK) printf("插入成功！\n");
            else printf("插入失败！\n");
            getchar(); getchar();
            break;
        }
        case 11: {
            int i;
            ElemType e;
            printf("请输入删除位置：");
            scanf("%d", &i);
            if (ListDelete(currentList, i, e) == OK) printf("删除成功，删除的元素为：%d\n", e);
            else printf("删除失败！\n");
            getchar(); getchar();
            break;
        }
        case 12:
            if (ListTraverse(currentList) == INFEASIBLE) printf("线性表不存在！\n");
            getchar(); getchar();
            break;
        case 13:
            if (reverseList(currentList) == OK) printf("链表翻转成功！\n");
            else printf("链表翻转失败！\n");
            getchar(); getchar();
            break;
        case 14: {
            int n;
            printf("请输入要删除的倒数第n个节点：");
            scanf("%d", &n);
            if (RemoveNthFromEnd(currentList, n) == OK) printf("删除成功！\n");
            else printf("删除失败！\n");
            getchar(); getchar();
            break;
        }
        case 15:
            if (sortList(currentList) == OK) printf("链表排序成功！\n");
            else printf("链表排序失败！\n");
            getchar(); getchar();
            break;
        case 16: {
            char filename[50];
            printf("请输入保存文件名：");
            scanf("%s", filename);
            if (SaveList(currentList, filename) == OK) printf("保存成功！\n");
            else printf("保存失败！\n");
            getchar(); getchar();
            break;
        }
        case 17: {
            char filename[50];
            printf("请输入加载文件名：");
            scanf("%s", filename);
            if (LoadList(currentList, filename) == OK) printf("加载成功！\n");
            else printf("加载失败！\n");
            getchar(); getchar();
            break;
        }
        case 18: {
            char name[30];
            printf("请输入新线性表名称：");
            scanf("%s", name);
            if (AddList(manager, name) == OK) printf("添加成功！\n");
            else printf("添加失败！\n");
            getchar(); getchar();
            break;
        }
        case 19: {
            char name[30];
            printf("请输入要移除的线性表名称：");
            scanf("%s", name);
            if (RemoveList(manager, name) == OK) printf("移除成功！\n");
            else printf("移除失败！\n");
            getchar(); getchar();
            break;
        }
        case 20: {
            char name[30];
            printf("请输入要切换的线性表名称：");
            scanf("%s", name);
            if (SwitchList(manager, name, currentList) == OK) printf("切换成功！\n");
            else printf("切换失败！\n");
            getchar(); getchar();
            break;
        }
        case 0:
            break;
        }
    }
    printf("欢迎下次再使用本系统！\n");
}
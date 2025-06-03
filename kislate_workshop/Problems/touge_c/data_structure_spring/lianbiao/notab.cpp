#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <windows.h>

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
    struct LNode *next;
} LNode, *LinkList;

typedef struct {
    struct {
        char name[30];
        LinkList L;
    } elem[10];
    int length;
} LLISTS;


status InitList(LinkList &L) {
    if(L != NULL) return INFEASIBLE;
    L = (LinkList)malloc(sizeof(LNode));
    if(L == NULL) return OVERFLOW;
    L->next = NULL;
    return OK;
}

status DestroyList(LinkList &L) {
    if(L == NULL) return INFEASIBLE;
    LinkList p, q;
    p = L->next;
    while(p != NULL){
        q = p->next;
        free(p);
        p = q;
    }
    free(L);
    L = NULL;
    return OK;
}

status ClearList(LinkList &L) {
    if(L == NULL) return INFEASIBLE;
    LinkList p, q;
    p = L->next;
    while(p != NULL){
        q = p->next;
        free(p);
        p = q;
    }
    L->next = NULL;
    return OK;
}

status ListEmpty(LinkList L) {
    if(L == NULL) return INFEASIBLE;
    if(L->next == NULL) return TRUE;
    return FALSE;
}

int ListLength(LinkList L) {
    if(L == NULL) return INFEASIBLE;
    int length = 0;
    LinkList p = L->next;
    while(p != NULL){
        length++;
        p = p->next;
    }
    return length;
}

status GetElem(LinkList L,int i,ElemType &e) {
    if(L == NULL) return INFEASIBLE;
    if(i < 1) return ERROR;
    LinkList p = L->next;
    int cnt = 1;
    while(p != NULL && cnt < i){
        p = p->next;
        cnt++;
    }
    if(p == NULL) return ERROR;
    e = p->data;
    return OK;
}

status LocateElem(LinkList L,ElemType e) {
    if(L == NULL) return INFEASIBLE;
    LinkList p = L->next;
    int cnt = 1;
    while(p != NULL){
        if(p->data == e) return cnt;
        p = p->next;
        cnt++;
    }
    return ERROR;
}

status PriorElem(LinkList L,ElemType e,ElemType &pre) {
    if(L == NULL) return INFEASIBLE;
    LinkList p = L->next;
    LinkList q = NULL;
    while(p != NULL){
        if(p->data == e){
            if(q == NULL) return ERROR;
            pre = q->data;
            return OK;
        }
        q = p;
        p = p->next;
    }
    return ERROR;
}

status NextElem(LinkList L,ElemType e,ElemType &next) {
    if(L == NULL) return INFEASIBLE;
    LinkList p = L->next;
    while(p != NULL){
        if(p->data == e){
            if(p->next == NULL) return ERROR;
            next = p->next->data;
            return OK;
        }
        p = p->next;
    }
    return ERROR;
}

status ListInsert(LinkList &L,int i,ElemType e) {
    if(L == NULL) return INFEASIBLE;
    if(i < 1) return ERROR;
    LinkList p = L;
    int cnt = 1;
    while(p != NULL && cnt < i){
        p = p->next;
        cnt++;
    }
    if(p == NULL) return ERROR;
    LinkList newNode = (LinkList)malloc(sizeof(LNode));
    if(newNode == NULL) return OVERFLOW;
    newNode->data = e;
    newNode->next = p->next;
    p->next = newNode;
    return OK;
}

status ListDelete(LinkList &L,int i,ElemType &e) {
    if(L == NULL) return INFEASIBLE;
    if(i < 1) return ERROR;
    LinkList p = L;
    int cnt = 1;
    while(p != NULL && cnt < i){
        p = p->next;
        cnt++;
    }
    if(p == NULL || p->next == NULL) return ERROR;
    e = p->next->data;
    LinkList q = p->next;
    p->next = p->next->next;
    free(q);
    q = NULL;
    return OK;
}

status ListTraverse(LinkList L) {
    if(L == NULL) return INFEASIBLE;
    LinkList p = L->next;
    printf("      线性表元素为：\n");// new
    printf("      ");
    while(p != NULL) {
        printf("%d", p->data);
        if(p->next != NULL) printf(" ");
        p = p->next;
    }
    printf("\n");
    return OK;
}

status  ListInsertTail(LinkList &L, ElemType e){
    if(L == NULL) return INFEASIBLE;
    LinkList p = L;
    int cnt = 1;
    while(p->next != NULL) p = p->next, cnt++;
    LinkList newNode = (LinkList)malloc(sizeof(LNode));
    if(newNode == NULL) return OVERFLOW;
    newNode->data = e;
    newNode->next = NULL;
    p->next = newNode;
    return OK;
}

// ========== 附加功能 ==========
// 链表翻转
status reverseList(LinkList &L) {
    if(L == NULL) return INFEASIBLE;
    LinkList prev = NULL, curr = L->next, next;
    while(curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    L->next = prev;
    return OK;
}

// 删除倒数第n个结点
status RemoveNthFromEnd(LinkList &L, int n) {
    if(L == NULL) return INFEASIBLE;
    LinkList fast = L, slow = L;
    for(int i = 0; i < n; i++) {
        if(fast->next == NULL) return ERROR;
        fast = fast->next;
    }
    while(fast->next) {
        fast = fast->next;
        slow = slow->next;
    }
    printf("      删除的元素为：%d\n", slow->next->data);
    LinkList toDel = slow->next;
    if(toDel == NULL) return ERROR;
    slow->next = toDel->next;
    free(toDel);
    return OK;
}

// 链表排序（冒泡）
status sortList(LinkList &L) {
    if(L == NULL) return INFEASIBLE;
    int len = ListLength(L);
    if(len <= 1) return OK;
    for(int i = 0; i < len - 1; i++) {
        LinkList p = L->next, q = p->next;
        for(int j = 0; j < len - i - 1; j++) {
            if(q && p->data > q->data) {
                int t = p->data; p->data = q->data; q->data = t;
            }
            p = p->next;
            if(q) q = q->next;
        }
    }
    return OK;
}

// 文件保存
status SaveList(LinkList L, char FileName[]) {
    if(L == NULL) return INFEASIBLE;
    FILE *fp = fopen(FileName, "wb");
    if(fp == NULL) return ERROR;
    LinkList p = L->next;
    while(p != NULL){
        fwrite(&p->data, sizeof(ElemType), 1, fp);
        p = p->next;
    }
    fclose(fp);
    return OK;
}

// 文件加载
status LoadList(LinkList &L, char FileName[]) {
    if(L != NULL) 
    {
        printf("      链表已存在，是否销毁后导入?(1: 销毁, 2: 取消加载)\n");
        int op;
        scanf("%d", &op);
        if(op == 1) 
        {
            if(DestroyList(L) == OK) printf("      链表销毁成功！\n");
            else{
                printf("      链表销毁失败！\n");
                return ERROR;
            }
        }
        else return ERROR;
    }
    FILE *fp = fopen(FileName, "rb");
    if(fp == NULL) return ERROR;
    L = (LinkList)malloc(sizeof(LNode));
    if(L == NULL) return OVERFLOW;
    L->next = NULL;
    LinkList p = L;
    ElemType temp;
    while(fread(&temp, sizeof(ElemType), 1, fp) == 1){
        LinkList newNode = (LinkList)malloc(sizeof(LNode));
        if(newNode == NULL) return OVERFLOW;
        newNode->data = temp;
        newNode->next = NULL;
        p->next = newNode;
        p = p->next;
    }
    fclose(fp);
    return OK;
}

// ========== 多链表管理 ==========

status AddList(LLISTS &Lists, char ListName[]) {
    for(int i = 0; i < Lists.length; i++) {
        if(strcmp(Lists.elem[i].name, ListName) == 0) {
            printf("      线性表名重复！\n");
            return ERROR;
        }
    }
    if(Lists.length >= 10) {
        printf("      线性表数量已达上限！\n");
        return ERROR;
    }
    Lists.elem[Lists.length].L = NULL;
    InitList(Lists.elem[Lists.length].L);
    strcpy(Lists.elem[Lists.length].name, ListName);
    Lists.length++;
    return OK;
}
status RemoveList(LLISTS &Lists, char ListName[]) {
    if(Lists.length == 0) return ERROR;
    int i = 0;
    for(i = 0; i < Lists.length; i++) {
        if(strcmp(Lists.elem[i].name, ListName) == 0) break;
    }
    if(i == Lists.length) return ERROR;
    DestroyList(Lists.elem[i].L);
    for(int j = i; j < Lists.length - 1; j++) {
        Lists.elem[j] = Lists.elem[j + 1];
    }
    Lists.length--;
    return OK;
}
int LocateList(LLISTS Lists, char ListName[]) {
    if(Lists.length == 0 ) return 0;
    for(int i = 0; i < Lists.length; i++) {
        if(strcmp(Lists.elem[i].name, ListName) == 0) return i + 1;
    }
    return ERROR;
}
void printAllListNames(LLISTS &Lists) {
    printf("      当前已有线性表数量：%d\n", Lists.length);
    for(int i = 0; i < Lists.length; i++) {
        printf("      %d. %s\n", i+1, Lists.elem[i].name);
    }
}

// ========== 单链表菜单 ==========

void singleListMenu() {
    printf("\n");
    printf("      ========== 单链表操作菜单 ==========\n");
    printf("      1. InitList          7. LocateElem\n");
    printf("      2. DestroyList       8. PriorElem\n");
    printf("      3. ClearList         9. NextElem \n");
    printf("      4. ListEmpty        10. ListInsert\n");
    printf("      5. ListLength       11. ListDelete\n");
    printf("      6. GetElem          12. ListTraverse\n");
    printf("      13. 链表翻转         14. 删除倒数第n个结点\n");
    printf("      15. 链表排序         16. 保存到文件\n");
    printf("      17. 从文件加载       18. 快速插入\n");
    printf("      0. 返回多表\n");
    printf("      =====================================\n");
    printf("      请选择你的操作[0~18]:");
}

void singleListControl(LinkList &L) {
    int op = 1;
    ElemType e, pre, next;
    int pos, loc, n;
    char filename[100];
    status result;
    while(op) {
        system("cls");
        singleListMenu();
        scanf("%d", &op);
        switch(op) {
            case 1:
                if(InitList(L)==OK) printf("      链表创建成功！\n");
                else printf("      链表创建失败！\n");
                getchar();
                printf("      按任意键继续...\n");
                getchar();
                break;
            case 2:
                if(DestroyList(L)==OK) printf("      链表销毁成功！\n");
                else printf("      链表销毁失败！\n");
                getchar(); 
                printf("      按任意键继续...\n");
                getchar();
                break;
            case 3:
                if(ClearList(L)==OK) printf("      链表清空成功！\n");
                else printf("      链表清空失败！\n");
                getchar(); 
                printf("      按任意键继续...\n");
                getchar();
                break;
            case 4:
                result = ListEmpty(L);
                if(result == INFEASIBLE) printf("      链表不存在！\n");
                else if(result == TRUE) printf("      链表为空！\n");
                else printf("      链表不为空！\n");
                getchar(); 
                printf("      按任意键继续...\n");
                getchar();
                break;
            case 5:
                result = ListLength(L);
                if(result == INFEASIBLE) printf("      链表不存在！\n");
                else printf("      链表长度为%d\n", result);
                getchar(); 
                printf("      按任意键继续...\n");
                getchar();
                break;
            case 6:
                printf("      请输入要获取的元素位置：");
                scanf("%d", &pos);
                result = GetElem(L, pos, e);
                if(result == INFEASIBLE) printf("      链表不存在！\n");
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
                if(loc == INFEASIBLE) printf("      链表不存在！\n");
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
                if(result == INFEASIBLE) printf("      链表不存在！\n");
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
                if(result == INFEASIBLE) printf("      链表不存在！\n");
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
                if(result == INFEASIBLE) printf("      链表不存在！\n");
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
                if(result == INFEASIBLE) printf("      链表不存在！\n");
                else if(result == ERROR) printf("      位置不合法！\n");
                else printf("      删除的元素为：%d\n", e);
                getchar(); 
                printf("      按任意键继续...\n");
                getchar();
                break;
            case 12:
                if(ListTraverse(L) == OK) printf("      链表遍历成功！\n");
                else printf("      链表遍历失败！\n");
                getchar(); 
                printf("      按任意键继续...\n");
                getchar();
                break;
            case 13:
                if(reverseList(L) == OK) 
                {
                    printf("      链表翻转成功！\n");
                    printf("      翻转后的链表为：\n");
                    ListTraverse(L);
                }
                else printf("      链表翻转失败！\n");
                getchar(); 
                printf("      按任意键继续...\n");
                getchar();
                break;
            case 14:
                printf("      请输入要删除的倒数第n个结点n：");
                scanf("%d", &n);
                if(RemoveNthFromEnd(L, n) == OK) printf("      删除成功！\n");
                else printf("      删除失败！\n");
                getchar(); 
                printf("      按任意键继续...\n");
                getchar();
                break;
            case 15:
                if(sortList(L) == OK) printf("      排序完成！\n");
                else printf("      排序失败！\n");
                getchar(); 
                printf("      按任意键继续...\n");
                getchar();
                break;
            case 16:
                printf("      请输入要保存的文件名：");
                scanf("%s", filename);
                if(SaveList(L, filename) == OK) printf("      保存成功！\n");
                else printf("      保存失败！\n");
                getchar(); 
                printf("      按任意键继续...\n");
                getchar();
                break;
            case 17:
                printf("      请输入要加载的文件名：");
                scanf("%s", filename);
                if(LoadList(L, filename) == OK) printf("      加载成功！\n");
                else printf("      加载失败！\n");
                getchar(); 
                printf("      按任意键继续...\n");
                getchar();
                break;
            
            case 18:// 快速插入:
                printf("      请输入插入元素(非数字结束):");
                while(scanf("%d", &e) == 1)
                {
                    if(ListInsertTail(L, e) == OK){
                        printf("      插入成功！\n");
                        printf("      线性表长度为：%d\n", ListLength(L));
                    }
                    else printf("      插入失败！\n");
                    printf("      请输入插入元素(非数字结束):");
                }
                getchar();
                printf("      按任意键继续...\n");
                getchar();
                break;

            case 0:
                return;
            default:
                printf("      无效的操作编号，请重新输入！\n");
                getchar();
                printf("      按任意键继续...\n"); 
                getchar();
                break;
        }
    }
}

// ========== 多链表主菜单 ==========

void multiListMenu() {
    printf("\n");
    printf("      ========== 多链表管理菜单 ==========\n");
    printf("      1. 新建链表\n");
    printf("      2. 删除链表\n");
    printf("      3. 打印所有链表名\n");
    printf("      4. 进入某个链表操作\n");
    printf("      5. 保存某表到文件\n");
    printf("      6. 从文件加载\n");
    printf("      7. 遍历链表\n");
    printf("      0. 退出系统\n");
    printf("      =====================================\n");
    printf("      请选择你的操作[0~7]:");
}

int main(void) {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    LLISTS Lists = {0};
    int op = 1;
    char name[30];
    while(op) {
        system("cls");
        multiListMenu();
        scanf("%d", &op);
        switch(op) {
            case 1:
                printf("      请输入新链表名(按Q返回)：");
                scanf("%s", name);
                if(strcmp(name, "Q") == 0 || strcmp(name, "q") == 0) break;
                if(AddList(Lists, name) == OK)
                    printf("      新建链表成功！\n");
                else
                    printf("      新建链表失败！\n");
                getchar(); 
                printf("      按任意键继续...\n");
                getchar();
                break;
            case 2:
                printf("      现有链表为:\n");
                printAllListNames(Lists);
                printf("      请输入要删除的链表名(按Q返回)：");
                scanf("%s", name);
                if(strcmp(name, "Q") == 0 || strcmp(name, "q") == 0) break;
                // 如果输入的是编号也可以(未实现):
                if(RemoveList(Lists, name) == OK)
                    printf("      删除链表成功！\n");
                else
                    printf("      删除链表失败（不存在）！\n");
                getchar(); 
                printf("      按任意键继续...\n");
                getchar();
                break;
            case 3:
                printAllListNames(Lists);
                getchar(); 
                printf("      按任意键继续...\n");
                getchar();
                break;
            case 4: {
                printf("      现有链表为:\n");
                printAllListNames(Lists);
                printf("      请输入要进入的链表名(按Q返回)：");
                scanf("%s", name);
                if(strcmp(name, "Q") == 0 || strcmp(name, "q") == 0) break;
                int idx = LocateList(Lists, name);
                if(idx > 0)
                    singleListControl(Lists.elem[idx-1].L);
                else {
                    printf("      未找到该链表！\n");
                    getchar(); 
                    printf("      按任意键继续...\n");
                    getchar();
                }
                break;
            }

            case 5:
            {
                printf("      现有链表为:\n");
                printAllListNames(Lists);
                printf("      请输入要保存的链表名(按Q返回)：");
                scanf("%s", name);
                if(strcmp(name, "Q") == 0 || strcmp(name, "q") == 0) break;
                int idx = LocateList(Lists, name);
                if(idx > 0) {
                    printf("      请输入文件名：");
                    scanf("%s", name);
                    SaveList(Lists.elem[idx-1].L, name);
                } else {
                    printf("      未找到该链表！\n");
                }
                getchar();
                printf("      按任意键继续...\n");
                getchar();
                break;
            }

            case 6:
            {
                printf("      现有链表为:\n");
                printAllListNames(Lists);
                printf("      请输入要加载到的链表名(按Q返回)：");
                scanf("%s", name);
                if(strcmp(name, "Q") == 0 || strcmp(name, "q") == 0) break;
                int idx = LocateList(Lists, name);
                if(idx > 0) {
                    printf("      请输入文件名：");
                    scanf("%s", name);
                    LoadList(Lists.elem[idx-1].L, name);
                } else {
                    printf("      未找到该链表！\n");
                }
                getchar();
                printf("      按任意键继续...\n");
                getchar();
                break;
            }

            case 7:
            {
                printf("      现有链表为:\n");
                printAllListNames(Lists);
                printf("      遍历方式(1:所有遍历, 2:单个遍历, 0: 返回): ");
                int showIndex;
                scanf("%d", &showIndex);
                if(showIndex == 1) {
                    for(int i = 0; i < Lists.length; i++) {
                        printf("      表名：%s\n", Lists.elem[i].name);
                        ListTraverse(Lists.elem[i].L);
                    }
                }
                else if(showIndex == 2) {
                    printf("      请输入要打印的表名：");
                    scanf("%s", name);
                    int idx = LocateList(Lists, name);
                    if(idx > 0) {
                        ListTraverse(Lists.elem[idx-1].L);
                    } else {
                        printf("      未找到该线性表！\n");
                    }
                }
                else{
                    break;
                }
                getchar();
                printf("      按任意键继续...\n");
                getchar();
                break;
            }
            case 0:
            {
                printf("      再见！\n");
                return 0;
            }
            
            default:
                printf("      无效的操作编号，请重新输入！\n");
                getchar(); 
                printf("      按任意键继续...\n");
                getchar();
                break;
        }
    }
    return 0;
}

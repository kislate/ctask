### 任务要求:
```txt
2基于链式存储结构的线性表实现
2.1 实验目的
通过实验达到：（1）加深对线性表的概念、基本运算的理解；（2）熟练掌握线性表的逻辑结构与物理结构的关系；（3）物理结构采用单链表,熟练掌握线性表的基本运算的实现。
2.2 线性表运算定义
依据最小完备性和常用性相结合的原则，以函数形式定义了线性表的初始化表、销毁表、清空表、判定空表、求表长和获得元素等12种基本运算，具体运算功能定义如下：
（1）初始化表：函数名称是InitList(L)；初始条件是线性表L不存在；操作结果是构造一个空的线性表；
（2）销毁表：函数名称是DestroyList(L)；初始条件是线性表L已存在；操作结果是销毁线性表L；
（3）清空表：函数名称是ClearList(L)；初始条件是线性表L已存在；操作结果是将L重置为空表；
（4）判定空表：函数名称是ListEmpty(L)；初始条件是线性表L已存在；操作结果是若L为空表则返回TRUE,否则返回FALSE；
（5）求表长：函数名称是ListLength(L)；初始条件是线性表已存在；操作结果是返回L中数据元素的个数；
（6）获得元素：函数名称是GetElem(L,i,e)；初始条件是线性表已存在，1≤i≤ListLength(L)；操作结果是用e返回L中第i个数据元素的值；
（7）查找元素：函数名称是LocateElem(L,e,compare())；初始条件是线性表已存在；操作结果是返回L中第1个与e满足关系compare（）关系的数据元素的位序，若这样的数据元素不存在，则返回值为0；
（8）获得前驱：函数名称是PriorElem(L,cur_e,pre_e)；初始条件是线性表L已存在；操作结果是若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱，否则操作失败，pre_e无定义；
（9）获得后继：函数名称是NextElem(L,cur_e,next_e)；初始条件是线性表L已存在；操作结果是若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继，否则操作失败，next_e无定义；
（10）插入元素：函数名称是ListInsert(L,i,e)；初始条件是线性表L已存在，1≤i≤ListLength(L)+1；操作结果是在L的第i个位置之前插入新的数据元素e；
（11）删除元素：函数名称是ListDelete(L,i,e)；初始条件是线性表L已存在且非空，1≤i≤ListLength(L)；操作结果：删除L的第i个数据元素，用e返回其值；
（12）遍历表：函数名称是ListTraverse(L,visit())，初始条件是线性表L已存在；操作结果是依次对L的每个数据元素调用函数visit( )。
附加功能：
（1）链表翻转：函数名称是reverseList(L)，初始条件是线性表L已存在；操作结果是将L翻转；
（2）删除链表的倒数第n个结点：函数名称是RemoveNthFromEnd(L,n); 初始条件是线性表L已存在且非空, 操作结果是该链表中倒数第n个节点；
（3）链表排序：函数名称是sortList(L)，初始条件是线性表L已存在；操作结果是将L由小到大排序；
（4）实现线性表的文件形式保存：其中，①需要设计文件数据记录格式，以高效保存线性表数据逻辑结构(D,{R})的完整信息；②需要设计线性表文件保存和加载操作合理模式。附录B提供了文件存取的参考方法；
注：①保存到文件后，可以由一个空表加载文件生成单链表。
（5）实现多个线性表管理：设计相应的数据结构管理多个线性表的查找、添加、移除等功能。
注：附加功能（5）实现多个线性表管理应能创建、添加、移除多个线性表，单线性表和多线性表的区别仅仅在于线性表管理的个数不同，多线性表管理应可自由切换到管理的每个表，并可单独对某线性表进行单线性表的所有操作。
2.3 实验任务
采用单链表作为线性表的物理结构，实现2.2小节的运算。其中ElemType为数据元素的类型名，具体含义可自行定义，其它有关类型和常量的定义和引用详见文献[1]的p10。
构造一个具有菜单的功能演示系统。其中，在主程序中完成函数调用所需实参值的准备和函数执行结果的显示，并给出适当的操作提示显示。附录A提供了简易菜单的框架（供参考）。


```

- 代码1:
```cpp
status InitList(LinkList &L)
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L != NULL) return INFEASIBLE;
    L = (LinkList)malloc(sizeof(LNode));
    if(L == NULL) return OVERFLOW;
    L->next = NULL;
    return OK;
    /********** End **********/
}
```
- 代码2:
```cpp
status DestroyList(LinkList &L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
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
    /********** End **********/
}
```

- 代码3:
```cpp
status ClearList(LinkList &L)
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
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
    /********** End **********/
}
```

- 代码4:
```cpp
status ListEmpty(LinkList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L == NULL) return INFEASIBLE;
    if(L->next == NULL) return TRUE;
    return FALSE;
    /********** End **********/
}
```

- 代码5:
```cpp
int ListLength(LinkList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L == NULL) return INFEASIBLE;
    int length = 0;
    LinkList p = L->next;
    while(p != NULL){
        length++;
        p = p->next;
    }
    return length;
    /********** End **********/
}
```

- 代码6:
```cpp
status GetElem(LinkList L,int i,ElemType &e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
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
    /********** End **********/
}
```

- 代码7:
```cpp
status LocateElem(LinkList L,ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L == NULL) return INFEASIBLE;
    LinkList p = L->next;
    int cnt = 1;
    while(p != NULL){
        if(p->data == e) return cnt;
        p = p->next;
        cnt++;
    }
    return ERROR;
    /********** End **********/
}
```
- 代码8:
```cpp
status PriorElem(LinkList L,ElemType e,ElemType &pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
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
    /********** End **********/
}
```

- 代码9:
```cpp
status NextElem(LinkList L,ElemType e,ElemType &next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
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
    /********** End **********/
}
```

- 代码10:
```cpp
status ListInsert(LinkList &L,int i,ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
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
    /********** End **********/
}
```

- 代码11:
```cpp
status ListDelete(LinkList &L,int i,ElemType &e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
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
    /********** End **********/
}
```

- 代码12:
```cpp
status ListTraverse(LinkList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L == NULL) return INFEASIBLE;
    LinkList p = L->next;
    while(p != NULL)
    {
        printf("%d", p->data);
        if(p->next != NULL) printf(" ");
        p = p->next;
    }
    printf("\n");
    return OK;
    /********** End **********/
}
```

- 代码13:
```cpp
status SaveList(LinkList L,char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 1 *********/
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
    /********** End 1 **********/
}

status LoadList(LinkList &L,char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 2 *********/
    if(L != NULL) return INFEASIBLE;
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
    return OK;
    /********** End 2 **********/
}


```

- 下面是一个基于顺序表的已经实现菜单系统, 可以完全依照其实现(但是具体(包括附加功能)功能和函数改为实验要求):
```cpp
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

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10

typedef struct{
    ElemType *elem = NULL;// 初始化为NULL
    int length;
    int listsize;
}SqList;

typedef struct{
    struct { 
        char name[30]; 
        SqList L;
    } elem[10];
    int length;
    int listsize;
}LISTS;


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
status ListTrabverseDetail(SqList L);

status AddList(LISTS &Lists, char ListName[]) {
    // 查重:
    for(int i = 0; i < Lists.length; i++) {
        if(strcmp(Lists.elem[i].name, ListName) == 0) 
        {
            printf("      线性表名重复！\n");
            return ERROR;
        }
    }
    if(Lists.length >= 10)
    {
        printf("      线性表数量已达上限！\n");
        return ERROR;
    }
    strcpy(Lists.elem[Lists.length].name, ListName);
    InitList(Lists.elem[Lists.length].L);
    Lists.length++;
    return OK;
}
status RemoveList(LISTS &Lists, char ListName[]) {
    if(Lists.length == 0) return ERROR;
    int i = 0;
    for(i = 0; i < Lists.length; i++) {
        if(strcmp(Lists.elem[i].name, ListName) == 0) break;
    }
    if(i == Lists.length) return ERROR;
    free(Lists.elem[i].L.elem);
    for(int j = i; j < Lists.length - 1; j++) {
        Lists.elem[j] = Lists.elem[j + 1];
    }
    Lists.length--;
    return OK;
}
int LocateList(LISTS Lists, char ListName[]) {
    if(Lists.length == 0 ) return 0;
    for(int i = 0; i < Lists.length; i++) {
        if(strcmp(Lists.elem[i].name, ListName) == 0) return i + 1;
    }
    return ERROR;
}

// 附加功能1：最大连续子数组和
int MaxSubArray(SqList L) {
    // 采用线性dp, 时间复杂度为O(n), 空间复杂度为O(1)
    if(L.length == 0) return 0;
    int maxSum = L.elem[0], currSum = L.elem[0] > 0 ? L.elem[0] : 0;
    for(int i = 1; i < L.length; i++){
        currSum += L.elem[i];
        if(currSum > maxSum) maxSum = currSum;
        if(currSum < 0) currSum = 0; // 如果当前和小于0，则重置为0
    }
    return maxSum;
}
// 附加功能2：和为K的子数组个数
int SubArrayNum(SqList L, int k) {
    int count = 0;
    // O(n^2)的暴力解法
    for(int i = 0; i < L.length; i++) {
        int sum = 0;
        for(int j = i; j < L.length; j++) {
            sum += L.elem[j];
            if(sum == k) count++;
        }
    }
    return count;
}
// 附加功能3：顺序表排序
void sortList(SqList &L) {
    if(L.elem == NULL) return; // 线性表不存在
    if(L.length == 0) return; // 线性表为空
    // 冒泡排序
    for(int i = 0; i < L.length - 1; i++)
        for(int j = 0; j < L.length - 1 - i; j++)
            if(L.elem[j] > L.elem[j+1]) {
                int t = L.elem[j]; L.elem[j] = L.elem[j+1]; L.elem[j+1] = t;
            }
}

// 文件保存：将某个线性表写入文件
status SaveListToFile(SqList L, const char* filename) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        printf("      文件打开失败！\n");
        return ERROR;
    }
    // 先写入表长
    fwrite(&L.length, sizeof(int), 1, fp);
    // 再写入所有元素
    fwrite(L.elem, sizeof(ElemType), L.length, fp);
    fclose(fp);
    printf("      已保存到文件：%s\n", filename);
    return OK;
}

// 文件读取：从文件生成线性表
status LoadListFromFile(SqList &L, const char* filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        printf("      文件打开失败！\n");
        return ERROR;
    }
    int len = 0;
    fread(&len, sizeof(int), 1, fp);
    if (len <= 0) {
        fclose(fp);
        printf("      文件内容无效！\n");
        return ERROR;
    }
    if (L.elem) free(L.elem);
    L.elem = (ElemType*)malloc(sizeof(ElemType) * (len + LISTINCREMENT));
    if (!L.elem) {
        fclose(fp);
        printf("      内存分配失败！\n");
        return OVERFLOW;
    }
    fread(L.elem, sizeof(ElemType), len, fp);
    L.length = len;
    L.listsize = len + LISTINCREMENT;
    fclose(fp);
    printf("      已从文件加载线性表：%s\n", filename);
    return OK;
}

// 多表主菜单
void multiListMenu() {
    printf("\n");
    printf("      ========== 多线性表管理菜单 ==========\n");
    printf("      1. 新建线性表\n");
    printf("      2. 删除线性表\n");
    printf("      3. 打印所有线性表名\n");
    printf("      4. 进入某个线性表操作\n");
    printf("      5. 保存某表到文件\n");
    printf("      6. 从文件加载到某表\n");
    printf("      7. 打印线性表\n");
    printf("      0. 退出系统\n");
    printf("      =====================================\n");
    printf("      请选择你的操作[0~7]:");
}

void singleListMenu() {
    printf("\n");
    printf("      ========== 单线性表操作菜单 ==========\n");
    printf("      1. InitList          7. LocateElem\n");
    printf("      2. DestroyList       8. PriorElem\n");
    printf("      3. ClearList         9. NextElem \n");
    printf("      4. ListEmpty        10. ListInsert\n");
    printf("      5. ListLength       11. ListDelete\n");
    printf("      6. GetElem          12. ListTrabverse\n");
    printf("      13. ListInsertFast  14. 最大连续子数组和\n");
    printf("      15. 和为K的子数组   16. 顺序表排序\n");
    printf("      0. 返回多表菜单\n");
    printf("      =====================================\n");
    printf("      请选择你的操作[0~16]:");
}

// 单表操作主控
void singleListControl(SqList &L) {
    int op = 1;
    ElemType e, pre, next;
    int pos, loc, k;
    status result;
    while(op) {
        system("cls"); // 清屏
        singleListMenu();
        scanf("%d", &op);
        switch(op) {
            case 1:
                if(InitList(L)==OK) printf("      线性表创建成功！\n");
                else printf("      线性表创建失败！\n");
                getchar();
                printf("      按任意键继续...\n");
                getchar();
                break;
            case 2:
                if(DestroyList(L)==OK) printf("      线性表销毁成功！\n");
                else printf("      线性表销毁失败！\n");
                getchar();
                printf("      按任意键继续...\n");
                getchar();
                break;
            case 3:
                if(ClearList(L)==OK) printf("      线性表清空成功！\n");
                else printf("      线性表清空失败！\n");
                getchar();
                printf("      按任意键继续...\n");
                getchar();
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
                printf("      请输入要获取的元素位置(按Q返回)：");
                if(scanf("%d", &pos) != 1) break;
                result = GetElem(L, pos, e);
                if(result == INFEASIBLE) printf("      线性表不存在！\n");
                else if(result == ERROR) printf("      位置不合法！\n");
                else printf("      第%d个元素为：%d\n", pos, e);
                getchar();
                printf("      按任意键继续...\n");
                getchar();
                break;
            case 7:
                printf("      请输入要查找的元素值(按Q返回)：");
                if(scanf("%d", &e) != 1) break;
                loc = LocateElem(L, e);
                if(loc == INFEASIBLE) printf("      线性表不存在！\n");
                else if(loc == 0) printf("      未找到该元素！\n");
                else printf("      元素%d的位置为：%d\n", e, loc);
                getchar();
                printf("      按任意键继续...\n");
                getchar();
                break;
            case 8:
                printf("      请输入要查找前驱的元素值(按Q返回)：");
                if(scanf("%d", &e) != 1) break;
                result = PriorElem(L, e, pre);
                if(result == INFEASIBLE) printf("      线性表不存在！\n");
                else if(result == ERROR) printf("      元素不存在或无前驱！\n");
                else printf("      元素%d的前驱为：%d\n", e, pre);
                getchar();
                printf("      按任意键继续...\n");
                getchar();
                break;
            case 9:
                printf("      请输入要查找后继的元素值(按Q返回)：");
                if(scanf("%d", &e) != 1) break;
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
                printf("      请输入删除位置(按Q返回)：");
                if(scanf("%d", &pos) != 1) break;
                result = ListDelete(L, pos, e);
                if(result == INFEASIBLE) printf("      线性表不存在！\n");
                else if(result == ERROR) printf("      位置不合法！\n");
                else printf("      删除的元素为：%d\n", e);
                getchar();
                printf("      按任意键继续...\n");
                getchar();
                break;
            case 12:
                printf("      是否详细显示？(1:是 0:否):");
                int showIndex;
                scanf("%d", &showIndex);
                if(showIndex){
                    // 12.5
                    if(ListTrabverseDetail(L) == OK) printf("      线性表遍历成功！\n");
                    else printf("      线性表遍历失败！\n");
                }
                else if(showIndex == 0)
                {
                    if(ListTrabverse(L) == OK) printf("      线性表遍历成功！\n");
                    else printf("      线性表遍历失败！\n");
                }
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
            case 14:
                printf("      最大连续子数组和为：%d\n", MaxSubArray(L));
                getchar();
                printf("      按任意键继续...\n");
                getchar();
                break;
            case 15:
                printf("      请输入目标和k：");
                scanf("%d", &k);
                printf("      和为%d的连续子数组个数为：%d\n", k, SubArrayNum(L, k));
                getchar();
                printf("      按任意键继续...\n");
                getchar();
                break;
            case 16:
                sortList(L);
                printf("      排序完成！\n");
                getchar();
                printf("      按任意键继续...\n");
                getchar();
                break;
            case 0:
                return; // 返回多表菜单
            default:
                printf("      无效的操作编号，请重新输入！\n");
                getchar();
                printf("      按任意键继续...\n");
                getchar();
                break;
        }
    }
}

// 打印所有线性表名
void printAllListNames(LISTS &Lists) {
    printf("      当前已有线性表数量：%d\n", Lists.length);
    for(int i = 0; i < Lists.length; i++) {
        printf("      %d. %s\n", i+1, Lists.elem[i].name);
    }
}

// 多表主控
int main(void) {
    // 防止输出乱码
    SetConsoleOutputCP(65001); // 设置输出为UTF-8
    SetConsoleCP(65001);       // 设置输入为UTF-8
    LISTS Lists = {0};
    int op = 1;
    char name[30], filename[100];
    while(op) {
        system("cls"); // 清屏
        multiListMenu();
        scanf("%d", &op);
        switch(op) {
        case 1: // 新建线性表
            printf("      请输入新表名(按Q返回)：");
            scanf("%s", name);
            if(strcmp(name, "Q") == 0 || strcmp(name, "q") == 0)
            {
                printf("      取消新建线性表！\n");
                break;
            }
            if(AddList(Lists, name) == OK)
                printf("      新建线性表成功！\n");
            else
                printf("      新建线性表失败！\n");
            getchar();
            printf("      按任意键继续...\n");
            getchar();
            break;
        case 2: // 删除线性表
            printf("      现有线性表为:\n");
            printAllListNames(Lists);
            printf("      请输入要删除的表名(返回请按'Q')：");
            scanf("%s", name);
            if(!strcmp(name, "Q") || !strcmp(name, "q")) break;
            // 如果输入的是编号也可以(未实现):
            if(RemoveList(Lists, name) == OK)
                printf("      删除线性表成功！\n");
            else
                printf("      删除线性表失败（不存在）！\n");
            getchar();
            printf("      按任意键继续...\n");
            getchar();
            break;
        case 3: // 打印所有表名
            printAllListNames(Lists);
            getchar();
            printf("      按任意键继续...\n");
            getchar();
            break;
        case 4: // 进入某个线性表
        {
            printf("      现有线性表为:\n");
            printAllListNames(Lists);
            printf("      请输入要进入的表名(返回请按Q)：");
            scanf("%s", name);
            if(!strcmp(name, "Q") || !strcmp(name, "q")) break;
            int idx = LocateList(Lists, name);
            if(idx > 0)
                singleListControl(Lists.elem[idx-1].L);
            else {
                printf("      未找到该线性表！\n");
                getchar();
                printf("      按任意键继续...\n");
                getchar();
            }
            break;
        }
        case 5: // 保存某表到文件
        {
            printf("      现有线性表为:\n");
            printAllListNames(Lists);
            printf("      请输入要保存的表名(按Q返回)：");
            scanf("%s", name);
            if(!strcmp(name, "Q") || !strcmp(name, "q")) break;
            int idx = LocateList(Lists, name);
            if(idx > 0) {
                printf("      请输入文件名：");
                scanf("%s", filename);
                SaveListToFile(Lists.elem[idx-1].L, filename);
            } else {
                printf("      未找到该线性表！\n");
            }
            getchar();
            printf("      按任意键继续...\n");
            getchar();
            break;
        }
        case 6: // 从文件加载到某表
        {
            printf("      现有线性表为:\n");
            printAllListNames(Lists);
            printf("      请输入要加载到的表名(按Q返回)：");
            scanf("%s", name);
            if(!strcmp(name, "Q") || !strcmp(name, "q")) break;
            int idx = LocateList(Lists, name);
            if(idx > 0) {
                printf("      请输入文件名：");
                scanf("%s", filename);
                LoadListFromFile(Lists.elem[idx-1].L, filename);
            } else {
                printf("      未找到该线性表！\n");
            }
            getchar();
            printf("      按任意键继续...\n");
            getchar();
            break;
        }
        case 7: // 打印表
        {
            printf("      选择全部打印还是单表打印？(1:全部 2:单表): ");
            int choice;
            scanf("%d", &choice);
            if(choice == 1) {
                for(int i = 0; i < Lists.length; i++) {
                    printf("      表名：%s\n", Lists.elem[i].name);
                    ListTrabverse(Lists.elem[i].L);
                }
            } else if(choice == 2) {
                printf("      请输入要打印的表名：");
                scanf("%s", name);
                int idx = LocateList(Lists, name);
                if(idx > 0) {
                    ListTrabverse(Lists.elem[idx-1].L);
                } else {
                    printf("      未找到该线性表！\n");
                }
            } else {
                printf("      无效选择！\n");
            }
            getchar();
            printf("      按任意键继续...\n");
            getchar();
            break;
        }
        case 0:
            printf("      再见！\n");
            return 0;
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
    printf("      线性表元素为：\n");
    printf("      ");
    for(int i = 0; i < L.length; i++)
    {
        printf("%d ", L.elem[i]);
    }
    printf("\n");
    return OK;
}

// 12.5:遍历线性表并输出（详细显示）
status ListTrabverseDetail(SqList L)
{
    if(L.elem == NULL)
    {
        printf("      线性表不存在！\n");
        return 0; // 线性表不存在
    }
    printf("      线性表的长度为%d：\n" , L.length);
    printf("      线性表元素为：\n");
    printf("      ");
    for(int i = 0; i < L.length; i++)
    {
        printf("%d:%d ", i+1, L.elem[i]);
    }
    printf("\n");
    return OK;
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
```
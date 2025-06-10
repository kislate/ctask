#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <bits/stdc++.h>
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
    int count = 0, sum = 0;
    std::unordered_map<int, int> mp;
    mp[0] = 1;
    for(int i = 0; i < L.length; i++) {
        sum += L.elem[i];
        if(mp.count(sum - k)) count += mp[sum - k];
        mp[sum]++;
    }
    return count;
}

// 无stl版本的和为K的子数组个数
// // 附加功能2：和为K的子数组个数（C语言实现，前缀和+数组哈希，适合小范围）
// int SubArrayNum(SqList L, int k) {
//     int count = 0, sum = 0;
//     // 假设前缀和范围在 [-100000, 100000]
//     // 需要开 200001 大小的数组，偏移量为 100000
//     static int mp[200001] = {0};
//     int offset = 100000;
//     for(int i = 0; i < 200001; i++) mp[i] = 0;
//     mp[offset] = 1; // sum=0 出现1次
//     for(int i = 0; i < L.length; i++) {
//         sum += L.elem[i];
//         int idx = sum - k + offset;
//         if(idx >= 0 && idx < 200001) count += mp[idx];
//         mp[sum + offset]++;
//     }
//     return count;
// }

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
                printf("      排序后的线性表为：\n");
                ListTrabverse(L);
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
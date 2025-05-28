#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType; // 数据元素类型定义

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

typedef struct LNode { // 单链表（链式结构）结点的定义
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;
typedef struct{  //线性表的管理表定义
    struct { char name[30];
                LinkList L;	
        } elem[10];
    int length;
    int listsize;
}LISTS;

FILE *fp;

status InitList(LinkList &L);
status DestroyList(LinkList &L);
status ClearList(LinkList &L);
status ListEmpty(LinkList L);
status ListLength(LinkList L);
status GetElem(LinkList L, int i, ElemType &e);
status LocateElem(LinkList L, ElemType e);
status PriorElem(LinkList L, ElemType e, ElemType &pre);
status NextElem(LinkList L, ElemType e, ElemType &next);
status ListInsert(LinkList &L, int i, ElemType e);
status ListDelete(LinkList &L, int i, ElemType &e);
status ListTraverse(LinkList L);
status SaveList(LinkList L, char FileName[]);
status LoadList(LinkList &L, char FileName[]);
status reverseList(LinkList &L);
status RemoveNthFromEnd(LinkList &L,int n,ElemType &e);
status sortList(LinkList &L);
status ListsManage(LISTS &Lists);
status AddList(LISTS &Lists, char ListName[]);
status RemoveList(LISTS &Lists, char ListName[]);
status LocateList(LISTS Lists, char ListName[]);

LinkList L = NULL;
char Lname[30];//匹配多线性表的名称
int mood=0; //mood=0表示单线性表操作，mood=1表示多线性表操作

int main() {
    int op = 1;
  
    LISTS Lists;
    Lists.length = 0;
    char FileName[30];

    while (op) {
        system("cls");
        printf("\n\n");
        printf("      Menu for Linear Table On Linked List Structure \n");
        printf("-----------------------------------------------------\n");
        printf("    	  1. InitList/Putdata       11. ListDelete \n");
        printf("    	  2. DestroyList            12. ListTraverse\n");
        printf("    	  3. ClearList              13. SaveList\n");
        printf("    	  4. ListEmpty              14. LoadList\n");
        printf("    	  5. ListLength             15. reverseList\n");
        printf("    	  6. GetElem                16. RemoveNthFromEnd\n");
        printf("    	  7. LocateElem             17. sortList\n");
if(!mood)    printf("    	  8. PriorElem              18. ListsManage\n");
else         printf("    	  8. PriorElem              \n");
        printf("    	  9. NextElem               0. Exit\n");
        printf("    	  10. ListInsert                \n");
        printf("-----------------------------------------------------\n");
        printf("    请选择你的操作[0~18]:");
        scanf("%d", &op);
        switch (op) {
            case 1:
                if (InitList(L) == OK)
                    printf("线性表创建成功！\n");
                else
                    printf("线性表已存在，无法再次创建！\n");
                printf("输入线性表的元素？（1/0）\n");
                int choice;
                scanf("%d", &choice);
                if (choice == 1) {
                    printf("请输入线性表的元素（以0结束）：\n");
                    ElemType data;
                    scanf("%d", &data);
                    while (data) {
                        ListInsert(L, ListLength(L) + 1, data);
                        scanf("%d", &data);
                    }
                }
                getchar();
                getchar();
                break;
            case 2:
                if (DestroyList(L) == OK)
                    printf("线性表销毁成功！\n");
                else
                    printf("线性表不存在，无法销毁！\n");
                getchar();
                getchar();
                break;
            case 3:
                if (ClearList(L) == OK)
                    printf("线性表已清空！\n");
                else
                    printf("线性表不存在，无法清空！\n");
                getchar();
                getchar();
                break;
            case 4:
                if (ListEmpty(L) == INFEASIBLE)
                    printf("线性表不存在！\n");
                else if (ListEmpty(L) == OK)
                    printf("线性表为空！\n");
                else
                    printf("线性表非空！\n");
                getchar();
                getchar();
                break;
            case 5:
                if (ListLength(L) == INFEASIBLE)
                    printf("线性表不存在！\n");
                else
                    printf("该线性表长度为%d\n", ListLength(L));
                getchar();
                getchar();
                break;
            case 6:
                printf("请输入要获取的元素位置：\n");
                int i;
                ElemType e;
                scanf("%d", &i);
                if (GetElem(L, i, e) == OK)
                    printf("获取元素成功，该元素为%d！\n", e);
                else if (GetElem(L, i, e) == ERROR)
                    printf("获取元素不在该线性表范围之内！\n");
                else
                    printf("线性表不存在，无法获取元素！\n");
                getchar();
                getchar();
                break;
            case 7:
                printf("请输入要查找的元素：\n");
                ElemType a;
                scanf("%d", &a);
                if (LocateElem(L, a) == INFEASIBLE)
                    printf("线性表不存在！\n");
                else if (LocateElem(L, a) == ERROR)
                    printf("没找到元素%d！\n", a);
                else
                    printf("元素%d在第%d个位置！\n", a, LocateElem(L, a));
                getchar();
                getchar();
                break;
            case 8:
                printf("请输入要查找前驱的元素：\n");
                ElemType b, pre;
                scanf("%d", &b);
                if (PriorElem(L, b, pre) == INFEASIBLE)
                    printf("线性表不存在！\n");
                else if (PriorElem(L, b, pre) == ERROR)
                    printf("前驱不存在！\n");
                else
                    printf("元素%d的前驱为%d！\n", b, pre);
                getchar();
                getchar();
                break;
            case 9:
                printf("请输入要查找后继的元素：\n");
                ElemType c, next;
                scanf("%d", &c);
                if (NextElem(L, c, next) == INFEASIBLE)
                    printf("线性表不存在！\n");
                else if (NextElem(L, c, next) == ERROR)
                    printf("后继不存在！\n");
                else
                    printf("元素%d的后继为%d！\n", c, next);
                getchar();
                getchar();
                break;
            case 10:
                printf("在何处插入何元素: ");
                int j;
                ElemType d;
                scanf("%d %d", &j, &d);
                if (ListInsert(L, j, d) == OK)
                    printf("插入成功！\n");
                else if (ListInsert(L, j, d) == INFEASIBLE)
                    printf("线性表不存在！\n");
                else
                    printf("插入位置选取有误！\n");
                getchar();
                getchar();
                break;
            case 11:
                printf("在何处删除元素: ");
                int k;
                ElemType f;
                scanf("%d", &k);
                if (ListDelete(L, k, f) == OK)
                    printf("删除成功，删除的元素为%d！\n", f);
                else if (ListDelete(L, k, f) == INFEASIBLE)
                    printf("线性表不存在！\n");
                else
                    printf("删除位置选取有误！\n");
                getchar();
                getchar();
                break;
            case 12:
                if (ListTraverse(L) == INFEASIBLE)
                    printf("线性表不存在！\n");
                getchar();
                getchar();
                break;
            case 13:
                printf("请输入文件名：\n");
                scanf("%s", FileName);
                if (SaveList(L, FileName) == OK)
                    printf("保存成功！\n");
                else
                    printf("线性表不存在，无法保存！\n");
                getchar();
                getchar();
                break;
            case 14:
                printf("请输入文件名：\n");
                scanf("%s", FileName);
                if (LoadList(L, FileName) == OK)
                    printf("读取成功！\n");
                else
                    printf("线性表已存在，无法读取！\n");
                getchar();
                getchar();
                break;
            case 15:
                if (reverseList(L) == OK)
                    printf("线性表反转成功！\n");
                else
                    printf("线性表不存在，无法反转！\n");
                getchar();
                getchar();
                break;
            case 16:
                printf("请输入要删除的元素的倒数序号n：\n");
                int n;
                ElemType o;
                scanf("%d", &n);
                if (RemoveNthFromEnd(L, n, o) == OK)
                    printf("删除成功，删除的元素为%d！\n", o);
                else
                    printf("线性表不存在或位置不合法，无法删除！\n");
                getchar();
                getchar();
                break;
            case 17:
                if (sortList(L) == OK)
                    printf("线性表排序成功！\n");
                else
                    printf("线性表不存在，无法排序！\n");
                getchar();
                getchar();
                break;
            case 18:
                mood=1;
                ListsManage(Lists);
                break;
            case 0:
                break;
        }
    }
    printf("欢迎下次再使用本系统！\n");
}



//多链表管理函数



status ListsManage(LISTS &Lists) {
    int op = 1;
    char ListName[30];
    while (op) {
        system("cls");
        printf("\n\n");
        printf("      Menu for Linear Table Management \n");
        printf("-------------------------------------------------\n");
        printf("    	  1. AddList        4. More\n");
        printf("    	  2. RemoveList     5. ListsTraverse\n");
        printf("    	  3. LocateList     0. Exit \n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~5]:");
        scanf("%d", &op);
        switch (op) {
            case 1:
                printf("请输入线性表名称：\n");
                scanf("%s", ListName);
                if (AddList(Lists, ListName) == OK) {
                    printf("线性表创建成功！\n");
                    printf("请输入线性表的元素（以0结束）：\n");
                    ElemType data;
                    while (scanf("%d", &data) && data != 0) {
                        ListInsert(Lists.elem[Lists.length - 1].L, ListLength(Lists.elem[Lists.length - 1].L) + 1, data);
                    }
                } else {
                    printf("空间已满，无法再创建线性表！\n");
                }
                getchar();
                getchar();
                break;
            case 2:
                printf("请输入要删除的线性表名称：\n");
                scanf("%s", ListName);
                if (RemoveList(Lists, ListName) == OK)
                    printf("该线性表删除成功！\n");
                else
                    printf("未找到该线性表，无法删除！\n");
                getchar();
                getchar();
                break;
            case 3:
                printf("请输入要查找的线性表名称：\n");
                scanf("%s", ListName);
                int x = LocateList(Lists, ListName);
                if (x > 0)
                    printf("线性表 %s 的逻辑序号为：%d\n", ListName, x);
                else
                    printf("未找到该线性表！\n");
                getchar();
                getchar();
                break;
            case 4:
                printf("对哪一个表展开更多单一操作（输入逻辑编号即可）？\n");
                int index2;
                scanf("%d", &index2);
                if (index2 < 1 || index2 > Lists.length) {
                    printf("输入的逻辑编号不合法！\n");
                    getchar();
                    getchar();
                    break;
                }
                printf("对线性表 %s 进行操作：\n", Lists.elem[index2 - 1].name);
                L = Lists.elem[index2 - 1].L;
                main(); // 调用主函数以对单线性表进行操作
                Lists.elem[index2 - 1].L = L;
                break;
            case 5:
                for (int i = 0; i < Lists.length; i++) {
                    printf("%s: ", Lists.elem[i].name);
                    ListTraverse(Lists.elem[i].L);
                    printf("\n");
                }
                getchar();
                getchar();
                break;
            case 0:
                mood = 0; // 返回主菜单
                break;
        }
    }
    return OK;
}
status AddList(LISTS &Lists, char ListName[]) {
    if (Lists.length >= 10) // 判断是否超过最大线性表数量
        return ERROR;
    strcpy(Lists.elem[Lists.length].name, ListName);
    Lists.elem[Lists.length].L = NULL; // 初始化链表
    if (InitList(Lists.elem[Lists.length].L) == OK) {
        Lists.length++;
        return OK;
    }
    return ERROR;
}

status RemoveList(LISTS &Lists, char ListName[]) {
    for (int i = 0; i < Lists.length; i++) {
        if (strcmp(Lists.elem[i].name, ListName) == 0) {
            DestroyList(Lists.elem[i].L); // 销毁链表
            for (int j = i; j < Lists.length - 1; j++) {
                Lists.elem[j] = Lists.elem[j + 1]; // 移动后续元素
            }
            Lists.length--;
            return OK;
        }
    }
    return ERROR; // 未找到指定线性表
}

status LocateList(LISTS Lists, char ListName[]) {
    for (int i = 0; i < Lists.length; i++) {
        if (strcmp(Lists.elem[i].name, ListName) == 0)
            return i + 1; // 返回逻辑序号
    }
    return 0; // 未找到指定线性表
}




//单链表操作函数



status InitList(LinkList &L)
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
    if(L != NULL) //线性表已经存在
        return INFEASIBLE;
    L = (LinkList)malloc(sizeof(LNode)); 
    L->next = NULL; 
    if(L != NULL)
        return OK; 
}

status DestroyList(LinkList &L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
    if(L == NULL) 
        return INFEASIBLE;
    LinkList p,q;
    p = L->next; //p指向第一个结点
    while(p != NULL) {
        q = p; //q指向当前结点
        p = p->next; 
        free(q); 
    }
    free(L); 
    L = NULL; //L置空
    return OK;
}

status ClearList(LinkList &L)
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
    if(L == NULL) 
        return INFEASIBLE;
    LinkList p,q;
    p = L->next; //p指向第一个结点
    while(p != NULL) {
        q = p; //q指向当前结点
        p = p->next; 
        free(q); 
    }
    L->next = NULL; //清空线性表
    return OK;
}

status ListEmpty(LinkList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
    if (L == NULL) 
        return INFEASIBLE;
    if (L->next == NULL)
        return TRUE; //线性表为空
    else
        return FALSE; //线性表不为空
}

status ListLength(LinkList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
    if (L == NULL) 
        return INFEASIBLE;
    int length = 0; 
    LinkList p = L->next; 
    while(p!=NULL){
        length++; 
        p = p->next;
    }
    return length;
}

status GetElem(LinkList L,int i,ElemType &e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L == NULL)
        return INFEASIBLE;
    else if(i < 1 || i > ListLength(L)) 
        return ERROR; 
    else {
        LinkList p=L->next;
        while(--i) p=p->next; 
        e = p->data; 
        return OK;  
    }
}

status LocateElem(LinkList L,ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
{
    if(L == NULL)
        return INFEASIBLE;
    LinkList p = L->next;
    int i = 1;
    while( p!= NULL){
        if(p->data == e)
            return i;
        p = p->next;
        i++;
    }
    return ERROR; 
}

status PriorElem(LinkList L,ElemType e,ElemType &pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L == NULL)
        return INFEASIBLE;
    if(L->next == NULL || L->next->next == NULL)
        return ERROR; //线性表为空或只有一个元素，没有前驱
    LinkList p = L->next;
    while(p->next != NULL) {
        if(p->next->data == e) {
            pre = p->data; 
            return OK;
        }
        p = p->next; 
    }
    return ERROR; 
}

status NextElem(LinkList L,ElemType e,ElemType &next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L == NULL)
        return INFEASIBLE;
    if(L->next == NULL || L->next->next == NULL)
        return ERROR; //线性表为空或只有一个元素，没有后继
    LinkList p = L->next;
    while(p->next != NULL) {
        if(p->data == e) {
            next = p->next->data; 
            return OK;
        }
        p = p->next; 
    }
    return ERROR;
}

status ListInsert(LinkList &L,int i,ElemType e)
// 如果线性表L存在，将元素e插入到线性表L成为第i个元素，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L == NULL)
        return INFEASIBLE;
    if(i < 1 || i > ListLength(L)+1)
        return ERROR;
    LinkList p = L; //p指向头结点
    for(int j = 1; j < i; j++) 
        p = p->next; 
    LinkList s = (LinkList)malloc(sizeof(LNode)); //创建新结点
    s->data = e;
    s->next = p->next; 
    p->next = s; 
    return OK;
}

status ListDelete(LinkList &L,int i,ElemType &e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L == NULL)
        return INFEASIBLE;
    if(i < 1 || i > ListLength(L))
        return ERROR;
    LinkList p = L; 
    while(--i) 
        p = p->next;
    LinkList q = p->next; //q指向要删除的结点
    p->next = q->next; 
    e = q->data; 
    free(q); 
    return OK;
}

status ListTraverse(LinkList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    if(L == NULL)
        return INFEASIBLE;
    LinkList p = L->next;
    while( p != NULL){
        if(p->next != NULL) 
            printf("%d ",p->data); 
        else
            printf("%d",p->data); 
        p = p->next; 
    }
    return OK;
}

status SaveList(LinkList L,char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    if(L == NULL)
        return INFEASIBLE;
    fp = fopen(FileName,"w"); 
    LinkList p = L->next; 
    for(; p != NULL ; p = p->next) 
        fprintf(fp, "%d ", p->data); 
    fclose(fp); 
    return OK; 
}

status LoadList(LinkList &L,char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
    if(L != NULL)
        return INFEASIBLE;
    fp = fopen(FileName,"r");
    L = (LinkList)malloc(sizeof(LNode)); 
    L->next = NULL;
    LinkList p = L;
    ElemType e;
    while(fscanf(fp, "%d", &e) != EOF) {
        LinkList s = (LinkList)malloc(sizeof(LNode)); 
        s->data = e; 
        s->next = NULL; 
        p->next = s; 
        p = s; 
    }
    fclose(fp);
    return OK;
}


//////////////////////////////////////////////////
status reverseList(LinkList &L)
// 如果线性表L存在，反转线性表L，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    if(L==NULL) return INFEASIBLE;
    int n=ListLength(L);
    if(n==0) return OK;
    int data[n];
    LinkList p=L->next;
    while(p!=NULL)
    {
        data[--n]=p->data;
        p=p->next;
    }
    p=L->next;
    while(p!=NULL)
    {
        p->data=data[n++];
        p=p->next;
    }
}

status RemoveNthFromEnd(LinkList &L,int n,ElemType &e)
// 如果线性表L存在，删除线性表L的倒数第n个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L==NULL) return INFEASIBLE;
    int i=ListLength(L)-n+1;
    if(i<1 || i>ListLength(L)) return ERROR;
    ListDelete(L,i,e);
    return OK;
}

status sortList(LinkList &L)
// 如果线性表L存在，将线性表L的元素按从小到大的顺序排列，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    if(L==NULL) return INFEASIBLE;
    int n=ListLength(L);
    if(n==0 || n==1) return OK;
    int data[n];

    //存
    LinkList p=L->next;
    while(p!=NULL)
    {
        data[--n]=p->data;
        p=p->next;
    }

    //排
    for(int i=0;i<ListLength(L);i++)
    {
        for(int j=i+1;j<ListLength(L);j++)
        {
            if(data[i]>data[j])
            {
                int temp=data[i];
                data[i]=data[j];
                data[j]=temp;
            }
        }
    }

    //录
    p=L->next;
    while(p!=NULL)
    {
        p->data=data[n++];
        p=p->next;
    }
}

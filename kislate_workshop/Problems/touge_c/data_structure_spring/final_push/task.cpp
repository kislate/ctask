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
        printf("      ��ѡ����Ĳ���[0~13]:");
        scanf("%d",&op);
        switch(op) {
        case 1:
            if(InitList(L)==OK) printf("      ���Ա����ɹ���\n");
            else printf("      ���Ա���ʧ�ܣ�\n");
            getchar(); getchar();
            break;
        case 2:
            if(DestroyList(L)==OK) printf("      ���Ա����ٳɹ���\n");
            else printf("      ���Ա�����ʧ�ܣ�\n");
            getchar();getchar();
            break;
        case 3:
            if(ClearList(L)==OK) printf("      ���Ա���ճɹ���\n");
            else printf("      ���Ա����ʧ�ܣ�\n");
            getchar();getchar();
            break;
        case 4:
            result = ListEmpty(L);
            if(result == INFEASIBLE) printf("      ���Ա����ڣ�\n");
            else if(result == TRUE) printf("      ���Ա�Ϊ�գ�\n");
            else printf("      ���Ա�Ϊ�գ�\n");
            getchar();
            printf("      �����������...\n");
            getchar();
            break;
        case 5:
            result = ListLength(L);
            if(result == INFEASIBLE) printf("      ���Ա����ڣ�\n");
            else printf("      ���Ա���Ϊ%d\n", result);
            getchar();
            printf("      �����������...\n");
            getchar();
            break;
        case 6:
            printf("      ������Ҫ��ȡ��Ԫ��λ�ã�");
            scanf("%d", &pos);
            result = GetElem(L, pos, e);
            if(result == INFEASIBLE) printf("      ���Ա����ڣ�\n");
            else if(result == ERROR) printf("      λ�ò��Ϸ���\n");
            else printf("      ��%d��Ԫ��Ϊ��%d\n", pos, e);
            getchar();
            printf("      �����������...\n");
            getchar();
            break;
        case 7:
            printf("      ������Ҫ���ҵ�Ԫ��ֵ��");
            scanf("%d", &e);
            loc = LocateElem(L, e);
            if(loc == INFEASIBLE) printf("      ���Ա����ڣ�\n");
            else if(loc == 0) printf("      δ�ҵ���Ԫ�أ�\n");
            else printf("      Ԫ��%d��λ��Ϊ��%d\n", e, loc);
            getchar();
            printf("      �����������...\n");
            getchar();
            break;
        case 8:
            printf("      ������Ҫ����ǰ����Ԫ��ֵ��");
            scanf("%d", &e);
            result = PriorElem(L, e, pre);
            if(result == INFEASIBLE) printf("      ���Ա����ڣ�\n");
            else if(result == ERROR) printf("      Ԫ�ز����ڻ���ǰ����\n");
            else printf("      Ԫ��%d��ǰ��Ϊ��%d\n", e, pre);
            getchar();
            printf("      �����������...\n");
            getchar();
            break;
        case 9:
            printf("      ������Ҫ���Һ�̵�Ԫ��ֵ��");
            scanf("%d", &e);
            result = NextElem(L, e, next);
            if(result == INFEASIBLE) printf("      ���Ա����ڣ�\n");
            else if(result == ERROR) printf("      Ԫ�ز����ڻ��޺�̣�\n");
            else printf("      Ԫ��%d�ĺ��Ϊ��%d\n", e, next);
            getchar();
            printf("      �����������...\n");
            getchar();
            break;
        case 10:
            printf("      ���������λ�ú�Ԫ��ֵ��");
            scanf("%d %d", &pos, &e);
            result = ListInsert(L, pos, e);
            if(result == INFEASIBLE) printf("      ���Ա����ڣ�\n");
            else if(result == ERROR) printf("      λ�ò��Ϸ����ڴ治�㣡\n");
            else printf("      ����ɹ���\n");
            getchar();
            printf("      �����������...\n");
            getchar();
            break;
        case 11:
            printf("      ������ɾ��λ�ã�");
            scanf("%d", &pos);
            result = ListDelete(L, pos, e);
            if(result == INFEASIBLE) printf("      ���Ա����ڣ�\n");
            else if(result == ERROR) printf("      λ�ò��Ϸ���\n");
            else printf("      ɾ����Ԫ��Ϊ��%d\n", e);
            getchar();
            printf("      �����������...\n");
            getchar();
            break;
        case 12:
            if(!ListTrabverse(L)) printf("      ���Ա��ǿձ�\n");
            getchar();
            printf("      �����������...\n");
            getchar();
            break;
        case 13:
            if(ListInsertFast(L) == OK) printf("      ���ٲ���ɹ���\n");
            else printf("      ���ٲ���ʧ�ܣ�\n");
            getchar();
            printf("      �����������...\n");
            getchar();
            break;
        case 0:
            break;
        default:
            printf("      ��Ч�Ĳ�����ţ����������룡\n");
            getchar();
            printf("      �����������...\n");
            getchar();
            break;
        }
    }
    printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
    return 0;
}


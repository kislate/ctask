#include <stdio.h>
#include <stdlib.h>
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
typedef int ElemType;
typedef struct
{
    ElemType *elem;
    int length;
    int listsize;
}SqList;
int insert(SqList &L,ElemType x)
{
    /**********begin**********/
        if(L.length == 0)
        {
            L.elem[0] = x;
            L.length++;
            return 1;
        }
        if(L.length >= L.listsize)
        {
            ElemType *newbase = (ElemType *)realloc(L.elem,(L.listsize + LISTINCREMENT) * sizeof(ElemType));
            if(!newbase)
                return 0;
            L.elem = newbase;
            L.listsize += LISTINCREMENT;
        }
        for(int i = 0; i < L.length; i++)
        {
            if(L.elem[i] < x)
            {
                for(int j = L.length; j > i; j--)
                {
                    L.elem[j] = L.elem[j - 1];
                }
                L.length++;
                L.elem[i] = x;
                return 1;
            }
        }
    /**********end**********/
    }
#include "def.h"
#include "stu.h"
int main() {
	LinkList L;
	int i,j;
	scanf("%d",&i);
	if (!i) { 
		L = NULL;
		j = InitList(L);
 		if (L==NULL) printf("可能没有正确分配表头节点空间");
		if (L->next!=NULL) printf("表头节点可能没有正确初始化");
		if (j==OK) printf("OK");
    }
	else {
		L=(LinkList)malloc(sizeof(LNode));
		j=InitList(L);
		if (j==INFEASIBLE) printf("INFEASIBLE");
		else printf("可能会对已经存在的线性表初始化");
		free(L);
	}
	return 1;
}
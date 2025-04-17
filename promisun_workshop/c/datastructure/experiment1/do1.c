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
typedef int ElemType; //数据元素类型定义

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef int ElemType;
typedef struct{  //顺序表（顺序结构）的定义
	      ElemType * elem;
	      int length;
	      int listsize;
         }SqList;
typedef struct{  //线性表的管理表定义
        struct { char name[30];
                    SqList L;	
            } elem[10];
            int length;
            int listsize;
        }LISTS;
// int main() 1111111111111111111111111111111111111111111111111111111111111111111111111111111
// {
// SqList L;
// int i,j;
// scanf("%d",&i);
// if (!i)
//     { 
//     L.elem=NULL;
//     j=InitList(L);
//     if (L.elem==NULL)
//         printf("可能没有正确分配元素空间");
//     if (L.length)
//         printf("未正确设置元素个数初始值");
//     if (L.listsize!=LIST_INIT_SIZE)
//         printf("未正确设置元素空间容量");
//     if (j==OK) {
//             printf("OK");
//             L.elem[0]=1;
//             L.elem[L.listsize-1]=2;
//             }
//     }
// else
//     {
//     L.elem=(ElemType *) malloc(sizeof(ElemType));
//     j=InitList(L);
//     if (j==INFEASIBLE) printf("INFEASIBLE");
//     else printf("可能会对已经存在的线性表初始化");
//     free(L.elem);
//     }
// return 1;
// }

         
// status InitList(SqList L)
// // 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
// {
//     // 请在这里补充代码，完成本关任务
//     /********** Begin *********/
//     if (L.elem != NULL) //如果线性表已经存在，返回INFEASIBLE
//         return INFEASIBLE;
//     L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType)); //分配空间
//     L.length = 0; //设置元素个数初始值
//     L.listsize = LIST_INIT_SIZE; //设置元素空间容量
//     return OK; //返回OK
//     /********** End **********/
// }



// status lex(FILE *fp,char word[])   //仅查找字母型标识符 222222222222222222222222222222222222222222222222222222222222222222
// {
//     char c,c1,i;
//     while ((c=fgetc(fp))!=EOF && !feof(fp))
//     {
//         if (isspace(c)) continue;
//         if (c=='/')
//         {
//             c==fgetc(fp);
//             if (c==EOF) return ERROR;
//             if (c=='/')
//             {
//                 while ((c=fgetc(fp))!='\n') 
//                        if (c==EOF) return ERROR;
//                 continue;
//             }
//             if (c=='*')
//             {
//                 c=fgetc(fp);
//                 if (c==EOF) return ERROR;
//                 do
//                 {
//                     c1=c;
//                     c=fgetc(fp);
//                     if (c==EOF) return ERROR;
//                  } while (c1!='*' || c!='/');
//                 continue;
//             }
//         }
//         if (!isalpha(c)) continue;
//         i=0;
//         do {
//             	word[i++]=c;
//             } while (isalpha(c=fgetc(fp)));
//         if (isspace(c)|| !(c>='0' && c<='9') || c==EOF)
//         {
//             word[i]='\0';
//             return OK;
//         }
//     }
//     return ERROR;
// }
// status match(char fileName[],char keyword[])
// {
//     FILE *fp;
//     char word[50];
//     fp=fopen(fileName,"r");
//     if (!fp) {printf("文件打开失败"); return FALSE;}
//     while (lex(fp,word)==OK){
//         if (strcmp(keyword,word))
//              continue;
//         fclose(fp);
//         return TRUE;
//     }
//     fclose(fp);
//     return FALSE;
// }

// int main()
// {
// SqList L;
// int f,i,j,e;
// scanf("%d",&f);
// if (f==0)
// 	{
// 	    L.elem=NULL;
//         j=DestroyList(L);
//         if (j==INFEASIBLE) printf("INFEASIBLE");
//         else printf("不能对不存在的线性表进行销毁操作！");
// 	}
// else
//      { 
//         L.elem=(ElemType *) malloc(sizeof(ElemType)*10);
//         L.length=0;
//         L.listsize= 10;
       
//         j=DestroyList(L);
//         if (j==OK) 
//             if (match("src/step02/stu.h","free")==FALSE || L.elem)
//                 printf("未正确释放数据元素空间");
//             else printf("OK");
//         else printf("ERROR");
//      }
// return 1;
// }
// status DestroyList(SqList L)
// // 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
// {
//     // 请在这里补充代码，完成本关任务
//     /********** Begin *********/
//     if (L.elem == NULL) //如果线性表不存在，返回INFEASIBLE
//         return INFEASIBLE;
//     L.elem = NULL; 
//     L.length = 0; 
//     L.listsize = 0; 
//     free(L.elem); //释放线性表的元素空间
//     return OK;
//     /********** End **********/
// }

// int main() { 3333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333
// 	SqList L;
// 	int i,j;
// 	scanf("%d",&i);
// 	if (!i) { 
// 		L.elem=NULL;
// 		j=ClearList(L);
// 		if (j==INFEASIBLE) printf("INFEASIBLE");
//     	else printf("可能会对不存在的线性表清空");
//     }
// 	else {
// 		L.elem=(ElemType *) malloc(sizeof(ElemType));
//         L.length = 1;
// 		j=ClearList(L);
// 		if (L.length) printf("未正确清空");
// 		if (!L.elem)  printf("错误释放元素空间");
// 		if (j==OK) printf("OK");
// 		free(L.elem);
//     }
// 	return 1;
// }


// status ClearList(SqList L)
// // 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
// {
//     // 请在这里补充代码，完成本关任务
//     /********** Begin *********/
//     if(L.elem == NULL) //如果线性表不存在，返回INFEASIBLE
//         return INFEASIBLE;
//     for(int i = 0; i < L.length; i++) 
//         L.elem[i] = 0; 
//     L.length = 0;
//     return OK; 
//     /********** End **********/
// }


// int main() { 44444444444444444444444444444444444444444444444444444444444444444444444444444444444444
// 	SqList L;
// 	int i,j;
// 	scanf("%d",&i);
// 	if (i==2) { 
// 		L.elem=(ElemType *) malloc(sizeof(ElemType));
// 		L.length=0;
// 		j=ListEmpty(L);
// 		if (j==OK) printf("TRUE");
// 		else printf("未正确判空");
// 		free(L.elem);
//     }
// 	else if(i==1) {
// 		L.elem=(ElemType *) malloc(sizeof(ElemType));
// 		L.length=1;
// 		j=ListEmpty(L);
// 		if (j==ERROR) printf("FALSE");
// 		else printf("未正确判空");
// 		free(L.elem);
//     }
//     else {
//     	L.elem=NULL;
//     	L.length=0;
// 		j=ListEmpty(L);
// 		if (j==INFEASIBLE) printf("INFEASIBLE");
//     	else printf("可能会对不存在的线性表判空");
// 	}
// 	return 1;
// }

// status ListEmpty(SqList L)
// // 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
// {
//     // 请在这里补充代码，完成本关任务
//     /********** Begin *********/
//     if (L.elem == NULL) 
//         return INFEASIBLE;
//     if (L.length == 0)
//         return TRUE; //线性表为空
//     else
//         return FALSE; //线性表不为空
//     /********** End **********/
// }

// int main() {   555555555555555555555555555555555555555555555555555555555555555555555555555555555
// 	SqList L;
// 	int f,i,j,c=0;
// 	scanf("%d",&f);
// 	if (!f) {
// 		L.elem=NULL;
//     	L.length=10;
// 		j=ListLength(L);
// 		if (j==INFEASIBLE) printf("INFEASIBLE");
//     	else printf("可能会对不存在的线性表求表长");
//     }
//     else {
//     	L.elem=(ElemType *) malloc(sizeof(ElemType));
//     	scanf("%d",&i);
//      	while (i) {
//          ++c;
//          scanf("%d",&i);
// 		}
// 		L.length=c;
// 		j=ListLength(L);
// 		printf("%d", j);
// 		free(L.elem);
// 	}
// 	return 1;
// }
// status ListLength(SqList L)
// // 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
// {
//     // 请在这里补充代码，完成本关任务
//     /********** Begin *********/
//     if(L.elem==NULL)
//         return INFEASIBLE;
//     else 
//         return L.length;
//     /********** End **********/
// }


// int main() {      66666666666666666666666666666666666666666666666666666666666666666666666666666666
// 	SqList L;
// 	int f,i,j,e;
// 	scanf("%d",&f);
// 	if (!f) {
// 		L.elem=NULL;
// 		j=GetElem(L,2,e); 
// 		if (j==INFEASIBLE) printf("INFEASIBLE");
//     	else printf("可能会对不存在的线性表获取元素");
		
// 	}
// 	else {
// 		L.elem=(ElemType *) malloc(sizeof(ElemType)*10);
// 		L.length=0;
// 		L.listsize= 100;
// 		scanf("%d",&i);
// 		while (i) {
// 			L.elem[L.length++]=i;
// 			scanf("%d",&i);
// 		}
// 		scanf("%d",&i);
// 		j=GetElem(L,i,e);
// 		if(j==OK) printf("OK\n%d",e);
// 		if(j==ERROR) printf("ERROR");
// 		free(L.elem);
// 	}
// 	return 1;
// }

// status GetElem(SqList L,int i,ElemType *e)
// // 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
// {
//     // 请在这里补充代码，完成本关任务
//     /********** Begin *********/
//     if (L.elem == NULL) 
//         return INFEASIBLE;
//     if (i < 1 || i > L.length) 
//         return ERROR;
//     *e = L.elem[i - 1]; 
//     return OK;
//     /********** End **********/
// }



// int main() {          777777777777777777777777777777777777777777777777777777777777777777777777777777777777
// 	SqList L;
// 	int f,i,j,e;
// 	scanf("%d",&f);
// 	if (!f) {
// 		L.elem=NULL;
// 		L.length=3;
// 		j=LocateElem(L,e); 
// 		if (j==INFEASIBLE) printf("INFEASIBLE");
//     	else printf("可能会对不存在的线性表查找元素");
		
// 	}
// 	else {
// 		L.elem=(ElemType *) malloc(sizeof(ElemType)*10);
// 		L.length=0;
// 		L.listsize= 10;
// 		scanf("%d",&i);
// 		while (i) {
// 			L.elem[L.length++]=i;
// 			scanf("%d",&i);
// 		}
// 		scanf("%d",&e);
// 		j=LocateElem(L,e);
// 		if(j==ERROR) printf("ERROR");
// 		else printf("%d",j);
// 		free(L.elem);
// 	}
// 	return 1;
// }
// int LocateElem(SqList L,ElemType e)
// // 如果线性表L存在，查找元素e在线性表L中的位置序号并返回该序号；如果e不存在，返回0；当线性表L不存在时，返回INFEASIBLE（即-1）。
// {
//     // 请在这里补充代码，完成本关任务
//     /********** Begin *********/
//     if(L.elem == NULL) 
//         return INFEASIBLE;
//     for(int i = 0; i < L.length; i++) { 
//         if(L.elem[i] == e) 
//             return i + 1; 
//     }
//     return 0;
//     /********** End **********/
// }

// int main() {  88888888888888888888888888888888888888888888888888888888888888888888888888888888
// 	SqList L;
// 	int f,i,j,e,pre;
// 	scanf("%d",&f);
// 	if (!f) {
// 		L.elem=NULL;
// 		L.length=3;
// 		j=PriorElem(L,e,pre); 
// 		if (j==INFEASIBLE) printf("INFEASIBLE");
//     	else printf("可能会对不存在的线性表查找前驱元素");
// 	}
// 	else {
// 		L.elem=(ElemType *) malloc(sizeof(ElemType)*10);
// 		L.length=0;
// 		L.listsize= 10;
// 		scanf("%d",&i);
// 		while (i) {
// 			L.elem[L.length++]=i;
// 			scanf("%d",&i);
// 		}
// 		scanf("%d",&e);
// 		j=PriorElem(L,e,pre);
// 		if(j==ERROR) printf("ERROR");
// 		if(j==OK) printf("OK\n%d",pre);
// 		free(L.elem);
// 	}
// 	return 1;
// }
// status PriorElem(SqList L,ElemType e,ElemType pre)
// // 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
// {
//     // 请在这里补充代码，完成本关任务
//     /********** Begin *********/
//     if(L.elem == NULL) 
//         return INFEASIBLE;
//     if(L.length == 0) 
//         return ERROR; //线性表为空，没有前驱
//     for(int i = 0; i < L.length; i++) { 
//         if(L.elem[i] == e) {
//             if(i == 0) 
//                 return ERROR; //没有前驱
//             pre = L.elem[i - 1]; 
//             return OK;
//         }
//     }
//     return ERROR; //元素e不存在
//     /********** End **********/
// }

// int main() {        99999999999999999999999999999999999999999999999999999999999999999999999999999999
// 	SqList L;
// 	int f,i,j,e,next;
// 	scanf("%d",&f);
// 	if (!f) {
// 		L.elem=NULL;
// 		L.length=3;
// 		j=NextElem(L,e,next); 
// 		if (j==INFEASIBLE) printf("INFEASIBLE");
//     	else printf("可能会对不存在的线性表查找后继元素");
// 	}
// 	else {
// 		L.elem=(ElemType *) malloc(sizeof(ElemType)*10);
// 		L.length=0;
// 		L.listsize= 10;
// 		scanf("%d",&i);
// 		while (i) {
// 			L.elem[L.length++]=i;
// 			scanf("%d",&i);
// 		}
// 		scanf("%d",&e);
// 		j=NextElem(L,e,next);
// 		if(j==ERROR) printf("ERROR");
// 		if(j==OK) printf("OK\n%d",next);
// 		free(L.elem);
// 	}
// 	return 1;
// }

// status NextElem(SqList L,ElemType e,ElemType next)
// // 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
// {
//     // 请在这里补充代码，完成本关任务
//     /********** Begin *********/
//     if(L.elem == NULL) 
//         return INFEASIBLE;
//     if(L.length == 0) 
//         return ERROR; //线性表为空，没有后继
//     for(int i = 0; i < L.length; i++) { 
//         if(L.elem[i] == e) {
//             if(i == L.length - 1) 
//                 return ERROR; //没有后继
//             next = L.elem[i + 1]; 
//             return OK;
//         }
//     }
//     return ERROR; 
//     /********** End **********/
// }


// int main() 0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
// {
// SqList L;
// int f,i,j,e;
// scanf("%d",&f);
// if (!f)
// 	{
// 	    L.elem=NULL;
//         j=ListInsert(L,1,1);
//         if (j==INFEASIBLE) printf("INFEASIBLE");
//         else printf("不能对不存在的线性表进行插入操作！");
// 	}

// else
//      {
//      L.elem=(ElemType *) malloc(sizeof(ElemType)*10);
//      L.length=0;
//      L.listsize= 10;
//      scanf("%d",&i);
//      while (i)
//      {
//          L.elem[L.length++]=i;
//          scanf("%d",&i);
//      }
//      scanf("%d%d",&i,&e);
//      j=ListInsert(L,i,e);
//      printf("%s\n", j==OK? "OK" : j==ERROR? "ERROR" : "OVERFLOW");
//      for(i=0;i<L.length;i++)
//         printf("%d ",L.elem[i]);
//      }
// return 1;
// }

// status ListInsert(SqList L,int i,ElemType e)
// // 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
// {
//     // 请在这里补充代码，完成本关任务
//     /********** Begin *********/
//     if(L.elem == NULL) 
//         return INFEASIBLE;
//     if(i < 1 || i > L.length + 1)
//         return ERROR; 
//     if(L.length >= L.listsize) {
//         ElemType *newbase = (ElemType *)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType)); //扩展空间
//         L.elem = newbase; 
//         L.listsize += LISTINCREMENT; 
//     }
//     for(int j = L.length; j >= i; j--) 
//         L.elem[j] = L.elem[j - 1]; //后移
//     L.elem[i - 1] = e; //插入元素
//     L.length++; //表长加1
//     return OK; 
//     /********** End **********/
// }

// status ListDelete(SqList L,int i,ElemType e)
// // 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
// {
//     // 请在这里补充代码，完成本关任务
//     /********** Begin *********/
//     if(L.elem == NULL) 
//         return INFEASIBLE;
//     if(i < 1 || i > L.length )
//         return ERROR; 
//     e=L.elem[i - 1]; //保存删除的元素
//     for(int j = i-1; j < L.length-1; j++) 
//         L.elem[j] = L.elem[j + 1]; //前移
//     L.elem[L.length - 1] = 0; //清空最后一个元素
//     L.length--; //表长减1
//     return OK; 
//     /********** End **********/
// }

// int main() {               1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
// 	SqList L;
// 	int f,i,j;
// 	scanf("%d",&f);
// 	if (!f) {
// 		L.elem=NULL;
// 		j=ListTraverse(L); 
// 		if (j==INFEASIBLE) printf("INFEASIBLE");
//     	else printf("可能会对不存在的线性表进行遍历操作！");
// 	}
// 	else {
// 		L.elem=(ElemType *) malloc(sizeof(ElemType)*10);
// 		L.length=0;
// 		L.listsize= 10;
// 		scanf("%d",&i);
// 		while (i) {
// 			L.elem[L.length++]=i;
// 			scanf("%d",&i);
// 		}
// 		j=ListTraverse(L);
// 		if(j==OK && !L.length) printf("空线性表\n");
// 		free(L.elem);
// 	}
// 	return 1;
// }
// status ListTraverse(SqList L)
// // 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
// {
//     // 请在这里补充代码，完成本关任务
//     /********** Begin *********/
//     if(L.elem == NULL) 
//         return INFEASIBLE;
//     if(L.length == 0)
//         return OK; //线性表为空
//     for(int i = 0; i < L.length; i++) {
//         printf("%d ", L.elem[i]); //输出
//     }
//         return OK;
//     /********** End **********/
// }

// SaveList：如果线性表L不存在，返回INFEASIBLE；否则将线性表L的全部元素写入到文件名为FileName的文件中，返回OK。
// LoadList：如果线性表L存在，表示L中已经有数据，读入数据会覆盖原数据造成数据丢失，返回INFEASIBLE；否则将文件名为FileName的数据读入到线性表L中，返回OK。
// 本实验不考虑用追加的方式读入文件数据追加到现有线性表中。
// int main()
// {
// SqList L;
// FILE *fp;
// //char FileName[30];
// int f,i=0,j,e;
// //strcpy(FileName,"src/step13/list.dat");
// scanf("%d",&f);
// if (!f)
// {
//     	L.elem=NULL;
//    		j=SaveList(L,"src/step13/list.dat");
//    		if (j!=INFEASIBLE) printf("不能对不存在的线性表进行写文件操作！");
//     	else 
//       {
//     		 L.elem=(ElemType *) malloc(sizeof(ElemType));
//    			 j=LoadList(L,"src/step13/list.dat");
//    			 if (j!=INFEASIBLE) printf("不能对已存在的线性表进行读文件操作！");
//     	    else printf("INFEASIBLE"); 
//     		 free(L.elem);
//       }
// }
// else
//      {
//         L.elem=(ElemType *) malloc(sizeof(ElemType)*LIST_INIT_SIZE);
//         L.length=0;
//         L.listsize= LIST_INIT_SIZE;
//         scanf("%d",&e);
//         while (e)
//         {
//             L.elem[i++]=e;
//             scanf("%d",&e);
//         }
//         L.length=i;
//         j=SaveList(L,"src/step13/list.dat");
//    		free(L.elem); 
// 		L.elem=NULL;
//         j=LoadList(L,"src/step13/list.dat");
//         printf("%d\n",L.length);
//         for(i=0;i<L.length;i++) 
//             printf("%d ",L.elem[i]);
//      }
// return 1;
// }

// status  SaveList(SqList L,char FileName[])
// // 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
// {
//     // 请在这里补充代码，完成本关任务
//     /********** Begin *********/
//     if(L.elem == NULL) 
//         return INFEASIBLE;
//     FILE *fp = fopen(FileName, "w"); 
//     for(int i = 0; i < L.length; i++) {
//         fprintf(fp, "%d ", L.elem[i]); 
//     }
//     fclose(fp); 
//     return OK; 
//     /********** End **********/
// }
// status  LoadList(SqList L,char FileName[])
// // 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
// {
//     // 请在这里补充代码，完成本关任务
//     /********** Begin *********/
//     if(L.elem != NULL) 
//         return INFEASIBLE;
//     FILE *fp = fopen(FileName, "r"); 
//     L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
//     L.length = 0;
//     L.listsize = LIST_INIT_SIZE;
//     while (fscanf(fp, "%d", &L.elem[L.length++]) != EOF) {
//         if (L.length >= L.listsize) {
//             L.elem = (ElemType *)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType)); 
//             L.listsize += LISTINCREMENT; 
//         }
//     }
//     fclose(fp);
//     L.length--;
//     return OK;
//     /********** End **********/
// }


int main() {
	LISTS Lists;
   int n,e;
   char name[30];
   Lists.length=0;
	scanf("%d", &n);
	while(n--)
   {
    	scanf("%s",name);
   		AddList(Lists,name);
      scanf("%d",&e);
      while (e)
      {
      		ListInsert(Lists.elem[Lists.length-1].L,Lists.elem[Lists.length-1].L.length+1,e);
      		scanf("%d",&e);
      }
   }
   for(n=0;n<Lists.length;n++)
   {
   		printf("%s ",Lists.elem[n].name);
   		ListTraverse(Lists.elem[n].L);
        putchar('\n');
   }
return 1;
}
status AddList(LISTS Lists,char ListName[])
// 只需要在Lists中增加一个名称为ListName的空线性表，线性表数据又后台测试程序插入。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (Lists.length >= 10) //判断是否超过最大线性表数量
        return ERROR;
    strcpy(Lists.elem[Lists.length].name, ListName);
    Lists.elem[Lists.length].L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType)); //分配空间
    Lists.elem[Lists.length].L.length = 0; 
    Lists.elem[Lists.length].L.listsize = LIST_INIT_SIZE; 
    Lists.length++; //线性表数量加1  
    return OK;  
    /********** End **********/
}

#include <string.h>
status RemoveList(LISTS Lists,char ListName[])
// Lists中删除一个名称为ListName的线性表
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    for(int i=0;i<Lists.length;i++)
    {
        if(strcmp(Lists.elem[i].name, ListName)==0)
        {
            for(;i<Lists.length-1;i++)
                Lists.elem[i]=Lists.elem[i+1];
            Lists.elem[i].L.elem = NULL; 
            Lists.elem[i].L.length = 0; 
            Lists.elem[i].L.listsize = 0; 
            free(Lists.elem[i].L.elem);
            Lists.length--;
            return OK;
        }
    }
    return ERROR;
    /********** End **********/
}

int LocateList(LISTS Lists,char ListName[])
// 在Lists中查找一个名称为ListName的线性表，成功返回逻辑序号，否则返回0
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    for(int i=0;i<Lists.length;i++)
    {
        if(strcmp(Lists.elem[i].name, ListName)==0)
            return i+1;
    }
    return 0;
    /********** End **********/
}
#include "stdio.h"
typedef char ElemType;
#define MAXLENGTH 100
#define N 100
typedef struct TWSTACK {
     ElemType elem[N];
     int top1,top2;
     } TWSTACK;
typedef struct QUEUE {
     ElemType elem[MAXLENGTH];
     int front,length;
     } QUEUE;
#include "queue.cpp"
#include "twstack.cpp"
#include "stu.h"

int isPalindrome(char *str);

int main()
{
    char str[100];
    scanf("%s",str);
    printf("%s",isPalindrome(str)?"YES":"NO");
    return 0;
}

int isPalindrome(char *str)
//判断字符串str是否回文，是则返回1，否则返回0
{
/**********begin**********/
     if(str==NULL) return 0;
     TWSTACK S;QUEUE Q;
     inistack(S);
     iniQueue(Q);
     for(int i=0;str[i]!='@';i++) push(S,1,str[i]);
     for(int i=0;str[i]!='@';i++) enQueue(Q,str[i]);
     for(int i=0;str[i]!='@';i++)
     {
         int a,b;
         pop(S,1,a);
         deQueue(Q,b);
         if(a!=b) return 0;
     }
     return 1;
/********** end **********/
}


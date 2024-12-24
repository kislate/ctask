/*消除类游戏是一种益智游戏，其核心规则是将一定的彼此相邻的相同元素配对消除。现给定一个n行m列的棋盘，棋盘中的每一个方格上放着一个棋子，每个棋子都有颜色，编号用1~9表示。当一行或一列上有连续3个或3个以上同色棋子时，这些棋子都被同时消除，对应的方格用0表示，请输出经过消除后的棋盘。例如，给定棋盘为：
4 4 3 1 4
3 1 1 1 1
4 3 4 1 2
4 4 2 2 2
消除后为：
4 4 3 0 4
3 0 0 0 0
4 3 4 0 2
4 4 0 0 0

示例
输入（输入的前两个数字为棋盘的行数和列数）：
4 5
4 4 3 1 4
3 1 1 1 1
4 3 4 1 2
4 4 2 2 2
输出（同行每个元素之间以空格分隔）：
4 4 3 0 4
3 0 0 0 0
4 3 4 0 2
4 4 0 0 0   */
/*#include <stdio.h>
int row,col;
int rpos=0,cpos=0;  //记录pos位置
int pos[50][2];  //记录可消除的位置


void delete(int chess[][10]);
void deleteRow(int chess[][10]);
void deleteCol(int chess[][10]);

int main()
{
    scanf("%d %d",&row,&col);
    int chess[row][10];
    //输入
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++) scanf("%d",&chess[i][j]);
    }
    //消除
    delete(chess);
    //输出
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++) 
        {
            printf("%d",chess[i][j]);
            if(j<col-1) printf(" ");
        }
        if(i<row-1) printf("\n");
    }
}

void delete(int chess[][10])
{
    deleteRow(chess);
    deleteCol(chess);
    for(int i=0;i<rpos;i++)
    {
        chess[pos[i][0]][pos[i][1]]=0;
        chess[pos[i][0]][pos[i][1]+1]=0;
        chess[pos[i][0]][pos[i][1]+2]=0;
    }
    for(int j=rpos;j<cpos;j++)
    {
        chess[pos[j][0]][pos[j][1]]=0;
        chess[pos[j][0]+1][pos[j][1]]=0;
        chess[pos[j][0]+2][pos[j][1]]=0;
    }
}

void deleteRow(int chess[][10])//按理说应该是标记而非删除，deleteCol同理
{
    for(int r=0;r<row;r++)
    {
        for(int i=0;i<col-2;i++)
        {
            if(chess[r][i]==chess[r][i+1]&&chess[r][i]==chess[r][i+2]) 
            {
                pos[rpos][0]=r;
                pos[rpos][1]=i;
                rpos++;
            }
        }
    }
    cpos=rpos;
}

void deleteCol(int chess[][10])
{
    for(int c=0;c<col;c++)
    {
        for(int i=0;i<row-2;i++)
        {
            if(chess[i][c]==chess[i+1][c]&&chess[i][c]==chess[i+2][c]) 
            {
                pos[cpos][0]=i;
                pos[cpos][1]=c;
                cpos++;
            }
        }
    }
}*/


/*#include<stdio.h>
#include<stdlib.h> 
#include<string.h>
// ��ָ������sָ���size���ַ��������������� 
void strsort ( char *s[],int size );
{ 
    char* temp; 
    int i, j ;
    for(i=0; i<size-1; i++)
        for(j=0; j<size-i-1; j++) 
            if ( strcmp(s[j],s[j+1])>0 )  
    		{ 
                temp=s[j];
                s[j]=s[j+1];    
	            s[j+1]=temp; 
            }
 }
int main( )
{ 
    int i,N;
    scanf("%d",&N);
    char *s[N], t[50]; 
    for(i=0;i<N;i++)   
    {
       scanf("%s",t);
       s[i] = (char *)malloc(strlen(t)+1);
       strcpy(s[i],t); 
    }
    strsort(s,N);    
    for(i=0;i<N;i++)  printf("%s\n",s[i]);
    return 0;
}

//�ö���ָ���β���д��2�ص�strsort�����������ڸú�������κ�λ�ö�������ʹ���±����á�(improve)
void strsort (char**s,int size)
{
	char **i,**j,*temp;
	for(i=s;i<s+size-1;i++)
		for(j=i+1;j<s+size;j++)
			if(strcmp(*i,*j)>0)	
			{
				temp=*i;
				*i=*j;
				*j=temp;
			}
} */
 
/* 
#include <stdio.h>
#include <string.h>

int main(void)
{
    char *(*p)(char*,const char*);
    char a[80], b[80], *result;
    int choice;


    while(1)
    {
        do
        {
            printf("\t\t1 copy string.\n");
            printf("\t\t2 connect string.\n");
            printf("\t\t3 Parse string.\n");
            printf("\t\t4 exit.\n");
            printf("\tinput a number (1-4) please!\n");
            scanf("%d", &choice);
        } while (choice<1||choice>4);
        

        switch(choice)
        {
            case 1: p=strcpy; break;
            case 2: p=strcat; break;
            case 3: p=strtok; break;
            case 4: goto down;
        }


        getchar();
        printf("input the first string please!\n");
        scanf("%s",a);
        printf("input the second string please!\n");
        scanf("%s",b);
        result=(*p)(a,b);
        printf("the result is %s\n", result);
    }
down:
    return 0;
}
 
#include <stdio.h>
#include <string.h>

int main(void)
{
    char *(*p[3])(char*,const char*)={strcpy,strcat,strtok};
    char a[80], b[80], *result;
    int choice;


    while(1)
    {
        do
        {
            printf("\t\t1 copy string.\n");
            printf("\t\t2 connect string.\n");
            printf("\t\t3 Parse string.\n");
            printf("\t\t4 exit.\n");
            printf("\tinput a number (1-4) please!\n");
            scanf("%d", &choice);
        } while (choice<1||choice>4);
	
		if(choice==4) return 0;
        getchar();
        printf("input the first string please!\n");
        scanf("%s",a);
        printf("input the second string please!\n");
        scanf("%s",b);
        result=(*p[choice-1])(a,b);
        printf("the result is %s\n", result);
    }
}*/

/*
#include<stdio.h>
int main()
{
    int n;
    char *p=(char*)&n+3;//ָ����ֽ� 
    scanf("%d",&n);
    do
    {
        int a,b;
        char c,d;
        a = ((*p)>>4)&0x0f;
        b = (*p)&0x0f;
        if(a>=10) c='a'+a-10;
        else c='0'+a;
        if(b>=10) d='a'+b-10;
        else d='0'+b;
        p--;
        printf("%c %c ",c,d);
    } while(p>=(char*)&n);
    
}*/


/*
#include<stdio.h>
int RemoveSame(int *s,int n)
{
    int c=1,same=*s,*j=s;//c���䲻ͬԪ�أ�same����ͬ�жϣ�j���ڸı����� 
    
    for(int *i=s+1;i<s+n;i++)
    {
        if(*i==same)continue;
        else {
            j++;
            same=*i;
            *j=*i;
            c++;
        }
    }
    return c;
}

int main()
{
    int n,count;
    scanf("%d",&n);
    int arr[n];
    for(int i=0;i<n;i++) scanf("%d",&arr[i]);//����������ģ��ʲ���Ҫ����
    count=RemoveSame(arr,n);
    for(int j=0;j<count;j++) printf("%d ",arr[j]);
    printf("\n");
    printf("%d",count);
}*/





/*
#include<stdio.h>
#include <stdlib.h>
int row,col;
void RotateMartix(int **s,int **t);

int main()
{
    scanf("%d %d",&row,&col);
    
    int **Martix = (int **)malloc(row * sizeof(int *));
    int **Rmartix = (int **)malloc(col * sizeof(int *));
    for (int i = 0; i < row; ++i) {
        Martix[i] = (int *)malloc(col * sizeof(int));
        // ��ʼ������
        for (int j = 0; j < col; ++j) {
            scanf("%d",&Martix[i][j]) ;
        }
    }
    for (int i = 0; i < col; ++i) {
        Rmartix[i] = (int *)malloc(row * sizeof(int));
    }
    
    RotateMartix(Rmartix,Martix);
    
    for(int i=0;i<col;i++)
    {
        for(int j=0;j<row;j++) 
        {
            printf("%d",Rmartix[i][j]);
            if(j<(row-1))printf(" ");
        }
        if(i<col-1) printf("\n");
    }
    
    for (int i = 0; i < row; ++i) {
        free(Martix[i]);
    }
    for (int i = 0; i < col; ++i) {
        free(Rmartix[i]);
    }
    free(Rmartix);
    free(Martix);
}

void RotateMartix(int **s,int **t)
{
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            s[col-j-1][i]=t[i][j];
        }
    }
}*/


/*
#include<stdio.h>
#include<string.h>
int delSubstr(char *s,const char* t)//s��ɾt
{
    int i=0,len2=strlen(t);
    char *p=strstr(s,t);
    while(p!=NULL)
    {
    	int len1=strlen(s);//len1��������ı���ı� 
    	for(char* pp=s;pp<s+len1;pp++)
        {
            if(pp==p)//����substr
                {
                    for(;(pp+len2)<(s+len1);pp++)
                        *pp=*(pp+len2);
                    *pp='\0';
                    break;//ɾ�Ӵ�
                }
        }
        i++;
        if(i>=1) p=strstr(p,t);//������
    }
    if(!i)return 0;
    return 1;
}

int main()
{
    char str[50],substr[10];//���Զ�̬����ʹ�ڴ�������
     scanf("%[^\n]",str);
	 getchar();
     scanf("%[^\n]",substr);
//	fgets(str,50,stdin); 
//	fgets(substr,10,stdin);
    int g=delSubstr(str,substr);
    printf("%s\n",str);
    printf("%d",g);
}*/


/*
#include<stdio.h>
#include<string.h>
void task0()
{
    printf("task0 is called!\n");
}
void task1()
{
    printf("task1 is called!\n");
}
void task2()
{
    printf("task2 is called!\n");
}
void task3()
{
    printf("task3 is called!\n");
}
void task4()
{
    printf("task4 is called!\n");
}
void task5()
{
    printf("task5 is called!\n");
}
void task6()
{
    printf("task6 is called!\n");
}
void task7()
{
    printf("task7 is called!\n");
}
int diaoyong[20];//����ú������
void (*p[8])(void)={task0,task1,task2,task3,task4,task5,task6,task7};

void execute(int n)
{
    for(int i=0;i<n;i++)
        (*p[diaoyong[i]])();//���ε���
}


void scheduler(void)
{
    char c;
    int n=0;//������
    while((c=getchar())!='\n')
    {
        diaoyong[n++]=c-'0';
    }
    execute(n);
}
int main()
{
    scheduler();
    return 0;
}*/

/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define Max 400 //����������200λ�ķǸ�������������400λ
int result[Max]={0};

int Multiply(char*s,char*t)
{
    int len1=strlen(s),len2=strlen(t),pos=0;//pos�洢���λ��
    char*p=s+len1-1,*q=t+len2-1;//ָ���λ
    for(int i=0;p>=s;p--,i++)
    {
        for(int j=0;q>=t;q--,j++)
        {
            result[i+j]=result[i+j]+(p[0]-'0')*(q[0]-'0');
        }
        q=t+len2-1;//���� 
    }//��ʱresult�ڸ���û��λ,�Ҿ�������200*81*��1.1��=17820;
    int carry=0;//�����λ
    for(int m=0;!(carry==0&&result[m+1]==0);pos++)
    {
        if(result[m]>9)
        {
            carry=result[m]/10;
            result[m++]%=10;
            result[m]+=carry;
            carry=0;
        }
    }
    return pos;
}
int main()
{
    char num1[200],num2[200];
    scanf("%s",num1);
    scanf("%s",num2);
    if(num1[0]==0||num2[0]==0) printf("0");
    else
	{
		int pos=Multiply(num1,num2);
    	for(int i=pos;i>=0;i--)
        	printf("%d",result[i]);
	}
    return 0;
}*/



/*
#include <stdio.h>
#include <string.h>

int main(void)
{
    char *(*p)(char*,const char*);
    char a[80], b[80], *result;
    int choice;


    while(1)
    {
        do
        {
            scanf("%d", &choice);
        } while (choice<1||choice>4);
        

        switch(choice)
        {
            case 1: p=strcpy; break;
            case 2: p=strcat; break;
            case 3: p=strtok; break;
            case 4: goto down;
        }
        getchar();
        scanf("%[^\n]",a);
        getchar();
        scanf("%[^\n]",b);
        result=(*p)(a,b);
        printf("%s\n", result);
    }
down:
    return 0;
}*/


/*
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
struct Node
{
    char value;
    struct Node *next;
};
typedef struct Node node;

node * createList(void);//��������(β�巨)
void addback(node *q,char c);//β���ӽڵ�
node *operateSimilar(node *phead,char c);//�ҵ���������c��ӽ��Ľ�㲢����
void printList(node *phead);//��������
node * deleteNode(node* p,node *phead);//ɾ�����

int main()
{
    node *phead=createList();
    char c;
    scanf(" %c",&c);//��ֹǰ���ո�Ӱ��

    node *p=phead;
    for(;p!=NULL;p=p->next)
        printf("%c ",p->value);
    printf("\n");
    printList(phead);
    
    phead=operateSimilar(phead,c);
    printList(phead);
    
    return 0;
}

node *createList(void)
{
    node *head=NULL,*p,*tail=NULL;
    char c;
    while((c=getchar())!='\n')
    {
        p=(node*)malloc(sizeof(node));
        p->value=c;
        if(head==NULL)
            head=p;//�׽�����ձ�
        else
            tail->next=p;//���������β��
        tail=p;//β�巨
    }
    if (tail != NULL) {
        tail->next = NULL;
    }
    return head;
}

void printList(node *phead)
{
    node *p=phead;
    for(;p!=NULL;p=p->next)
        printf("%c",p->value);
    printf("\n");
}

node *operateSimilar(node *phead,char c)//
{
    node  *p=phead,*q=NULL,*last=NULL;//q��������,������Ӳ���;lastָ��p��ǰһ�����,����ɾ������
    int min=100;

    for(;p!=NULL&&p->value!=c;)
    {
        last = p;
        if(abs(p->value-c)<min)
        {
            min=abs(p->value-c);
            q=p;
        }
        p=p->next;
    } 
    if(p==NULL) addback(q,c);
    else 
    {
        return deleteNode(last,phead);
    }
    return phead;
}

node* deleteNode(node* p,node *phead)
{
    if(p==NULL) //˵��ͷ����Ҫɾȥ�Ľ��
    {
        node *q=phead;
        phead=phead->next;
        free(q);
        return phead;
    }
    node *temp = p->next;
    p->next = p->next->next;
    free(temp);
    return phead;
}

void addback(node *q,char c)
{
    node *p=(node*)malloc(sizeof(node));
    p->value=c;
    p->next=q->next;
    q->next=p;
}
*/

/*
#include <stdio.h>
int main()
{
    char u[]="UVWXYZ",v[]="xyz";
    struct T
    {
        int x;
        char c;
        char *t;
    } a[]={{11,'A',u},{100,'B',v}},*p=a;
    int n;
    scanf("%d",&n);
    switch (n)
    {
    case 1:
        printf("%d\n",(++p)->x);
        break;
    case 2:
        p++;
        printf("%c\n",p->c);
        break;
    case 3:
        printf("%c\n",*p++->t);
        printf("%c\n",*p->t);
        break;
    case 4:
        printf("%c\n",*(++p)->t);
        break;
    case 5:
        printf("%c\n",*++p->t);
        break;
    case 6:
        printf("%c\n",++*p->t);
        break;
    default:
        break;
    }
    return 0;
}*/

/*
#include <stdio.h>
#include <stdlib.h>
struct s_list{
    int data;
    struct s_list *next;
};
void create_list(struct s_list **headp,int *p);
int main(void){
    struct s_list *head=NULL,*p;
    int s[]={1,2,3,4,5,6,7,8,0};
    create_list(&head,s);
    p=head;
    while (p){
        printf("%d\t",p->data);
        p=p->next;
    }
    printf("\n");
    return 0;  
}
void create_list(struct s_list **headp,int *p){
    struct s_list *loc_head=NULL,*tail;
    if(p[0]==0);
    else {
        loc_head=(struct s_list *)malloc(sizeof(struct s_list));
        loc_head->data=*p++;
        tail=loc_head;
        while (*p)
        {
            tail->next=(struct s_list *)malloc(sizeof(struct s_list));
            tail=tail->next;
            tail->data=*p++;
        }
        tail->next=NULL;
        
    }
    *headp=loc_head;
}*/


/*
#include <stdio.h>
struct bits
{
    unsigned int bit0 : 1;
    unsigned int bit1 : 1;
    unsigned int bit2 : 1;
    unsigned int bit3 : 1;
    unsigned int bit4 : 1;
    unsigned int bit5 : 1;
    unsigned int bit6 : 1;
    unsigned int bit7 : 1;
};
void f0(int b){
    printf("the function %d is called!\n",b);
}
void f1(int b){
    printf("the function %d is called!\n",b);
}
void f2(int b){
    printf("the function %d is called!\n",b);
}
void f3(int b){
    printf("the function %d is called!\n",b);
}
void f4(int b){
    printf("the function %d is called!\n",b);
}
void f5(int b){
    printf("the function %d is called!\n",b);
}
void f6(int b){
    printf("the function %d is called!\n",b);
}
void f7(int b){
    printf("the function %d is called!\n",b);
}
void (*p_fun[8])(int) = {f0, f1, f2, f3, f4, f5, f6, f7};

int main()
{
    unsigned int n;
    scanf("%d", &n);
    struct bits a;
    a.bit0 = n & 1;
    a.bit1 = (n >> 1) & 1;
    a.bit2 = (n >> 2) & 1;
    a.bit3 = (n >> 3) & 1;
    a.bit4 = (n >> 4) & 1;
    a.bit5 = (n >> 5) & 1;
    a.bit6 = (n >> 6) & 1;
    a.bit7 = (n >> 7) & 1;
    if(a.bit0)
        p_fun[0](0);
    if(a.bit1)
        p_fun[1](1);
    if(a.bit2)
        p_fun[2](2);
    if(a.bit3)
        p_fun[3](3);
    if(a.bit4)
        p_fun[4](4);
    if(a.bit5)
        p_fun[5](5);
    if(a.bit6)
        p_fun[6](6);
    if(a.bit7)
        p_fun[7](7);
    return 0; 
}*/



/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Data
{
    char id[15];
    char name[10];
    int eng;
    int math;
    int phy;
    int c;
    float average;
};
typedef struct Data data;
struct student
{
    data student_data;
    struct student *next;
};
typedef struct student stu;
stu *createList(stu *phead);//������Ϣ
void printList(stu *phead);//�����Ϣ
void modify(stu *phead);//�޸���Ϣ
void average(stu *phead);//����ƽ���ɼ������
void printNewList(stu *phead);//�������Ϣ
void sort2(stu **phead);

int main()
{
    stu *phead=NULL;
    int n;
    scanf("%d",&n);
    while(n)
    {
        switch (n)
        {
        case 1:
            phead=createList(phead);
            break;
        case 2:
            sort2(&phead);
            printList(phead);
            break;
        case 3:
            modify(phead);
            break;
        case 4:
            sort2(&phead);
            average(phead);
            break;
        case 5:
            sort2(&phead);
            printNewList(phead);
            break;
        default:
            break;
        }
        scanf("%d",&n);
    }
    return 0;
}


stu * createList(stu *phead)
{
    stu *s=phead,*p,*tail=NULL;//s������ͷָ��(�������Ϊ�������Ϊ�����������β�������ӳ���ͷ������p���½�㣬tail��βָ��
    int n;//����ѧ������
    int flag=1;//flag��¼ͷָ���Ƿ�Ϊ�� ��0Ϊ�գ�1��Ϊ��
    if(!phead) flag=0;
    scanf("%d",&n);
    
    if(flag) for(;s->next!=NULL;s=s->next);//ͷָ�벻�ղŻ���s->next 
    
    for(int i=0;i<n;i++)
    {
        p=(stu*)malloc(sizeof(stu));
        scanf(" %s %s %d %d %d %d", p->student_data.id, p->student_data.name, &p->student_data.eng, &p->student_data.math, &p->student_data.phy, &p->student_data.c);
        if(flag)//ͷָ�벻�ղŻ���s->next ���ӳ���
        {
        	if(s->next==NULL)
            s->next=p;//�׽�����ձ�
        	else
            tail->next=p;//���������β��
		}
		else//������
		{
			if(!s)
				s=p;
			else
				tail->next=p;
		}
        tail=p;//β�巨
    }
    if (tail != NULL) {
        tail->next = NULL;
    }
    if(!flag) return s;//��ǰ�����������������ͷָ��
    return phead;//��ǰ����������ԭ�����ͷָ��
}

void printList(stu *phead)
{
    stu *p=phead;
    for(;p!=NULL;p=p->next)
        printf("%s %s %d %d %d %d\n", p->student_data.id, p->student_data.name, p->student_data.eng, p->student_data.math, p->student_data.phy, p->student_data.c);
}

void modify(stu *phead)
{
    char id[15];
    int n;
    scanf("%s %d", id, &n);
    stu *p=phead;
    for(;p!=NULL;p=p->next)
    {
        if(strcmp(p->student_data.id, id)==0)
            break;
    }
    if(p==NULL)
    {
        printf("Not found!\n");
        return;
    }
    switch (n)
    {
    case 1:
        scanf("%d", &p->student_data.eng);
        break;
    case 2:
        scanf("%d", &p->student_data.math);
        break;
    case 3:
        scanf("%d", &p->student_data.phy);
        break;
    case 4:
        scanf("%d", &p->student_data.c);
        break;
    default:
        break;
    }
}

void average(stu *phead)
{
    stu *p=phead,*s=phead;
    for(;p!=NULL;p=p->next)
        p->student_data.average=1.00*(p->student_data.eng+p->student_data.math+p->student_data.phy+p->student_data.c)/4;
    for(;s!=NULL;s=s->next)
        printf("%s %s %.2f\n", s->student_data.id, s->student_data.name, s->student_data.average);
}

void printNewList(stu *phead)
{
    stu *p=phead;
    for(;p!=NULL;p=p->next)
        printf("%s %s %d %.2f\n", p->student_data.id, p->student_data.name, p->student_data.eng + p->student_data.math + p->student_data.phy + p->student_data.c, 1.00*(p->student_data.eng+p->student_data.math+p->student_data.phy+p->student_data.c)/4);
}

void sort2(stu **phead)//����ָ���������������
{
    stu *p=*phead,*q,*r;
    for(int i=0;p!=NULL;p=p->next,i++)
    {
        for(q=p->next;q!=NULL;q=q->next)
        {
            if((p->student_data.eng+p->student_data.math+p->student_data.phy+p->student_data.c)>(q->student_data.eng+q->student_data.math+q->student_data.phy+q->student_data.c))
            {
                r=p->next;
                p->next=q->next;
                q->next=r;
                
                r=p;
                p=q;
                q=r;
            }
        }
        if(!i) *phead=p;//ͷָ���ڵ�һ�δ�ѭ���ǻᷢ���ı� 
    }
}*/





/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct c_node{
    char data;
    struct c_node *next;
} C_NODE;   
void createLinkList(C_NODE **headp, char s[]) ;
void judgePalindrome(C_NODE *head);

int main()  
{
    char s[1000],*pc=s;
    int len=0;
    C_NODE *head=NULL,*p;
    scanf("%[^\n]",s);
    createLinkList(&head,s);   
    for(p=head;p;p=p->next) len++;
    if (len!=strlen(s)) { printf("�������Ȳ���ȷ");return 1;}
    else for(p=head;p;p=p->next)
        if (p->data!=*pc++) { printf("�������д�����");return 1;}
    judgePalindrome(head);
    return 1;
}

/*���Գ����������½������
typedef struct c_node{
    char data;  struct c_node *next;
} C_NODE;*/
/*
void createLinkList(C_NODE **headp, char s[]) 
{
    int i=0;
    C_NODE *head=NULL,*p,*tail=NULL;
    while(s[i]!='\0'&&s[i]!='\n')
    {
        p=(C_NODE*)malloc(sizeof(C_NODE));
        p->data=s[i++];
        if(head==NULL)
            head=p;//�׽�����ձ�
        else
            tail->next=p;//���������β��
        tail=p;//β�巨
    }
    if (tail != NULL) {
        tail->next = NULL;
    }
    *headp=head;
}

void judgePalindrome(C_NODE *head)
{
   C_NODE *s,*t;
    int len=0;
    for(s=head;s;s=s->next) len++;
    s=head;
    if(len%2)
        for(int i=0;i<=len/2;i++)
            s=s->next;
    else
        for(int i=0;i<len/2;i++)
            s=s->next;
    t=s;
    for(int i=1,j=len/2-1;i<=len/2;i++,j--)
    {
        s=head;
        for(int m=0;m<j;m++) s=s->next;//�ҵ���Ӧλ��
        if(s->data!=t->data)
        {
            printf("false\n");
            return;
        }
        t=t->next;
    }
    printf("true\n");
}*/


#include<stdio.h>
#include<string.h>
int main(int agrc,const char*agrv[])
{
    int flag=0;
    FILE *pf = fopen("shuzu.c","r");
    if(!pf)
    {
        perror("fopen");
        return 1;
    }
    char *c;
    if(!strcmp(agrv[1],"\p"))
            flag=1;
    for(int i=1;;i++)
    {
        printf("%d ",i);
        fgets(c,100,pf);
        printf("%s",c);
        if(flag)
        {
            if(!i%10)
                if(getchar()=='q')
                    continue;
        }
    }

    if(fclose(pf)==EOF)
    {
        perror("fclose");
        return 1;
    }
	return 0; 
}

#include<stdio.h>
#include<stdlib.h> 
#include<string.h>
/* 对指针数组s指向的size个字符串进行升序排序 */
void strsort ( char *s[],int size )
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

//用二级指针形参重写第2关的strsort函数，并且在该函数体的任何位置都不允许使用下标引用。(improve)
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
		
} 
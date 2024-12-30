#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(void)
{
    int start = 1 ;
    int end = 1;
    int f[10000],a[10000];
    memset(f,0,sizeof(f));
    memset(a,0,sizeof(a));
    int i,j,k,n;
    scanf("%d",&n);
    for( i = 1 ; i <= n ; i++)
        scanf("%d",&a[i]);
    int max = a[1];
    int temp = 1;
    for( i = 1 ; i<=n ; i++)
    {
        int flag = 0;
        f[i] = f[i-1] + a[i];
        if(f[i] < 0) 
        {   
            if( f[i] > max ) max = f[i];
            f[i] = 0;
            temp = i + 1;
            continue;
        }
        if( f[i] > max ) 
        {
            max = f[i];
            start = end;
            end = i;
            flag = 1;
        }
        if(flag)
        {
            start = temp;
        }
        
    }
    printf("%d\n",max);
    printf("start = %d end = %d \n",start,end);
    system("pause");
}//完善了一下，但是好像是一坨屎
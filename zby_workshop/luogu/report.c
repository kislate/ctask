#include<stdio.h>
#include<stdlib.h>

int main(){
    int n,b,temp,h[20000],sum=0,count=0;
    scanf("%d %d",&n,&b);
    for(int i=0;i<n;i++)
    {
        scanf("%d",&h[i]);
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n-1;j++)
        {
            if(h[j]<h[j+1])
            {
                temp=h[j];
                h[j]=h[j+1];
                h[j+1]=temp;
            }
        }
    }
    for(int i=0;sum<b;i++)
    {
        sum+=h[i];
        count++;
    }
    printf("%d",count);
    return 0;
}
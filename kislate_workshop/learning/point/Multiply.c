#include<stdio.h>
int main(void)
{
    char num1[200]={'0'};
    char num2[200]={'0'};
    int num3[10000];
    for(int i=9999;i>=0;i--)
    {
        num3[i]=0;
    }
    int sum1=0;
    int sum2=0;
    int sum3=0;
    for(int i=0;(num1[i]=getchar())!='\n';i++,sum1++);
    for(int i=0;(num2[i]=getchar())!='\n';i++,sum2++);
    for(int i=sum1-1,s=0;i>=0;i--,s++)
    {
        for(int j=sum2-1,t=0;j>=0;j--,t++){
            int a=(unsigned int)(num1[i]-48)*(unsigned int)(num2[j]-48);
            num3[s+t]+=a%10;
            if(num3[s+t]>=10)
            {
                num3[s+t]=num3[s+t]%10;
                num3[s+t+1]+=1;
            }
            num3[s+t+1]+=a/10;
            if(num3[s+t+1]>=10)
            {
                num3[s+t+1]=num3[s+t+1]%10;
                num3[s+t+2]+=1;
            }
        }
    }
    int k=9999;
    for(k;num3[k]==0;k--);
    for(k;k>=0;k--)
    {
        printf("%d",num3[k]);
    }
    return 0;
}
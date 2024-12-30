#include<stdio.h>
#define swap(x,y) x = x + y ; y = x - y ; x = x - y
int main(void)
{
    int a = 1 , b = 1;
    for(int i = 0 ;i < 3 ;i++)
    {
        static int a;
        printf("%d %d\n",a++,b++);
    }
    swap(a,b);
    printf("%d %d",a,b);
    a ^=(-1)<<5;
    return 0;
}
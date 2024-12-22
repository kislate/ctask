#include<stdio.h>
#include<stdlib.h>
int minus(int v1 , int v2)
{
    return v1-v2;
}
int add(int v1,int v2);
{
    return v1+v2;
}
int demo3(int v1,int v2,int (*p)(int ,int ))
{
    return p(v1,v2);
}
int mian(void)
{
    int x,y;
    printf("%d",demo(x,y,add));

     void (*testP)();//这里就定义了一个函数指针，没有参数，输出也是void;

}
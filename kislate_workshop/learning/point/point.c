#include<stdio.h>
#include<stdlib.h>
char * demo1()
{
    char name_1[]="kislate";
    char *p=name_1;
    return *p;//这里返回的地址是在动态区中，随着函数的结束,数组会释放，
    //当你回到main函数中找到一个指针来接受它时，那个地址上已经没东西了；
}
char * demo2()
{
    char *p="kislate";
    return *p;//返回后可以正常打印
}
char * demo3()
{
    char *p=(char*)malloc(sizeof(char)*12);
    *p="kislate";
    return *p;//这时候就可以正常返回了，只要你不free()函数结束时，这个空间还在
}
int main(void)
{

}

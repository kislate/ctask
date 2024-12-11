#include<stdio.h>

typedef union
{
    int i;
    char arr[sizeof(int)];
}CHI;//这个联合体可以找到一个int的每一个字节
//联合体的存储空间是最大的那个元素的大小
//因为联合体的所有元素都是从同一个地址开始的，所以他们的地址是一样的
//后面的元素会覆盖前面的元素；
//每次赋值的时候都会覆盖前面的值；

int main(void)
{

}
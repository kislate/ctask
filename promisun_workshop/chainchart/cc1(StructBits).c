/*本关任务：
设计一个字段结构 struct bits, 它将一个 8 位无符号字节从最低位到最高位声明为 8 个字段，
依次为 bit0, bit1,..., bit7，且 bit0 优先级最高。
同时设计8个函数，第 i 个函数以 biti(i=0, 1, ..., 7)为参数，并且在函数体内输出 biti 的值。
将 8 个函数的名字存入一个函数指针数组 p_fun。如果 bit0 为 1, 调用 p_fun[0] 指向的函数。
如果 struct bits 中有多位为 1，则根据优先级从高到低顺序依次调用函数指针数组 p_fun 中相应元素指向的函数。
8 个函数中的第 0 个函数可以设计为：

void f0(int b){
    printf("the function %d is called!",b);
}
相关知识
为了完成本关任务，你需要掌握：1.结构体。

编程要求
根据题目要求，在右侧编辑器完成程序设计。

测试说明
平台会对你编写的代码进行测试：

测试输入：
32   对应字节二进制为：00100000
预期输出：
the function 5 is called!

测试输入：
111   对应字节二进制为：011001111
预期输出：
the function 0 is called!
the function 1 is called!
the function 2 is called!
the function 3 is called!
the function 5 is called!
the function 6 is called!

开始你的任务吧，祝你成功！*/
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

}
//字段结构可以储存数据特征信息同时充分利用空间，提高程序效率。
//暂时了解字段结构写法即可
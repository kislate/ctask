/*本关任务：
设计一个字段结构 struct bits, 它将一个 8 位无符号字节从最低位到最高位声明为 8 个字段，依次为 bit0, bit1,..., bit7，且 bit0 优先级最高。同时设计8个函数，第 i 个函数以 biti(i=0, 1, ..., 7)为参数，并且在函数体内输出 biti 的值。将 8 个函数的名字存入一个函数指针数组 p_fun。如果 bit0 为 1, 调用 p_fun[0] 指向的函数。如果 struct bits 中有多位为 1，则根据优先级从高到低顺序依次调用函数指针数组 p_fun 中相应元素指向的函数。
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
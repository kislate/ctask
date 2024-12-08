#include "tmyString.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

void put1(const char* str)//这里不会改变字符串的内容，自定义puts，不会加上换行符；
{
    while (*str != '\0')
    {
        putchar(*str++);//直接用地址，不用数组，更加方便；
    }
}

int put2(const char* str)//这个函数可以为我统计字符串的长度；
{
    int count=0;
    while (*str)//不需要直接判断是否为'\0'，因为'\0'是0，所以可以直接判断；
    {
        putchar(*str++);
        count++;
    }
    putchar('\n');
    return count;
}
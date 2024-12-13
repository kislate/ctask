#ifndef MYSTDIO_H
#define MYSTDIO_H

long fac(int n);//阶乘

long sum_fac(int n); //阶乘和

int isPrime(int n); //素数判断

int gcd(int a, int b);//最大公约数

int lcm(int a, int b);//最小公倍数

long fibonacci(int n);//斐波拉契数

int isLeapyear(int n);//闰年判断

int combination(int i,int j);//组合数Cij，i为下标

void swap(int *a,int *b);//交换（传的是地址）

char swapLetter(char c);//字母大小写转换

void selectSort(int arr[],int n);//升序排列

void outArray(int arr[],int n);//打印数组

void myrever(void);//递归逆序输出字符，用getchar与putchar

void bubble_sort(int arr[],int n);//冒泡排序

void strnins(char *t,char *s,int n);//s插入t第N个位置之后（没打印，要打印printf数组t即可）

void strcate(char t[],char s[]);//拼接两字符串

void strdelc(char s[],char c);//删特定字符 

int isPalindrome(char arr[],int len);//递归回文判断,要传数组长度

void move(int u[],int n,int k);//二分段交换:输入n个整数到数组u中，再输入正整数k(0< k < n )，k将数组u的n个元素划分为u[0]，……，u[k-1]和u[k]，……，u[n-1]两段，将两段元素交换位置但仍然存放在数组u中

int divideFindLeft(int arr[], int size, int target);//二分查找最左侧索引

int divideFindRight(int arr[], int size, int target) ;//二分查找最右侧索引

void divideFind(int arr[], int size, int target);//二分查找所有匹配项
#endif 
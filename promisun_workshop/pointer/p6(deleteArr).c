// 删除子串。

// 编写一个函数 delSubstr(str, substr)，删除字符串 str 中出现的所有子串 substr。
// 如果成功删除子串，则函数返回 1；
// 如果 str 中不包含子串 substr，则 str 未作修改，函数返回0。
// 要求：子串在函数中不会被修改；函数中的任何地方都不使用下标引用；
//     允许使用strstr、strcpy 等标准库函数。在 main 函数中输出删除子串后的结果字符串。

// 输入输出示例
// 示例1：
// 输入：先输入字符串str,再输入字符串substr。
// hello world!
// ll

// 输出：输出删除子串后的结果字符串以及返回值。
// heo world!
// 1

// 示例2：
// 输入：
// hello world!
// how

// 输出：
// hello world!
// 0

// strstr
// 函数原型
// c
// 深色版本
// char *strstr(const char *haystack, const char *needle);
// 参数
// haystack: 指向要搜索的源字符串的指针。
// needle: 指向要在 haystack 中查找的子串的指针。如果 needle 是空字符串（即只有终止符 \0），则函数总是返回 haystack。
// 返回值
// 如果找到匹配的子串，则返回指向 haystack 中第一次出现的子串的指针。
// 如果未找到匹配项，则返回 NULL。


#include<stdio.h>
#include<string.h>
int delSubstr(char *s,const char* t)//s中删t
{
    int i=0,len1=strlen(s),len2=strlen(t);
    char *p[5];
    p[0]=strstr(s,t);
    for(;p[i]!=NULL;)
    {
        i++;
        if(i>=1) p[i]=strstr(p[i-1]+1,t);
    }
    for(int j=0;j<i;j++)
    {
        for(char* pp=s;pp<s+len1&&(*pp)!='\0';pp++)
        {
            if(pp==p[j])
                {
                    for(;(pp+len2)<(s+len1)&&*(pp+len2)!='\0';pp++)
                        *pp=*(pp+len2);
                    *pp='\0';
                    break;
                }
        }
    }
}
int main()
{
    char str[50],substr[10];//可以动态分配使内存无冗余
    scanf("%[^\n]",str);
	getchar();
    scanf("%[^\n]",substr);
//	fgets(str,50,stdin);
//	fgets(substr,10,stdin);
    delSubstr(str,substr);
    printf("%s",str);
}
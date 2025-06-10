#include "stdio.h"
#include "stdlib.h"
#include "string.h"
typedef struct {
	char *ch;
   int length;
} HString;
void Replace(HString &S,HString T,HString V)
//
{
/************** begin *****************/
// kmp算法求解
// 求next数组;
int *next = (int *)malloc((T.length+1)*sizeof(int));
next[0] = -1;
int j = -1, i = 0;
while(i < T.length)
{
    while(j != -1 && T.ch[i] != T.ch[j]) j = next[j];
    next[++i] = ++j;
}
/*for(int i = 0; i < T.length; i++)
    printf("%d ", next[i]);// 非常完美的next数组
*/
// kmp算法匹配
int k = 0, m = 0, cnt = 0;
// 存储新串的数组
char *newStr = (char *)malloc(1000* sizeof(char));
while(k < S.length)
{
    if(m == T.length) // 全匹配成功
    {
        for(int i = 0; i < V.length; i++) newStr[cnt++] = V.ch[i];
        m = 0;
    }
    if(S.ch[k] == T.ch[m]) k++, m++; // 单匹配成功, 匹配数加一,继续匹配下一个字符
    else{
        if(m == 0) newStr[cnt++] = S.ch[k++]; // 单匹配失败, k加一, m不变
        else
        {
            // 把之前没加的给加上去
            for(int i = 0; i < (m - next[m]); i++) newStr[cnt++] = S.ch[k - m + i];
            m = next[m];
            if(m == -1) m = 0;
        }
    }
    // if(k == S.length) // 未能正确处理结束时如果刚好有需要处理的字符串的情况
    // {
    //     for(int i = k - m; i < S.length; i++) newStr[cnt++] = S.ch[i]; // 把剩下的字符加上去
    //     break;
    // }
    if(k == S.length)
    {
        if(m == T.length) 
        {
            for(int i = 0; i < V.length; i++) newStr[cnt++] = V.ch[i];
            m = 0;
            break;
        }
        else
        {
            for(int i = k - m; i < S.length; i++) newStr[cnt++] = S.ch[i];
            break;
        }
    }
}
free(next);
free(S.ch);
S.ch = newStr;
S.length = cnt;
/**************  end  *****************/
}
int main()
{
HString S[3];
char buf[100],i,j;
for(i=0;i<3;i++)
{
	fgets(buf,100,stdin);
	S[i].length=strlen(buf)-1;  //-1是去掉回车符号
	S[i].ch=(char *)malloc(S[i].length);
	for(j=0;j<S[i].length; j++)
		S[i].ch[j]=*(buf+j);
}
Replace(S[0],S[1],S[2]);
printf("S的长度：%d\n",S[0].length);
for(i=0;i<S[0].length;i++)
	putchar(S[0].ch[i]);
return 1;

}
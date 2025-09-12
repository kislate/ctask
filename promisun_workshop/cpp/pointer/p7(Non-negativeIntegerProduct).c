
// 求两个不超过200位的非负整数积。
// （本题涉及高精度计算，可参考理论课教材例8.9 和 实验课教材 例6.17）

// 输入输出示例
// 示例一
// 输入：
// 123
// 456

// 输出：
// 56088

// 示例二
// 输入：
// 666666666666666666666666666666666666666666666666666666666666666666
// 22222222222222222222222222222222222222222222222222222222222222222

// 输出：
// 1481481481481481481481481481481481481481481481481481481481481481465
// 1851851851851851851851851851851851851851851851851851851851851852
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define Max 400 //两个不超过200位的非负整数积不超过400位
int result[Max]={0};

int Multiply(char*s,char*t)
{
    int len1=strlen(s),len2=strlen(t),pos=0;//pos存储结果位数
    char*p=s+len1-1,*q=t+len2-1;//指向低位
    for(int i=0;p>=s;p--,i++)
    {
        for(int j=0;q>=t;q--,j++)
        {
            result[i+j]=result[i+j]+(p[0]-'0')*(q[0]-'0');
        }
        q=t+len2-1;//重置

    }//此时result内各数没进位,且均不超过200*81*（1.1）=17820;
    int carry=0;//保存进位

//进位
    for(int m=0;!(carry==0&&result[m+1]==0);pos++) //应该有一些特殊情况没考虑到，判断循环结束的条件可能有纰漏
    //————>如果result改为字符串数组，则对result进行自增再*result得到后续字符串与0比较则判断循环结束没问题
    {
        if(result[m]>9)
        {
            carry=result[m]/10;
            result[m++]%=10;
            result[m]+=carry;
            carry=0;
        }
    }

    return pos;
}
int main()
{
    char num1[200],num2[200];
    scanf("%s",num1);
    scanf("%s",num2);
    if(num1[0]==0||num2[0]==0) printf("0");//Multiply函数有上述“判断循环结束的条件可能有纰漏”的问题，若两数中有一个为0，则循环停不下来
    else
	{
		int pos=Multiply(num1,num2);
    	for(int i=pos;i>=0;i--)  //由于pos与进位中m是同步增长的，故从pos开始而非pos-1；
        	printf("%d",result[i]);
	}
    return 0;
}

//此题之后需改进
//傻逼了，因为位数有限，上述进位根本不需要自己判断循环条件，直接让其循环400都行，反正0怎么操作都是0
//后续打印时也可以直接从400位开始，遇到第一个不为0的数就开始打印，不用再去判断pos

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define Max 400 //两个不超过200位的非负整数积不超过400位
int result[Max]={0};

void Multiply(char*s,char*t)
{
    int len1=strlen(s),len2=strlen(t);
    char*p=s+len1-1,*q=t+len2-1;//指向低位
    for(int i=0;p>=s;p--,i++)
    {
        for(int j=0;q>=t;q--,j++)
        {
            result[i+j]=result[i+j]+(p[0]-'0')*(q[0]-'0');
        }
        q=t+len2-1;//重置

    }//此时result内各数没进位,且均不超过200*81*（1.1）=17820;
    int carry=0;//保存进位

//进位
    for(int m=0;m<400;) //不用管，进位就行
    {
        if(result[m]>9)
        {
            carry=result[m]/10;
            result[m++]%=10;
            result[m]+=carry;
            carry=0;
        }
        else m++;
    }
}
int main()
{
    char num1[200],num2[200];
    scanf("%s",num1);
    scanf("%s",num2);
    if(num1[0]==0||num2[0]==0) printf("0");
    else
	{
		int k=399;
		Multiply(num1,num2);
		for(k;result[k]==0;k--);//找到第一个不为0的位置
    	for(k;k>=0;k--)
        	printf("%d",result[k]);
	}
    return 0;
}

/*任务描述
本关任务：设计一个含有年、月、日的日期结构类型，输入一个日期，计算并输出该日期是该年中的第几天。

测试说明
平台会对你编写的代码进行测试，若是与预期输出相同，则算通关。

年、月、日中间使用空格进行分隔

测试输入：2019 1 1
预期输出：
1

测试输入：2019 3 5
预期输出：
64

测试输入：2019 5 3
预期输出：
123

测试输入：2016 2 29
预期输出：
60

测试输入：2000 2 29
预期输出：
60

测试输入：2100 2 29
预期输出：
不存在这样的日期

测试输入：2019 2 29
预期输出：
不存在这样的日期

开始你的任务吧，祝你成功！*/

#include<stdio.h>
int main(void)
{
    int year,month,day;
    int sum=0;
    scanf("%d %d %d",&year,&month,&day);
    if(year%4==0&&year%100!=0||year%400==0)
    {
        if(month==2&&day>29)
        {
            printf("不存在这样的日期");
            return 0;
        }
    }
    else
    {
        if(month==2&&day>28)
        {
            printf("不存在这样的日期");
            return 0;
        }
    }
    if(month>12||month<1)
    {
        printf("不存在这样的日期");
        return 0;
    }
    if(month==1)
    {
        sum=day;
    }
    else if(month==2)
    {
        sum=31+day;
    }
    else if(month==3)
    {
        sum=59+day;
    }
    else if(month==4)
    {
        sum=90+day;
    }
    else if(month==5)
    {
        sum=120+day;
    }
    else if(month==6)
    {
        sum=151+day;
    }
    else if(month==7)
    {
        sum=181+day;
    }
    else if(month==8)
    {
        sum=212+day;
    }
    else if(month==9)
    {
        sum=243+day;
    }
    else if(month==10)
    {
        sum=273+day;
    }
    else if(month==11)
    {
        sum=304+day;
    }
    else if(month==12)
    {
        sum=334+day;
    }
    printf("%d",sum);
    return 0;
}
// 函数调度。

// 输入输出示例
// 输入：
// 13607122

// 输出：
// task1 is called!
// task3 is called!
// task6 is called!
// task0 is called!
// task7 is called!
// task1 is called!
// task2 is called!
// task2 is called!

#include<stdio.h>
#include<string.h>
void task0()
{
    printf("task0 is called!\n");
}
void task1()
{
    printf("task1 is called!\n");
}
void task2()
{
    printf("task2 is called!\n");
}
void task3()
{
    printf("task3 is called!\n");
}
void task4()
{
    printf("task4 is called!\n");
}
void task5()
{
    printf("task5 is called!\n");
}
void task6()
{
    printf("task6 is called!\n");
}
void task7()
{
    printf("task7 is called!\n");
}
int diaoyong[20];//存调用函数序号
void (*p[8])(void)={task0,task1,task2,task3,task4,task5,task6,task7};


void execute(int n)
{
    for(int i=0;i<n;i++)
        (*p[diaoyong[i]])();//依次调用
}


void scheduler(void)
{
    char c;
    int n=0;//任务数
//   while((c=getchar())!= '\n')
    while(scanf("%c", &c) == 1 && c != '\n')
    {
        diaoyong[n++]=c-'0';
    }
    execute(n);
}
int main()
{
    scheduler();
    return 0;
}

//Q:为何头歌又不过，明明dev-c++运行完全没问题
//A:因为在dev-c++中输入时会自动加上回车，而在在线编译器中不会，故在在线编译器中要用scanf("%c", &c) == 1 && c != '\n'来判断输入是否结束
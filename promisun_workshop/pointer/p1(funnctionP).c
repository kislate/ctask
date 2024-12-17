

// 实验教材P179 6.3.2节 2.程序完善和修改替换 第（2）题第①问
// 通过函数指针和菜单选择来调用库函数实现字符串操作：串复制strcpy、串连接strcat或串分解strtok。请完善该程序
// ( 函数strtok的实现和使用参见理论课教材例8.19)

// 输入输出示例
// 输入：
// 1
// the more you learn,
// the more you get.
// 2
// the more you learn,
// the more you get.
// 3
// www.educoder.net
// .
// 4

// 输出：
// the more you get.
// the more you learn,the more you get.
// www

// 通过函数指针和菜单选择来调用库函数实现字符串操作：串复制strcpy、串连接strcat或串分解strtok。
// 请使用转移表而不是switch语句重写第4关程序。（improve）

#include <stdio.h>
#include <string.h>

int main(void)
{
    char *(*p)(char*,const char*);
    char a[80], b[80], *result;
    int choice;


    while(1)
    {
        do
        {
            printf("\t\t1 copy string.\n");
            printf("\t\t2 connect string.\n");
            printf("\t\t3 Parse string.\n");
            printf("\t\t4 exit.\n");
            printf("\tinput a number (1-4) please!\n");
            scanf("%d", &choice);
        } while (choice<1||choice>4);
        

        switch(choice)
        {
            case 1: p=strcpy; break;
            case 2: p=strcat; break;
            case 3: p=strtok; break;
            case 4: goto down;
        }


        getchar();
        printf("input the first string please!\n");
        scanf("%s",a);
        printf("input the second string please!\n");
        scanf("%s",b);
        result=(*p)(a,b);
        printf("the result is %s\n", result);
    }
down:
    return 0;
}

//使用转移表
#include <stdio.h>
#include <string.h>

int main(void)
{
    char *(*p[3])(char*,const char*)={strcpy,strcat,strtok};
    char a[80], b[80], *result;
    int choice;


    while(1)
    {
        do
        {
            printf("\t\t1 copy string.\n");
            printf("\t\t2 connect string.\n");
            printf("\t\t3 Parse string.\n");
            printf("\t\t4 exit.\n");
            printf("\tinput a number (1-4) please!\n");
            scanf("%d", &choice);
        } while (choice<1||choice>4);
	
		if(choice==4) return 0;
        getchar();
        printf("input the first string please!\n");
        scanf("%s",a);
        printf("input the second string please!\n");
        scanf("%s",b);
        result=(*p[choice-1])(a,b);
        printf("the result is %s\n", result);
    }
}
 
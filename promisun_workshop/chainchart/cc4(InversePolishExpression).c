/*本关任务：
利用值栈对逆波兰表达式进行求值。逆波兰表达式从键盘输入，其中的运算符仅包含加、减、乘、除4种运算，
表达式中的数都是十进制数，用换行符结束输入。由于逆波兰表达式的长度不限，所以值栈要用后进先出链表实现。

编程要求
根据题目要求，在右侧编辑器中完成程序设计。

测试说明
平台会对你编写的代码进行测试：

测试输入：
2  1  +  3  *
预期输出：
9
解释:
该算式转化为常见的中缀算术表达式为：((2 + 1) * 3) = 9

测试输入：
4  13  5  /  +
预期输出：
6
解释: 该算式转化为常见的中缀算术表达式为：(4 + (13 / 5)) = 6

开始你的任务吧，祝你成功！*/
#include <stdio.h>
#include <stdlib.h>
struct SUAN
{
    char data;
    struct SUAN *next;
};
typedef struct SUAN suan;
void create_list(suan **headp,char *p)//headp是指向指针的指针，p是指向数组的指针，要改指针则应该传指针地址，故用**headp
{
    suan *loc_head=NULL,*s;
    while (*p)
    {
        if(*p==' ')
        {
            p++;
            continue;
        }
        s=(suan *)malloc(sizeof(suan));
        s->data=*p++;
        s->next=loc_head; //新结点指向原首结点
        loc_head=s;       //新节点成为首结点 
    }
    *headp=loc_head;
}

int main()
{
    suan *head;
    char s[1000];
    scanf("%[^\n]",s);
    create_list(&head,s);

}

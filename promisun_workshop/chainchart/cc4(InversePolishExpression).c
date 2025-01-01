/*本关任务：
利用值栈对逆波兰表达式进行求值。逆波兰表达式从键盘输入，其中的运算符仅包含加、减、乘、除4种运算，
表达式中的数都是十进制数，用换行符结束输入。由于逆波兰表达式的长度不限，所以值栈要用后进先出链表实现。————>利用栈实现更方便

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
    int num;
    struct SUAN *next;
};
typedef struct SUAN suan;
void create_list(suan **headp,char *q)//headp是指向指针的指针，p是指向数组的指针，要改指针则应该传指针地址，故用**headp
{
    suan *loc_head=NULL,*s;
    char *p=q;
    int is_negetive=0;
    while (*p)
    {
        while(*p=='-'&&*(p+1)<='0'||*p=='-'&&*(p+1)>='9'||*p=='+'||*p=='*'||*p=='/'||*p==' ')
        {
            p++;
            is_negetive=0;
        }
        s=(suan *)malloc(sizeof(suan));
        s->num=0;
        while(*p=='-'&&*(p+1)>='0'&&*(p+1)<='9')//判断是否为负数
        {
            is_negetive=1;
            p++;
        }
        while(*p>='0'&&*p<='9')
                s->num=(*p++)-'0'+s->num*10;
        if(is_negetive) s->num=-s->num;
        s->next=loc_head; //新结点指向原首结点
        loc_head=s;       //新节点成为首结点 
    }
    *headp=loc_head;
}
int suanPolish(suan*head,char*s)
{
    suan *p=head;
    if(p==NULL) return 0;
    if(p->next==NULL) return p->num;
    int num1=p->num,num2;
    p=p->next;
    num2=p->num;
    while(!p)
    {
        while(!(*s=='-'&&*(s+1)<='0'||*s=='-'&&*(s+1)>='9'||*s=='+'||*s=='*'||*s=='/'))
            s++;
        if(*s=='+'){
            num1=num1+num2;
            p=p->next;
            if(!p) num2=p->num;
        }
        if(*s=='-'){
            num1=num1-num2;
            p=p->next;
            if(!p) num2=p->num;
        }
        if(*s=='*'){
            num1=num1*num2;
            p=p->next;
            if(!p) num2=p->num;
        }
        if(*s=='/'){
            num1=num1/num2;
            p=p->next;
            if(!p) num2=p->num;
        }
    }
    return num1;
}

int main()
{
    suan *head;
    char s[1000];
    scanf("%[^\n]",s);
    create_list(&head,s);
    int result=suanPolish(head,s);
    printf("%d",result);
}

//失败失败失败，明显设计的就有问题，生硬的将运算符和数字分开，导致运算顺序只能适应于数字全在前，运算符全在后的情况。

//此题说了用值栈的方法，故采用及时进栈与出栈的方法（因为逆波兰表达式特点就是遇到运算符计算其前两个数）。其实可以不用链表，用也行
//以下为网络版本
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct {
    int data[100];
    int top;
} Stack;

void initStack(Stack* stack) {
    stack->top = -1;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

int isFull(Stack* stack) {
    return stack->top ==99;
}

void push(Stack* stack, int value) {
    if (isFull(stack)) {
        return;
    }
    stack->data[++stack->top] = value;
}

int pop(Stack* stack) {
    if (isEmpty(stack)) {
        return -1; 
    }
    return stack->data[stack->top--];
}

int evaluateRPN(char* expression) {
    Stack stack;
    initStack(&stack);
    
    char* token = strtok(expression, " ");
    
    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            push(&stack, atoi(token));
        } 
        else if (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/') {
            int b = pop(&stack);
            int a = pop(&stack);
            int result = 0;
            
            switch (token[0]) {
                case '+':
                    result = a + b;
                    break;
                case '-':
                    result = a - b;
                    break;
                case '*':
                    result = a * b;
                    break;
                case '/':
                    result = a / b;
                    break;
            }
            push(&stack, result); 
        }
        token = strtok(NULL, " ");
    }
    
    return pop(&stack);
}

int main() {
    char expression[100];
    fgets(expression,100, stdin);
    expression[strcspn(expression, "\n")] = 0;
    int result = evaluateRPN(expression);
    printf("%d\n", result);
    
    return 0;
}



//自己写的
#include <stdio.h>
#include <stdlib.h>
typedef struct Stack
{
	int data[10];//适应于十个数以内的逆波兰表达式 
	int top;
}stack;

void initStack(stack* polan)
{
	polan->top=-1;
};

void push(stack*polan,int a)
{
	polan->data[++polan->top]=a;
};

void popwithSuan(stack*polan,char c)
{
	if(c=='+')
	polan->data[--polan->top]=polan->data[polan->top]+polan->data[polan->top+1];
	if(c=='-')
	polan->data[--polan->top]=polan->data[polan->top]-polan->data[polan->top+1];
	if(c=='*')
	polan->data[--polan->top]=polan->data[polan->top]*polan->data[polan->top+1];
	if(c=='/')
	polan->data[--polan->top]=polan->data[polan->top]/polan->data[polan->top+1];
};

int SUAN(char *s)
{
	stack Polan,*polan=&Polan;
	initStack(polan);
	for(;*s!='\0';s++)
	{
		int is_negative=0,data=0,flag=0;//data录数据，flag判断是否有数 
		if(*s==' ') continue;
		if(*s=='-'&&*(s+1)>='0'&&*(s+1)<='9')//判断是否为负数
        {
            is_negative=1;
            s++;
        }
        while(*s>='0'&&*s<='9')
        {
			data=(*s++)-'0'+data*10;
			flag=1;
		}
        if(is_negative) data=-data;
        if(flag) push(polan,data);//注意，如果是数则此时*s应该是空格,否则*s就是运算符 
        else popwithSuan(polan,*s);
	}
	return Polan.data[0];
}

int main()
{
	char str[100];
	scanf("%[^\n]",str);
	printf("%d",SUAN(str));
	return 0;
}
//此方案很成功，但不知为何头歌测评答案与devc++的答案不一样，devc++的测评（包括负数）是完全正确的，但头歌的测评是完全错误的，甚至有的答案差距过大
//其实此方案并没有将多余数据清除出栈，而是采用top定位的方式进行覆盖或者回退，能够确保最终运算结果在栈底。
//（比如2  1  +  3  *，2和1相加后栈变为3 1，1就没有用了，但是没有清除，而是之后遇到3直接覆盖了1，栈变为3 3，然后3和3相乘，最终结果在栈底9，栈变为9 3）
//此题还需写参入链表的方法。。。。。。未完待续
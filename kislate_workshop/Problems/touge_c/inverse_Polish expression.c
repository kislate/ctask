/*任务描述
实验教材P207 程序设计 第（9）题
本关任务：
利用值栈对逆波兰表达式进行求值。逆波兰表达式从键盘输入，其中的运算符仅包含加、减、乘、除4种运算，表达式中的数都是十进制数，用换行符结束输入。由于逆波兰表达式的长度不限，所以值栈要用后进先出链表实现。

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
#include <string.h>

typedef struct c_node {
    int num;
    char ch;
    struct c_node *next;
    struct c_node *prev;
} C_NODE;

// 这里的四个函数都是a先出，b后出；
int add(int a, int b) {
    return a + b;
}

int minus(int a, int b) {
    return b - a;
}

int times(int a, int b) {
    return a * b;
}

int divide(int a, int b) {
    return b / a;
}

void createLinkList(C_NODE **head, C_NODE **tail, char *s) {
    C_NODE *p_new;
    C_NODE *p_mov = *head;
    while (*s != '\0') {
        p_new = (C_NODE *)malloc(sizeof(C_NODE));
        p_new->num = 0;
        p_new->ch = 0;
        while (*s == ' ') {
            s++;
        }

        if (*s >= '0' && *s <= '9') {
            while (*s >= '0' && *s <= '9') {
                p_new->num = p_new->num * 10 + (*s) - '0';
                s++;
            }
            if(*s == '-')
            {
                p_new->num = -p_new->num;
                s++;
            }
        } 
        else {
            p_new->ch = *s;
            s++;
        }

        p_new->next = NULL;
        p_new->prev = NULL; // 防止野指针；
        if (*head == NULL) {
            *head = p_new;
        } else {
            p_new->prev = p_mov;
            p_mov->next = p_new;
        }
        p_mov = p_new;
        s++;
    }
    *tail = p_new;
}

int BolanLinkList(C_NODE **tail) {
    if ((*tail)->prev == NULL) {
        return (*tail)->num;
    }

    if ((*tail)->num != 0) {
        int num = (*tail)->num;
        *tail = (*tail)->prev;
        return num;
    }

    if ((*tail)->ch == '+') {
        *tail = (*tail)->prev;
        int num1 = BolanLinkList(tail);
        int num2 = BolanLinkList(tail);
        return add(num1, num2);
    }

    if ((*tail)->ch == '-') {
        *tail = (*tail)->prev;
        int num1 = BolanLinkList(tail);
        int num2 = BolanLinkList(tail);
        return minus(num1, num2);
    }

    if ((*tail)->ch == '*') {
        *tail = (*tail)->prev;
        int num1 = BolanLinkList(tail);
        int num2 = BolanLinkList(tail);
        return times(num1, num2);
    }

    if ((*tail)->ch == '/') {
        *tail = (*tail)->prev;
        int num1 = BolanLinkList(tail);
        int num2 = BolanLinkList(tail);
        return divide(num1, num2);
    }

    return 0; 
}

int main(void) {
    char s[1000];
    fgets(s, sizeof(s), stdin); 
    s[strcspn(s, "\n")] = '\0'; 
    C_NODE *head = NULL, *tail = NULL;
    createLinkList(&head, &tail, s);
    int ret = BolanLinkList(&tail);
    printf("%d", ret);
    return 0;
}





//靠，这个东西读字符串的时候是从前往后读的啊；
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct c_node {
    int num;
    char ch;
    struct c_node *next;
    struct c_node *prev;
} C_NODE;

// 这里的四个函数都是a先出，b后出；
int add(int a, int b) {
    return a + b;
}

int minus(int a, int b) {
    return b - a;
}

int times(int a, int b) {
    return a * b;
}

int divide(int a, int b) {
    return b / a;
}

void createLinkList(C_NODE **head, C_NODE **tail, char *s) {
    C_NODE *p_new;
    C_NODE *p_mov = *head;
    while (*s != '\0') {
        p_new = (C_NODE *)malloc(sizeof(C_NODE));
        p_new->num = 0;
        p_new->ch = 0;
        int is_negative = 0;

        while (*s == ' ') {
            s++;
        }

        if (*s == '-' && (*(s + 1) >= '0' && *(s + 1) <= '9')) {
            is_negative = 1;
            s++;
        }

        if (*s >= '0' && *s <= '9') {
            while (*s >= '0' && *s <= '9') {
                p_new->num = p_new->num * 10 + (*s) - '0';
                s++;
            }
            if (is_negative) {
                p_new->num = -p_new->num;
            }
        } else {
            p_new->ch = *s;
            s++;
        }

        p_new->next = NULL;
        p_new->prev = NULL; // 防止野指针；
        if (*head == NULL) {
            *head = p_new;
        } else {
            p_new->prev = p_mov;
            p_mov->next = p_new;
        }
        p_mov = p_new;
        s++;
    }
    *tail = p_new;
}

int BolanLinkList(C_NODE **tail) {
    if ((*tail)->prev == NULL) {
        return (*tail)->num;
    }

    if ((*tail)->num != 0) {
        int num = (*tail)->num;
        *tail = (*tail)->prev;
        return num;
    }

    if ((*tail)->ch == '+') {
        *tail = (*tail)->prev;
        int num1 = BolanLinkList(tail);
        int num2 = BolanLinkList(tail);
        return add(num1, num2);
    }

    if ((*tail)->ch == '-') {
        *tail = (*tail)->prev;
        int num1 = BolanLinkList(tail);
        int num2 = BolanLinkList(tail);
        return minus(num1, num2);
    }

    if ((*tail)->ch == '*') {
        *tail = (*tail)->prev;
        int num1 = BolanLinkList(tail);
        int num2 = BolanLinkList(tail);
        return times(num1, num2);
    }

    if ((*tail)->ch == '/') {
        *tail = (*tail)->prev;
        int num1 = BolanLinkList(tail);
        int num2 = BolanLinkList(tail);
        return divide(num1, num2);
    }

    return 0; // 默认返回值，防止编译器警告
}

int main(void) {
    char s[1000];
    fgets(s, sizeof(s), stdin); // 使用 fgets 读取包含空格的整行输入
    s[strcspn(s, "\n")] = '\0'; // 去掉换行符
    C_NODE *head = NULL, *tail = NULL;
    createLinkList(&head, &tail, s);
    int ret = BolanLinkList(&tail);
    printf("%d\n", ret);
    return 0;
}













































































































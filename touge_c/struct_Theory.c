/*
任务描述
本关任务：编程实现
（1）用一个单向链表接收一个长字符串，且每个节点接收一个字符，遍历输出链表中的所有字符，并将字符串无冗余地存放到一个动态存储分配的的字符数组中，并且输出该字符串。（本题暂不考虑空字符串情况）(结尾以回车结束)
（2）再输入一个字符，如果该字符已在链表中，则删除该结点，否则在输入字符和结点的数据域字符差值最小的结点后面插入包含该字符的结点，输出最后的字符串。

要求：采用模块化设计方法，将创建链表、遍历链表、删除结点、插入结点等功能用函数实现。

测试说明
平台会对你编写的代码进行测试，若是与预期输出相同，则算通关。

测试输入：
qwertyuiopasdfghjkl
i
预期输出：
q w e r t y u i o p a s d f g h j k l
qwertyuiopasdfghjkl
qwertyuopasdfghjkl

测试输入：
qwertyuiopasdfghjkl
q
预期输出：
q w e r t y u i o p a s d f g h j k l
qwertyuiopasdfghjkl
wertyuiopasdfghjkl

测试输入：
qwer1234?@%
5
预期输出：
q w e r 1 2 3 4 ? @ %
qwer1234?@%
qwer12345?@%

开始你的任务吧，祝你成功！*/

//这题真尼玛逆天
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node
{
    char data;
    struct node *next;
}Node;
void createList(Node **head,Node *p_new);
char printList(Node *head,char ch);
void insertNode(Node **head,char ch);
int deleteNode(Node **head,char ch);
int main(void)
{
    Node *head = NULL;
    Node *p_new = NULL;
    char ch;
    char str[100];
    while((ch=getchar())!='\n')
    {
        p_new = (Node*)malloc(sizeof(Node));
        if (p_new == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }
        
        p_new->data = ch;
        createList(&head,p_new);
    }
    ch = getchar();
    char inser_ch;
    inser_ch=printList(head,ch);
    int i = 0;
    Node *p = head;
    while(p!=NULL)
    {
        str[i++] = p->data;
        p = p->next;
    }

    str[i] = '\0';
    printf("%s\n",str);
    if(deleteNode(&head,ch))
    {
        insertNode(&head,inser_ch);
    }

    i = 0;
    p = head;
    while(p!=NULL)
    {
        str[i++] = p->data;
        p = p->next;
    }
    str[i] = '\0';
    printf("%s\n",str);
    return 0;
}

void createList(Node **head,Node *p_new)
{
    Node *p_mov = *head;
    if(*head == NULL)
    {
        *head = p_new;
        p_new->next = NULL;
    }
    else
    {
        while(p_mov->next!=NULL)
        {
            p_mov=p_mov->next;
        }
        p_mov->next=p_new;
        p_new->next=NULL;
    }
    return;
}
char printList(Node *head,char ch)
{
    int min=200;
    char ret='\0';
    Node *p_mov=head;
    while(p_mov!=NULL)
    {
        printf("%c ",p_mov->data);
        if(   ((p_mov->data-ch) >0?(p_mov->data-ch):(-(p_mov->data-ch)))<min        )
        {
            min= ((p_mov->data-ch) >0?(p_mov->data-ch):(-(p_mov->data-ch)));
            ret=p_mov->data;
        }
        p_mov = p_mov->next;
    }
    putchar(10);
    return ret;
}

int deleteNode(Node **head,char ch)
{
    Node *pb,*pf;
    pb = pf = *head;
    if(pb==NULL)
    {
        printf("链表为空，不需要删掉");
        return 0;
    }
    while(pb!=NULL && pb->data!=ch)
    {
       pf = pb;
       pb = pb->next;
    }
    if(pb != NULL&&pb->data==ch)
    {
        if(pb==*head)
        {
            *head = pb->next;
        }
        else
        {
            pf->next=pb->next;
        }

        free(pb);
        pb = NULL;
        return 1;
    }
    else{
        return 0;
    }
}
void insertNode(Node **head,char ch)
{
    Node *p_new;
    p_new = (Node*)malloc(sizeof(Node));
    p_new->data=ch;
    p_new->next=NULL;
    Node *pf,*pb;
    pf=pb=*head;
    if(*head==NULL)
    {
        *head=p_new;
        return;
    }
    while(pb != NULL && pb->data!=ch)
    {
        pf=pb;
        pb=pb->next;
    }

    p_new->next=pb->next;
    pb->next=p_new;
    return;
}


//下面都是copilot生成的代码，是对的，而我的那个是错的，我真是服了

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <limits.h>
// #include <ctype.h>

// // 定义链表节点结构体
// typedef struct node {
//     char data;
//     struct node *next;
// } Node;

// // 函数声明
// void createList(Node **head, Node *p_new);
// void printList(Node *head);
// char* buildString(Node *head);
// int deleteNode(Node **head, char ch);
// Node* findClosestNode(Node *head, char ch);
// void insertAfter(Node *target, char ch);
// void freeList(Node *head);

// int main(void)
// {
//     Node *head = NULL;
//     Node *p_new = NULL;
//     char ch;
//     char *str = NULL;

//     // 输入字符串，直到回车
//     while((ch = getchar()) != '\n' && ch != EOF)
//     {
//         p_new = (Node*)malloc(sizeof(Node));
//         if (p_new == NULL) {
//             fprintf(stderr, "内存分配失败\n");
//             freeList(head);
//             return 1;
//         }
//         p_new->data = ch;
//         p_new->next = NULL;
//         createList(&head, p_new);
//     }

//     // 遍历输出链表中的所有字符，带空格
//     printList(head);

//     // 将链表内容存放到动态分配的字符数组中
//     str = buildString(head);
//     if(str == NULL)
//     {
//         fprintf(stderr, "字符串构建失败\n");
//         freeList(head);
//         return 1;
//     }
//     printf("%s\n", str);

//     // 输入要查找或插入的字符
//     ch = getchar();
//     if(ch == '\n' || ch == EOF)
//     {
//         // 如果读取到的是换行符或文件结束符，说明没有输入字符
//         fprintf(stderr, "没有输入要处理的字符\n");
//         free(str);
//         freeList(head);
//         return 1;
//     }

//     // 尝试删除该字符
//     if(deleteNode(&head, ch))
//     {
//         // 删除成功，不需要插入
//     }
//     else
//     {
//         // 删除失败，说明字符不存在，需插入
//         Node *closest = findClosestNode(head, ch);
//         if(closest != NULL)
//         {
//             insertAfter(closest, ch);
//         }
//         else
//         {
//             // 如果链表为空，直接插入
//             p_new = (Node*)malloc(sizeof(Node));
//             if (p_new == NULL) {
//                 fprintf(stderr, "内存分配失败\n");
//                 free(str);
//                 freeList(head);
//                 return 1;
//             }
//             p_new->data = ch;
//             p_new->next = NULL;
//             head = p_new;
//         }
//     }

//     // 重新构建字符串并输出
//     free(str); // 释放之前的字符串
//     str = buildString(head);
//     if(str == NULL)
//     {
//         fprintf(stderr, "字符串构建失败\n");
//         freeList(head);
//         return 1;
//     }
//     printf("%s\n", str);

//     // 释放内存
//     free(str);
//     freeList(head);

//     return 0;
// }

// // 创建链表，添加节点到末尾
// void createList(Node **head, Node *p_new)
// {
//     if(*head == NULL)
//     {
//         *head = p_new;
//     }
//     else
//     {
//         Node *p_mov = *head;
//         while(p_mov->next != NULL)
//         {
//             p_mov = p_mov->next;
//         }
//         p_mov->next = p_new;
//     }
// }

// // 打印链表中的所有字符，带空格
// void printList(Node *head)
// {
//     Node *p_mov = head;
//     while(p_mov != NULL)
//     {
//         printf("%c ", p_mov->data);
//         p_mov = p_mov->next;
//     }
//     putchar('\n');
// }

// // 将链表内容存放到动态分配的字符数组中
// char* buildString(Node *head)
// {
//     // 先计算链表长度
//     int length = 0;
//     Node *p_mov = head;
//     while(p_mov != NULL)
//     {
//         length++;
//         p_mov = p_mov->next;
//     }

//     // 动态分配字符数组
//     char *str = (char*)malloc((length + 1) * sizeof(char));
//     if(str == NULL)
//     {
//         return NULL;
//     }

//     // 复制字符到数组中
//     p_mov = head;
//     for(int i = 0; i < length; i++)
//     {
//         str[i] = p_mov->data;
//         p_mov = p_mov->next;
//     }
//     str[length] = '\0';

//     return str;
// }

// // 删除链表中第一个匹配的字符节点
// int deleteNode(Node **head, char ch)
// {
//     if(head == NULL || *head == NULL)
//     {
//         return 0;
//     }

//     Node *current = *head;
//     Node *previous = NULL;

//     // 查找要删除的节点
//     while(current != NULL && current->data != ch)
//     {
//         previous = current;
//         current = current->next;
//     }

//     if(current != NULL && current->data == ch)
//     {
//         if(current == *head)
//         {
//             // 删除头节点
//             *head = current->next;
//         }
//         else
//         {
//             // 删除中间或尾节点
//             previous->next = current->next;
//         }
//         free(current);
//         return 1;
//     }
//     else
//     {
//         // 未找到节点
//         return 0;
//     }
// }

// // 查找与输入字符差值最小的节点
// Node* findClosestNode(Node *head, char ch)
// {
//     if(head == NULL)
//     {
//         return NULL;
//     }

//     Node *closest = head;
//     int min_diff = abs(head->data - ch);
//     Node *p_mov = head->next;

//     while(p_mov != NULL)
//     {
//         int diff = abs(p_mov->data - ch);
//         if(diff < min_diff)
//         {
//             min_diff = diff;
//             closest = p_mov;
//         }
//         p_mov = p_mov->next;
//     }

//     return closest;
// }

// // 在指定节点后插入新节点
// void insertAfter(Node *target, char ch)
// {
//     if(target == NULL)
//     {
//         return;
//     }

//     Node *p_new = (Node*)malloc(sizeof(Node));
//     if(p_new == NULL)
//     {
//         fprintf(stderr, "内存分配失败\n");
//         return;
//     }
//     p_new->data = ch;
//     p_new->next = target->next;
//     target->next = p_new;
// }

// // 释放链表内存
// void freeList(Node *head)
// {
//     Node *temp;
//     while(head != NULL)
//     {
//         temp = head;
//         head = head->next;
//         free(temp);
//     }
// }
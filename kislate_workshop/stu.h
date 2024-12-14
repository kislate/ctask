/*任务描述
实验教材P207 程序设计 第（4）题
本关任务：
回文字符串是正读和反读都相同的字符串，例如“abba”和“abcba”是回文字符串。设计程序判断输入的任意长度的字符串是否为回文字符串。
提示：由于要求字符串长度任意，所以用单链表存储字符串，即判断一个单链表是否为回文链表。

编程要求
根据题目要求，在右侧编辑器中两个函数的算法设计。

void createLinkList(C_NODE **headp, char s[]) 根据字符串s构造单链表，得到一个以单链表表示的字符串，单链表结点定义见右侧编辑器。
void judgePalindrome(C_NODE *head) 判断以head为头指针的单链表表示的字符串是否为回文，是则显示true，否则显示false。
测试说明
平台会对你编写的代码进行测试：

测试输入1：
ababa
预期输出1：
true

测试输入2：
race a car
预期输出2：
false

测试输入2：
happycoding!
预期输出2：
false

开始你的任务吧，祝你成功！*/


void createLinkList(C_NODE **headp, char s[]) 
{
/************************************* BEGIN *******************************************/
    C_NODE *p=*headp;
    char *pc= s;
    if(*headp==NULL)
    {
        *headp = (C_NODE *)malloc(sizeof(C_NODE));//这里不应该直接给这个headp分配空间
        (*headp)->data = *pc++;
        (*headp)->next = NULL;
    }
    while(p->next != NULL)
    {
        p->next;//这里的p没有更新，此时的headp已经改变了
    }
    while(s!='\0')//这里应该是*pc!='\0'
    {
        C_NODE *p_new = (C_NODE*)malloc(sizeof(C_NODE));
        p_new->data = *s++;//这里应该是*pc++
        p_new->next = NULL;
        p->next = p_new;
        p = p->next;
    }
/************************************* BEGIN *******************************************/
}//应该直接看下面的代码

void createLinkList(C_NODE **headp, char s[]) 
{
/************************************* BEGIN *******************************************/
    C_NODE *p = NULL;
    while (*s != '\0') 
    {
        C_NODE *p_new = (C_NODE *)malloc(sizeof(C_NODE));
        p_new->data = *s++;
        p_new->next = NULL;
        if (*headp == NULL) 
        {
            *headp = p_new;
            p = p_new; // 初始化 p
        } 
        else 
        {
            p->next = p_new;
            p = p_new; // 更新 p
        }
    }
/************************************* BEGIN *******************************************/
}

void creatLinkList(C_NODE **headp,char s[])
{
    C_NODE *p = NULL;
    while(*s != '\0')
    {
        C_NODE *p_new = (C_NODE *)malloc(sizeof(C_NODE));
        p_new = *s++;
        p_new->next = NULL;
        if(*headp == NULL)
        {
            *headp = p_new;
            p = p_new;
        }
        else{
            p->next = p_new;
            p = p_new;
        }
    }
}

void judgePalindrome(C_NODE *head)
{
    C_NODE *start,*tail;
    if(head->next == NULL)
    {
        printf("true\n");
        return;
    }
    int cnt=0;
    while(tail->next != NULL)
    {
        tail = tail->next;
        cnt ++;
    }
    C_NODE *pf;
    pf= start;
    int commit = 0;
    char str[100];
    char *q = str;
    while(commit < cnt/2)
    {
        *q++ = start->data;
        pf = start;
        start = start->next;
        free(pf);
    }
    if(cnt%2)
    {
        start = start->next;
    }
    q = str;
    while(start != NULL)
    {
        if(start != *q++)
        {
            printf("false");
            return;
        }
        start = start->next;
    }
    printf("true\n");

}
/************************************* BEGIN *******************************************/

void judgePalindrome(C_NODE *head)
{
    C_NODE *start, *tail;
    if (head == NULL || head->next == NULL) // 检查空链表或单节点链表
    {
        printf("The list is a palindrome.\n");
        return;
    }

    // 找到链表的尾节点
    tail = head;
    while (tail->next != NULL)
    {
        tail = tail->next;
    }

    // 检查是否为回文
    while (head != tail && head->next != tail)
    {
        if (head->data != tail->data)
        {
            printf("The list is not a palindrome.\n");
            return;
        }
        head = head->next;

        // 找到新的尾节点
        start = head;
        while (start->next != tail)
        {
            start = start->next;
        }
        tail = start;
    }

    printf("The list is a palindrome.\n");
}

void judgePalindrome(C_NODE *head)
{
    C_NODE *start , *tail;
    if(head->next ==NULL ||head == NULL)
    {
        printf("true\n");
        return;
    }
    tail = head;
    while(tail->next != NULL)
    {
        tail = tail->next;
    }
    while(head != tail &&head->next != tail)
    {
        if(head->data != tail ->data)
        {
            printf("false\n");
            return;
        }
        head = head->next;
        start = head;
        while(start->next !=tail)
        {
            start = start->next;
        }
        tail = start;
    }
}

void judgePalindrome(C_NODE *head)
{
    C_NODE *start,*tail;
    if(head==NULL ||head->next == NULL)
    {
        printf("true\n");
        return;
    }
    tail = head;
    while(tail->next != NULL)
    {
        tail = tail->next;
    }
    while(head != tail &&head->next != tail)
    {
        if(head->data != tail->data)
        {
            printf("false\n");
            return;
        }
        start = head;
        while(start->next != tail)
        {
            start = start->next;
        }
        tail =start;
    }
    
}
/*
小 S 与 NLP（nlp）
【题目描述】
小 S 是一位世界记录员，她的职责是将来自不同异世界的文字材料整理归档。
虽然异世界的文明不知道为何都是用日语交流，但是他们的文字各异。所以处理这
些材料并非易事。
幸好小 S 是一位 NLP（自然语言处理）高手，通过机器学习，她的模型帮她轻松
地把所有文本翻译成了英文。
但是小 S 发现，她的语言模型不能很好的处理不同进制数值的转换，所以她只好进
行人脑 NLP，手动完成异世界数字文本的替换工作。
幸好，小S 有一份巨大的字典，其中包含n 个异世界数字代表的数值。她只需要单
纯的依此对翻译后的英文文本进行简单替换即可。
不过由于小 S 正在用电脑玩肉鸽游戏 tarjan lusa，无法使用，所以这项任务就被丢
给了你。
为了方便本世界的计算机处理，需要进行替换的异世界数字都被替换成了小写英
文字符串，并处于 {} 之间。简单的说，你需要把给出的英文文本里每一句话中全部的
{异世界数字} 替换为变量的值并输出。同时小 S 保证，给你的每句话都满足仅由大小
写英文字母、空格、半角逗号、半角句号和 {、} 组成。同时每句话由在 {} 之间的，必
然为字典中 N 个异世界数字中的一个。
例如，有 a = 20, b = 10，对于句子 Kitsuki achieved a {b} game winning
streak on advanced difficulty of {a}.，替换后将得到Kitsuki achieved a
10 game winning streak on advanced difficulty of 20.。
【输入格式】
输入共 n + m + 1 行。
输入的第一行为两个整数 n, m。
接下来 n 行，每行一个小写英文字符串、一个整数，分别代表异世界数字和其代表
的数值。
接下来 m 行，每行一个需要进行替换的句子。
【输出格式】
输出 m 行，每行一个标注好的句子。
【样例 1 输入】
1 4 2
2 shinki 1
3 a 3
4 tarjanlusa 4
5 d 5
6 We have {a} apples.
7 We {d}onot have pencils.
【样例 1 输出】
1 We have 3 apples.
2 We 5onot have pencils.
【子任务】
对于 100% 的测试数据，1 ≤n ≤5000，1 ≤m ≤20。保证 {} 成对合法出现，需要
替换的句子长度不超过 5 ×104。异世界数字为长度不超过 20 的英文小写字母串，且对
应的数值在 int 范围内。每句话由大小写英文字母、空格、半角逗号、半角句号和 {、}
组成。
【提示】
string 类型是 C++ 提供的有力类型，它封装了很多常用的字符串成员函数。
cin/cout 是 C++ 风格的输入方式，它在读取字符串时尤其好用。
本题使用字符数组同样方便，但在后面的题目中，你可以尝试学习并使用上面提示
的内容，并选择自己喜欢的那个。
我们计划为你提供 string 类型的学习材料，有关内容正在编写中。*/
// #include<stdio.h>
// #include<stdlib.h>
// #include<string.h>
// int main(void)
// {
//     int n,m;
//     scanf("%d%d",&n,&m);
//     char **str = (char**)malloc(sizeof(char*)*n);
//     int *num = (int *)malloc(sizeof(int)*n);
//     if(str == NULL || num == NULL)
//     {
//         fprintf(stderr,"\"**str or *num\" Memory allocation failed\n");
//         return 1;
//     }
//     for(int i = 0; i < n ; i++)
//     {
//         str[i] = (char *)malloc(sizeof(char)*21);
//         if(str[i] == NULL)
//         {
//             fprintf(stderr,"\"*str\" Memory allocation failed\n");
//             return 1;
//         }
//         scanf("%s%d",str[i],num + i);
//     }
//     while(getchar() != '\n');
//     for(int i = 0 ; i < m ; i++)
//     {
//         char *sentence = (char *)malloc(sizeof(char)*50001);
//         char *start = sentence;
//         if(sentence == NULL)
//         {
//             fprintf(stderr,"\"sentence\" Memory allocation failed\n");
//             return 1;
//         }
//         scanf("%[^\n]",sentence);
//         for(int j = 0 ; j < n ; j++)
//         {
//             while(strstr(start,str[j]) != NULL)
//             {
//                 char *p = strstr(start,str[j]);
//                 int len = strlen(str[j]);
//                 char *q = p + len;
//                 if(*(p - 1) == '{' && *q == '}')
//                 {
//                     p--;
//                     q++;
//                     *p = '\0';
//                     printf("%s%d",start,num[j]);
//                 }
//                 start = q;
//             }
//         }
//         printf("%s",start);
//     }
//     for(int i = 0 ; i < n ; i++)
//     {
//         free(str[i]);
//     }
//     free(str);
//     free(num);
//     return 0;
// }//good

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 21
#define MAX_SENTENCE_LEN 50001

void free_memory(char **str, int n, int *num) {
    for (int i = 0; i < n; i++) {
        free(str[i]);
    }
    free(str);
    free(num);
}

int main(void) {
    int n, m;
    scanf("%d%d", &n, &m);

    char **str = (char **)malloc(sizeof(char *) * n);
    int *num = (int *)malloc(sizeof(int) * n);
    if (str == NULL || num == NULL) {
        fprintf(stderr, "\"**str or *num\" Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        str[i] = (char *)malloc(sizeof(char) * MAX_STR_LEN);
        if (str[i] == NULL) {
            fprintf(stderr, "\"*str\" Memory allocation failed\n");
            free_memory(str, i, num);
            return 1;
        }
        scanf("%s%d", str[i], &num[i]);
    }

    while (getchar() != '\n');

    for (int i = 0; i < m; i++) {
        char *sentence = (char *)malloc(sizeof(char) * MAX_SENTENCE_LEN);
        if (sentence == NULL) {
            fprintf(stderr, "\"sentence\" Memory allocation failed\n");
            free_memory(str, n, num);
            return 1;
        }

        fgets(sentence, MAX_SENTENCE_LEN, stdin);
        char *start = sentence;
        char *output = (char *)malloc(sizeof(char) * MAX_SENTENCE_LEN);
        if (output == NULL) {
            fprintf(stderr, "\"output\" Memory allocation failed\n");
            free(sentence);
            free_memory(str, n, num);
            return 1;
        }
        output[0] = '\0';

        while (*start) {
            char *p = strchr(start, '{');
            if (p == NULL) {
                strcat(output, start);
                break;
            }//先找左边
            strncat(output, start, p - start);//先把左边加进去
            char *q = strchr(p, '}');
            if (q == NULL) {
                strcat(output, p);
                break;
            }//再找右边，两边逻辑一样，没找到都会把整段加进去

            //找到了
            *q = '\0';
            for (int j = 0; j < n; j++) {
                if (strcmp(p + 1, str[j]) == 0) {
                    char num_str[12];
                    sprintf(num_str, "%d", num[j]);//获取数字字符串
                    strcat(output, num_str);
                    break;
                }
            }
            start = q + 1;
        }

        printf("%s", output);
        free(sentence);
        free(output);
    }

    free_memory(str, n, num);
    return 0;
}//goods



// //另外一种查找方法，这个过不了
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #define MAX_STR_LEN 21
// #define MAX_SENTENCE_LEN 50001

// void free_memory(char **str, int n, int *num) {
//     for (int i = 0; i < n; i++) {
//         free(str[i]);
//     }
//     free(str);
//     free(num);
// }

// int main(void) {
//     int n, m;
//     scanf("%d%d", &n, &m);

//     char **str = (char **)malloc(sizeof(char *) * n);
//     int *num = (int *)malloc(sizeof(int) * n);
//     if (str == NULL || num == NULL) {
//         fprintf(stderr, "\"**str or *num\" Memory allocation failed\n");
//         return 1;
//     }

//     for (int i = 0; i < n; i++) {
//         str[i] = (char *)malloc(sizeof(char) * MAX_STR_LEN);
//         if (str[i] == NULL) {
//             fprintf(stderr, "\"*str\" Memory allocation failed\n");
//             free_memory(str, i, num);
//             return 1;
//         }
//         scanf("%s%d", str[i], &num[i]);
//     }

//     while (getchar() != '\n');

//     for (int i = 0; i < m; i++) {
//         char *sentence = (char *)malloc(sizeof(char) * MAX_SENTENCE_LEN);
//         if (sentence == NULL) {
//             fprintf(stderr, "\"sentence\" Memory allocation failed\n");
//             free_memory(str, n, num);
//             return 1;
//         }

//         fgets(sentence, MAX_SENTENCE_LEN, stdin);
//         char *output = (char *)malloc(sizeof(char) * MAX_SENTENCE_LEN);
//         if (output == NULL) {
//             fprintf(stderr, "\"output\" Memory allocation failed\n");
//             free(sentence);
//             free_memory(str, n, num);
//             return 1;
//         }
//         output[0] = '\0';

//         for (int j = 0; j < n; j++) {
//             char *start = sentence;
//             while ((start = strstr(start, str[j])) != NULL) {
//                 char *p = start;
//                 int len = strlen(str[j]);
//                 char *q = p + len;
//                 if (*(p - 1) == '{' && *q == '}') {
//                     p--;
//                     q++;
//                     *p = '\0';
//                     strcat(output, sentence);
//                     char num_str[12];
//                     sprintf(num_str, "%d", num[j]);
//                     strcat(output, num_str);
//                     start = q;
//                     strcpy(sentence, start);
//                     start = sentence;
//                 } else {
//                     start++;
//                 }
//             }
//         }
//         strcat(output, sentence);
//         printf("%s", output);
//         free(sentence);
//         free(output);
//     }

//     free_memory(str, n, num);
//     return 0;
// }
/*
【题目描述】
小 S 是一名 MMORPG 玩家，她经常玩一款名为“狒狒食柿”的游戏。
（如果你不知道什么是 MMORPG，你可以将其简单理解为 Many Men Online
Role Playing as Girls 的缩写。）
在狒狒食柿中，有一个叫做潜水艇的每日玩法，简单来说，你有一个海图，由大量
互相连接的节点组成，每个节点用一个字符串表示名字，一开始你只发现了一个节点，
每次派遣潜艇探索完一个节点以后，与之相连的节点有可能会被发现，从而允许你探索
更深的节点。该玩法的目的是探索尽可能多的节点，因此我们每天会且仅会向所有未探
索过的节点，或是存在相连节点未被发现的节点派遣潜艇。
潜水艇是一个每天都要处理的日常玩法，但是遗憾的是，小 S 打了一晚上高难度副
本 P10S 变成脑瘫了。所以她只能把这个任务交给你来完成。
不过好心的小 S 已经帮你处理好了一部分任务。具体而言，她会告诉你三组节点信
息：
• 昨天派遣潜艇的节点（即所有可能发现新节点的节点）
• 今天收回潜艇后，哪些节点的所有相连节点已被发现。
• 新发现了哪些节点
最后，你要给出所有今天应该探索的节点的列表，按字典序顺序输出。
【输入格式】
第一行有三个整数，依次表示昨天派遣潜艇的节点数量 n，所有相连节点已被发现
的节点数量 m，和新发现的节点数量 k。
接下来 n 行，每行一个字符串，表示一个昨天派遣潜艇的节点名字。
接下来 m 行，每行一个字符串，表示一个所有相连节点已被发现的节点名字。
接下来 k 行，每行一个字符串，表示一个新发现的节点名字。
【输出格式】
输出若干行，每行一个字符串。
按字典序从小到大的顺序输出今天应该探索的节点的名字。
【样例 1 输入】
 5 4 1
 PureWhiteShallowBeach
 DrowningSea1
 DrowningSea2
 MatteBasin
 DrowningSea3
 PureWhiteShallowBeach
 DrowningSea1
 DrowningSea2
 MatteBasin
 LimilalaTrench
【样例 1 输出】
DrowningSea3
LimilalaTrench
【子任务】
对全部的测试点，保证：- 1 ≤n ≤105 - 0 ≤m ≤n - 0 ≤k ≤105 - 除样例外，输入
字符串的长度不超过 10。- 输入字符串仅含有大小写字母和数字。- 昨天派遣潜艇的节
点名字。- 所有相连节点已被发现的节点名字互不相同，且均是昨天派遣潜艇的节点名
字。- 新发现的节点名字互不相同，且均不是昨天派遣潜艇的节点名字。*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int cmp(const void *a, const void *b)
{
    return strcmp((char *)a, (char *)b);
}
int main()
{
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    char **yesterday = (char **)malloc(n * sizeof(char *));
    char **today = (char **)malloc(m * sizeof(char *));
    char **new = (char **)malloc(k * sizeof(char *));
    for (int i = 0; i < n; i++)
    {
        yesterday[i] = (char *)malloc(11 * sizeof(char));
        scanf("%s", yesterday[i]);
    }
    for (int i = 0; i < m; i++)
    {
        today[i] = (char *)malloc(11 * sizeof(char));
        scanf("%s", today[i]);
    }
    for (int i = 0; i < k; i++)
    {
        new[i] = (char *)malloc(11 * sizeof(char));
        scanf("%s", new[i]);
    }
    qsort(new, k, sizeof(char *), cmp);
    for (int i = 0; i < k; i++)
    {
        printf("%s\n", new[i]);
    }
    return 0;
}
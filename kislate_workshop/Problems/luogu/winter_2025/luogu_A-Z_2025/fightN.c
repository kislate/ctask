/*
bngg 与 hmgg 的决斗（fight）
【题目描述】
bngg 和 hmgg 在战斗。
两人一共开辟了 n 个战场，战场排列成一条线段，依次编号为 1 ∼n，相邻编号的
战场之间相隔 1 厘米，即所有战场为长度为 n −1 厘米的线段。i 号战场现在有 ci 名士
兵在战斗。
bngg 的大本营在 1 号战场左侧，hmgg 的大本营在 n 号战场右侧，他们的势力范
围以 m 号战场分界，m 号战场左侧 bngg 占优，m 号战场右侧 hmgg 占优，而 m 号战
场是两人正在争夺的战场，没有人占优。
一个战场的士气为该战场的士兵数 ×该战场到 m 号战场的距离，一方的士气为自
己占优战场士气之和。
bngg 奇袭了 hmgg，将 s1 名士兵派往了 p1 号战场。如果双方士气差距太大，会导
致 hmgg 或者 bngg 红温。hmgg 还有 s2 名士兵可供调动，请你确定一个战场 p2，使得
hmgg 将全部 s2 名士兵派遣往战场 p2，两人士气差距尽可能小。
【输入格式】
输入共三行。
输入的第一行为一个正整数 n。
接下来一行包含 n 个正整数，第 i 个为 ci。
接下来一行包含四个正整数，分别代表 m, p1, s1, s2。
【输出格式】
输出一行一个整数 p2，若存在多个答案，输出编号最小的那个。
【样例 1 输入】
1  6
2  2 3 2 3 2 3
3  4 6 5 2
【样例 1 输出】
1  2
【样例 2 输入】
1  6
2  1 1 1 1 1 16
3  5 4 1 1
【样例 2 输出】
1  1
【子任务】
数据保证：1 ≤n ≤105，1 ≤s1, s2 ≤109，1 < m < n，1 ≤p1 ≤n。
【hints】
请考虑不同类型可以表示的数据范围，并选择合适的那个。
abs 函数是求绝对值函数。请注意，C 语言中 abs 函数只能接受 int 类型参数，若
你传入 long long 类型参数，将发生隐式类型转换，存在溢出的可能性。
你可以选择使用 llabs 函数，这个函数将接受 long long 类型的参数。你也可以直接
选用 C++ 语言提交，C++ 完全向下兼容 C 语言。C++ 的 abs 函数经过函数重载，可
以接受多种数据类型。
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(void) {
    long long n;
    scanf("%lld", &n);
    long long *c = (long long *)malloc(sizeof(long long) * (n + 1)); // this arr index from 1;
    if (c == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return -1;
    }
    for (long long i = 1; i <= n; i++) {
        scanf("%lld", c + i);
    }
    long long m, p1, s1, s2;
    scanf("%lld%lld%lld%lld", &m, &p1, &s1, &s2);
    *(c + p1) += s1;

    long long bngg = 0, hmgg = 0;
    for (long long i = 1; i <= n; i++) {
        if (i < m) {
            bngg += c[i] * (m - i);
        } else if (i > m) {
            hmgg += c[i] * (i - m);
        }
    }

    long long p2 = m;
    long long min = llabs(bngg - hmgg);
    long long flag = 0;
    if (bngg > hmgg)
        flag = 1;
    long long start = flag ? m + 1 : 1;
    long long end = flag ? n : m - 1;
    for (long long i = start; i <= end; i++) {
        long long temp = 0;
        if (i < m) {
            temp = bngg + (s2 * (m - i));
            if (llabs(temp - hmgg) < min) {
                min = llabs(temp - hmgg);
                p2 = i;
            }
        } else if (i > m) {
            temp = hmgg + (s2 * (i - m));
            if (llabs(bngg - temp) < min) {
                min = llabs(bngg - temp);
                p2 = i;
            }
        }
    }
    printf("%lld\n", p2);
    free(c);
    return 0;
}//这道题部分使用int的时候会有部分测试集过不了，全部使用longlong就可以解决这个问题
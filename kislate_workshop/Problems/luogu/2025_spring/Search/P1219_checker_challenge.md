# P1219 [USACO1.5] 八皇后 Checker Challenge

## 题目描述

一个如下的 $6 \times 6$ 的跳棋棋盘，有六个棋子被放置在棋盘上，使得每行、每列有且只有一个，每条对角线（包括两条主对角线的所有平行线）上至多有一个棋子。

![](https://cdn.luogu.com.cn/upload/image_hosting/3h71x0yf.png)

上面的布局可以用序列 $2\ 4\ 6\ 1\ 3\ 5$ 来描述，第 $i$ 个数字表示在第 $i$ 行的相应位置有一个棋子，如下：

行号 $1\ 2\ 3\ 4\ 5\ 6$

列号 $2\ 4\ 6\ 1\ 3\ 5$

这只是棋子放置的一个解。请编一个程序找出所有棋子放置的解。  
并把它们以上面的序列方法输出，解按字典顺序排列。  
请输出前 $3$ 个解。最后一行是解的总个数。

## 输入格式

一行一个正整数 $n$，表示棋盘是 $n \times n$ 大小的。

## 输出格式

前三行为前三个解，每个解的两个数字之间用一个空格隔开。第四行只有一个数字，表示解的总数。

## 输入输出样例 #1

### 输入 #1

```
6
```

### 输出 #1

```
2 4 6 1 3 5
3 6 2 5 1 4
4 1 5 2 6 3
4
```

## 说明/提示

【数据范围】  
对于 $100\%$ 的数据，$6 \le n \le 13$。

题目翻译来自NOCOW。

USACO Training Section 1.5
## 最简单的一道提高减:
$$index直接用会报错, 系统库可能存在使用$$
```cpp
#include <bits/stdc++.h>
using namespace std;
int N, sum = 0;
int index_now = 1; // 记录当前的行数
//vector<vector<int>> dp;
vector<int> mem1(10000000, 0), mem2, path;// 第一个记录的是斜对角线的, 第二个是记录是已经用过的数字, path用来记录路径
vector<int> mem3(10000000, 0); // 记录另外一条对角线
void dfs();
int main(void)
{
    cin >> N;
    //dp.resize(N + 1, vector<int>(N + 1, 0));
    path.resize(N + 1, -1);
    mem2.resize(N + 1, 0);
    dfs();
    cout << sum << endl;
}
void dfs()
{
    if(index_now == N + 1)
    {
        sum++;
        if(sum <= 3)
        {
            for(int i = 1; i <= N; i++)
            {
                cout << path[i] << " ";
            }
            cout << endl;
        }
        return;
    }
    for(int i = 1; i <= N; i++)
    {
        if(mem1[index_now - i + N] == 0 && mem2[i] == 0 && mem3[index_now + i] == 0)
        {
            mem1[index_now-i+N] = 1;
            mem2[i] = 1;
            mem3[index_now + i] = 1;
            path[index_now] = i;
            index_now++;
            dfs();
            index_now--;
            mem1[index_now-i+N] = 0;
            mem2[i] = 0;
            mem3[index_now + i] = 0;
            path[index_now] = -1;
            // 这里是为了防止重复使用, 但是实际上并没有用到
        }
    }
}
```
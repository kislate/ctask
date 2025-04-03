# P1020 [NOIP 1999 提高组] 导弹拦截

## 题目描述

某国为了防御敌国的导弹袭击，发展出一种导弹拦截系统。但是这种导弹拦截系统有一个缺陷：虽然它的第一发炮弹能够到达任意的高度，但是以后每一发炮弹都不能高于前一发的高度。某天，雷达捕捉到敌国的导弹来袭。由于该系统还在试用阶段，所以只有一套系统，因此有可能不能拦截所有的导弹。

   
输入导弹依次飞来的高度，计算这套系统最多能拦截多少导弹，如果要拦截所有导弹最少要配备多少套这种导弹拦截系统。

## 输入格式

一行，若干个整数，中间由空格隔开。

## 输出格式

两行，每行一个整数，第一个数字表示这套系统最多能拦截多少导弹，第二个数字表示如果要拦截所有导弹最少要配备多少套这种导弹拦截系统。

## 输入输出样例 #1

### 输入 #1

```
389 207 155 300 299 170 158 65
```

### 输出 #1

```
6
2
```

## 说明/提示

对于前 $50\%$ 数据（NOIP 原题数据），满足导弹的个数不超过 $10^4$ 个。该部分数据总分共 $100$ 分。可使用$\mathcal O(n^2)$ 做法通过。  
对于后 $50\%$ 的数据，满足导弹的个数不超过 $10^5$ 个。该部分数据总分也为 $100$ 分。请使用 $\mathcal O(n\log n)$ 做法通过。

对于全部数据，满足导弹的高度为正整数，且不超过 $5\times 10^4$。


此外本题开启 spj，每点两问，按问给分。

NOIP1999 提高组 第一题

---

$\text{upd 2022.8.24}$：新增加一组 Hack 数据。
##  下面是我的尝试代码,(最终版, 时间复杂度超了, 但是洛谷抽风, 给了100分):
一个比较好的题解🔗https://www.luogu.com.cn/article/yc19s69p
```cpp
// 这里是没有dfs的计算
#include <bits/stdc++.h>
using namespace std;
int main(void) 
{
    // input
    string line;
    getline(cin, line);
    istringstream iss(line);
    int height;
    vector<int> heights;
    while(iss >> height) heights.push_back(height);
    // 

    int n = heights.size();// 长度
    vector<int> dp(n, 1);
    vector<int> dp2(n, 1);
    int ans = 0;
    int cnt = 0;
    for(int i = n-1; i >= 0; i--)// 从后往前遍历
    {
        for(int j = i + 1; j < n; j++)// 向后找最优解
        {
            if(heights[j] <= heights[i]) dp[i] = max(dp[i], dp[j] + 1);
            else if(heights[j] > heights[i]) dp2[i] = max(dp2[i], dp2[j] + 1);
        }
        //dp[i] = max(dp[i], dp[j] + 1);
        ans = max(ans, dp[i]);
        cnt = max(cnt, dp2[i]);
    }
    
    cout << ans << endl;
    cout << cnt << endl;
    //for(int i = 0; i < n; i++) cout << dp[i] << " ";
    //cout << endl;
    return 0;
}
```
`deepseek`的正经写法:
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    string line;
    getline(cin, line);
    istringstream iss(line);
    int height;
    vector<int> heights;
    while (iss >> height) heights.push_back(height);
    int n = heights.size();

    // 计算最长不上升子序列（Non-Increasing）
    vector<int> tail1;
    for (int num : heights) {
        auto it = upper_bound(tail1.begin(), tail1.end(), num, greater<int>());
        if (it == tail1.end()) {
            tail1.push_back(num);
        } else {
            *it = num;
        }
    }
    int ans1 = tail1.size();

    // 计算最长上升子序列（Increasing）
    vector<int> tail2;
    for (int num : heights) {
        auto it = lower_bound(tail2.begin(), tail2.end(), num);
        if (it == tail2.end()) {
            tail2.push_back(num);
        } else {
            *it = num;
        }
    }
    int ans2 = tail2.size();

    cout << ans1 << endl;
    cout << ans2 << endl;

    return 0;
}
```
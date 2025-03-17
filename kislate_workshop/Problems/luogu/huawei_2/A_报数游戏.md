# T586190 报数游戏

## 题目描述

华小科的班级在团建时进行了一场报数游戏，游戏的核心是数字增量 $t$，假设上一名同学报出的数字为 $x$，那么下一名同学将报出 $(x+t) \bmod M$ 的值。

华小科对 $0,1$ 有着特殊的执念。她认为，如果所报的数字里含有 $1$（如 $101,231,1$ 等），则称该数字为第 I 类幸运数字；如果所报的数字里含有 $0$（如 $101,200,0$ 等），则称该数字为第 II 类幸运数字。一个数字，如 $101$，可以同时为第 I 类和第 II 类幸运数字。

华小科的班级一共有 $k$ 名同学，每一名同学都参与了这个游戏，第一名同学从 $1$ 开始报数。华小科想要知道，报出的数中，第 I 类幸运数字，第 II 类幸运数字，同时为第 I 类幸运数字和第 II 类幸运数字的数分别有多少。

需要注意，同时为第 I 类和第 II 类幸运数字的数不再计入第 I 类幸运数字和第 II 类幸运数字。

## 输入格式

输入一行三个正整数 $k,t,M$，分别由一个空格隔开，依次代表班级人数，数字增量，取模值。

## 输出格式

输出一行三个整数，分别由一个空格隔开，依次代表第 I 类幸运数字，第 II 类幸运数字，同时为第 I 类和第 II 类幸运数字的个数。

## 输入输出样例 #1

### 输入 #1

```
6 1 100
```

### 输出 #1

```
1 0 0
```

## 输入输出样例 #2

### 输入 #2

```
6 4 11
```

### 输出 #2

```
1 0 1
```

## 输入输出样例 #3

### 输入 #3

```
906 3269516512 3963064054
```

### 输出 #3

```
332 145 316
```

## 说明/提示

对于所有测试数据，保证 $1 \le k \le 10^7$，$0 \le t < 2^{63}$，$1 \le M < 2^{63}$。

![](https://cdn.luogu.com.cn/upload/image_hosting/qszxbp4f.png)

特殊性质 A：保证 $M>k\cdot t+1$。
## 下面是代码(95分):
### 知道了,想要过,必须用`unsigned long long`:
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main(void)
{
    long long k, t, M;;
    long long num_now = 1;
    cin >> k >> t >> M;
    long long lucky_1 = 0, lucky_2 = 0, lucky_3 = 0;
    for(int i = 0; i < k; i++, num_now = (num_now + t) % M)
    {
        bool flag_1 = false, flag_2 = false;
        string temp = to_string(num_now);
        if(temp.find('1') != string::npos)
        {
            flag_1 = true;
        }
        if(temp.find('0') != string::npos)
        {
            flag_2 = true;
        }
        if(flag_1 && !flag_2)
            lucky_1++;
        if(flag_2 && !flag_1)
            lucky_2++;
        if(flag_1 && flag_2)
            lucky_3++;
    }
    cout << lucky_1 << " " << lucky_2 << " " << lucky_3 << endl;
}
```
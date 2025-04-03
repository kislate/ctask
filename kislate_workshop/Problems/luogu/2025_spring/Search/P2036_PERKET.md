# P2036 [COCI 2008/2009 #2] PERKET

## 题目描述

Perket 是一种流行的美食。为了做好 Perket，厨师必须谨慎选择食材，以在保持传统风味的同时尽可能获得最全面的味道。你有 $n$ 种可支配的配料。对于每一种配料，我们知道它们各自的酸度 $s$ 和苦度 $b$。当我们添加配料时，总的酸度为每一种配料的酸度总乘积；总的苦度为每一种配料的苦度的总和。

众所周知，美食应该做到口感适中，所以我们希望选取配料，以使得酸度和苦度的绝对差最小。

另外，我们必须添加至少一种配料，因为没有任何食物以水为配料的。

## 输入格式

第一行一个整数 $n$，表示可供选用的食材种类数。

接下来 $n$ 行，每行 $2$ 个整数 $s_i$ 和 $b_i$，表示第 $i$ 种食材的酸度和苦度。

## 输出格式

一行一个整数，表示可能的总酸度和总苦度的最小绝对差。

## 输入输出样例 #1

### 输入 #1

```
1
3 10
```

### 输出 #1

```
7
```

## 输入输出样例 #2

### 输入 #2

```
2
3 8
5 8
```

### 输出 #2

```
1
```

## 输入输出样例 #3

### 输入 #3

```
4
1 7
2 6
3 8
4 9
```

### 输出 #3

```
1
```

## 说明/提示

#### 数据规模与约定
对于 $100\%$ 的数据，有 $1 \leq n \leq 10$，且将所有可用食材全部使用产生的总酸度和总苦度小于 $1 \times 10^9$，酸度和苦度不同时为 $1$ 和 $0$。
#### 说明
- 本题满分 $70$ 分。
- 题目译自 [COCI2008-2009](https://hsin.hr/coci/archive/2008_2009/) [CONTEST #2](https://hsin.hr/coci/archive/2008_2009/contest2_tasks.pdf) PERKET，译者 @[mnesia](https://www.luogu.com.cn/user/115711)。
## 下面是尝试代码(很快就AC了, 这道题卡的第一个点就是至少要选择一种):
```cpp
#include <bits/stdc++.h>
using namespace std;
int sum = 0;
vector<int> bitter, sour;// 酸度乘积和苦度和;
int min_minus = 10000000;
void dfs(int x, int add, int mult);
int main(void)
{
    int n;
    cin >> n;
    sum = n;
    bitter.resize(n + 1);
    sour.resize(n+1);
    for(int i = 0; i < n; i++) cin >> sour[i] >> bitter[i];
    for(int i = 0; i < n; i++)
    {
        dfs(i, bitter[i], sour[i]);
    }
    cout << min_minus << endl;
}
void dfs(int x, int add, int mult)
{
    if(x == sum) return;
    min_minus = min(min_minus, abs(add - mult));
    dfs(x + 1, add + bitter[x + 1], mult * sour[x + 1]);
    dfs(x + 1, add, mult);
}
```
### 可以用二进制表示取子集(大佬解法):
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
int N,s[12],b[12],mi=2000000001;
int main()
{
	scanf("%d",&N);
	for(int i=0;i<N;i++)
		scanf("%d %d",&s[i],&b[i]);
	for(int i=1;i<(1<<N);i++)//因为至少有一种配料，所以从1开始
	{
		int S=1,B=0;//注意总酸度初始值为1！
		for(int j=0;j<N;j++)
			if((i>>j)&1)//判断是否为1
			{
				S*=s[j];
				B+=b[j];
			}
		mi=min(mi,abs(S-B));//别忘了绝对值
	}
	printf("%d",mi);
	return 0;
}
```
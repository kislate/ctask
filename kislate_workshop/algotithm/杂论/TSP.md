# P1433 吃奶酪问题知识点与逻辑

## 知识点详解

### 1. 状态压缩动态规划
状态压缩动态规划是一种通过位掩码（bitmask）表示状态的动态规划方法，常用于解决涉及多个状态组合的问题，例如旅行商问题（TSP）。

#### 核心思想
- 使用一个整数的二进制位表示状态。例如，若有 4 个点，则可以用一个 4 位二进制数表示哪些点已经访问过。
- 每个二进制位的值为 1 表示对应的点已访问，为 0 表示未访问。

#### 示例
假设有 3 个点，编号为 0、1、2：
- 状态 `011` 表示访问了点 1 和点 2，但未访问点 0。
- 状态 `101` 表示访问了点 0 和点 2，但未访问点 1。

#### 代码构建思路
1. **状态表示**

2. **状态转移**
   - 遍历所有可能的状态 `mask` 和当前点 `i`。
   - 对于每个未访问的点 `j`，更新状态：
     ```cpp
     dp[next_mask][j] = min(dp[next_mask][j], dp[mask][i] + distance(i, j));
     ```

3. **初始状态**
   - 起点状态：`dp[1][0] = 0`，表示从原点出发。

4. **终止条件**
   - 遍历所有可能的终点，找到最小的总距离。

---

### 2. 几何计算
在涉及平面几何的题目中，常需要计算两点间的欧几里得距离。

#### 距离公式
\[
\text{distance} = \sqrt{(x_1 - x_2)^2 + (y_1 - y_2)^2}
\]

#### 示例
假设有两点 A 和 B：
- A 的坐标为 (1, 1)，B 的坐标为 (4, 5)。
- 两点间的距离为：
  \[
  \sqrt{(4-1)^2 + (5-1)^2} = \sqrt{9 + 16} = 5
  \]

#### 代码构建思路
1. **定义函数**
   - 编写一个函数计算两点间的距离：
     ```cpp
     double cal_dis(double x1, double y1, double x2, double y2) {
         return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
     }
     ```

2. **预计算距离矩阵**
   - 将所有点之间的距离预先计算并存储，减少重复计算：
     ```cpp
     for (int i = 0; i < n; i++) {
         for (int j = 0; j < n; j++) {
             dist[i][j] = cal_dis(points[i].x, points[i].y, points[j].x, points[j].y);
         }
     }
     ```

---

### 3. 动态规划的转移方程
动态规划的核心是通过状态转移方程递推求解。

#### 一般形式
\[
dp[\text{mask}][i] = \min(dp[\text{mask}][i], dp[\text{prev\_mask}][j] + \text{distance}(j, i))
\]

#### 示例
假设有 3 个点，编号为 0、1、2：
- 当前状态为 `011`，最后一个访问的点是 1。
- 从点 1 转移到点 2，更新状态为 `111`：
  ```cpp
  dp[111][2] = min(dp[111][2], dp[011][1] + dist[1][2]);
  ```

#### 代码构建思路
1. **初始化动态规划数组**
   - 将所有状态初始化为无穷大：
     ```cpp
     for (int mask = 0; mask < (1 << n); mask++) {
         for (int i = 0; i < n; i++) {
             dp[mask][i] = INF;
         }
     }
     ```

2. **状态转移**
   - 遍历所有状态和当前点，更新转移方程：
     ```cpp
     for (int mask = 0; mask < (1 << n); mask++) {
         for (int i = 0; i < n; i++) {
             if (!(mask & (1 << i))) continue; // 当前点未访问
             for (int j = 0; j < n; j++) {
                 if (mask & (1 << j)) continue; // 点 j 已访问
                 int next_mask = mask | (1 << j);
                 dp[next_mask][j] = min(dp[next_mask][j], dp[mask][i] + dist[i][j]);
             }
         }
     }
     ```

---

### 4. 算法优化
- **预计算距离矩阵**：将所有点之间的距离预先计算并存储，减少重复计算。
- **剪枝**：在状态转移时跳过不可能的状态，减少计算量。

#### 示例
假设有 4 个点，编号为 0、1、2、3：
- 预计算距离矩阵：
  ```cpp
  for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
          dist[i][j] = cal_dis(points[i].x, points[i].y, points[j].x, points[j].y);
      }
  }
  ```
- 剪枝：若当前状态 `mask` 已经包含点 3，则无需再尝试从点 3 转移到其他点。

---

## 在 P1433 中的应用

### 问题描述
给定若干块奶酪的坐标，求从原点出发，访问所有奶酪并返回原点的最短路径。

### 算法名称
旅行商问题（TSP）的状态压缩动态规划解法。

### 应用步骤

1. **状态表示**
   - 使用位掩码表示状态。例如，若有 3 块奶酪，则状态 `mask = 011` 表示访问了第 2 和第 3 块奶酪。

2. **状态转移**
   - 转移方程：
     ```cpp
     dp[mask | (1 << j)][j] = min(dp[mask | (1 << j)][j], dp[mask][i] + dist[i][j]);
     ```
   - 含义：从状态 `mask` 转移到状态 `mask | (1 << j)`，最后一个访问的点是 `j`。

3. **初始状态**
   - 起点状态：`dp[1][0] = 0`，表示从原点出发。

4. **终止条件**
   - 遍历所有可能的终点，找到最小的总距离。

5. **输出结果**
   - 输出最小路径长度，保留两位小数。

### 示例讲解

#### 输入示例
```
3
1 1
2 2
2 4
```

#### 输出示例
```
7.65
```

#### 详细步骤
1. **初始化**
   - 奶酪数量为 3，坐标分别为 (1, 1)、(2, 2)、(2, 4)。
   - 预计算距离矩阵：
     \[
     \text{distance}(i, j) = \sqrt{(x_i - x_j)^2 + (y_i - y_j)^2}
     \]

2. **状态转移**
   - 遍历所有状态 \( \text{mask} \) 和当前点 \( i \)。
   - 对于每个未访问的点 \( j \)，更新状态转移方程。

3. **求解答案**
   - 遍历所有可能的终点，找到最小的总距离。

4. **输出结果**
   - 使用 `printf` 输出结果，保留两位小数。

## 示例代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
vector<pair<double, double>> cheese;
double dp[1<<16][16];

double cal_dis(double x1, double y1, double x2, double y2) {
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

int main() {
    cin >> n;
    cheese.push_back({0,0});
    for(int i=1;i<=n;i++) {
        double x, y;
        cin >> x >> y;
        cheese.push_back({x, y});
    }
    int N = n+1;
    int full = (1<<N)-1;
    for(int i=0;i<(1<<N);i++)
        for(int j=0;j<N;j++)
            dp[i][j]=1e18;
    dp[1][0]=0; // 只在原点

    for(int mask=1;mask<(1<<N);mask++) {
        for(int u=0;u<N;u++) {
            if(!(mask&(1<<u))) continue;
            for(int v=1;v<N;v++) {
                if(mask&(1<<v)) continue;
                int next=mask|(1<<v);
                double d=cal_dis(cheese[u].first,cheese[u].second,cheese[v].first,cheese[v].second);
                dp[next][v]=min(dp[next][v],dp[mask][u]+d);
            }
        }
    }
    double ans=1e18;
    for(int i=1;i<N;i++) {
        ans=min(ans,dp[full][i]);
    }
    printf("%.2f\n",ans);
    return 0;
}
```
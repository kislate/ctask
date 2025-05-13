#include <bits/stdc++.h>
using namespace std;
long long state[2005], site[2005], dp[15][2005][2005];
int n, k, cnt; // cnt 用于记录合法状态的数量
void dfs(int x, int num, int cur)
{
    if(cur >= n){
        site[++cnt] = x;
        state[cnt] = num;
        return;
    }
    dfs(x, num, cur + 1);                         // 不选当前位
    dfs(x + (1 << cur), num + 1, cur + 2);        // 当前列放国王, 跳过下一列
 }

 // 判断上一行和当前行是否有冲突
 bool compatible(int x, int y)
 {
    if(site[x] & site[y]) return false;          // 正上方
    if((site[x] << 1) & site[y]) return false;   // 左上方
    if(site[x] & (site[y] << 1)) return false;   // 右上方
    return true;
  }
  int main(void)
  {
    cin >> n >> k;
    dfs(0, 0, 0); // 生成所有合法状态, 此时cnt 和 state 和 site就会初始化完毕, 每一行的合法情况不会超出这些限定范围
    for(int i = 1; i <= cnt; i++) dp[1][i][state[i]] = 1; // 初始化第一行
    for(int i = 2; i <= n; i++)// 枚举各行
    {
        for(int x = 1; x <= cnt; x++)// 遍历当前行的合法状态
        {
            for(int y = 1; y <= cnt; y++)// 遍历上一行的合法状态
            {
                if(!compatible(x, y)) continue;// 状态冲突
                for(int l = state[x]; l <= k; l++)// 当前行此合法状态下的总状态数
                {
                    dp[i][x][l] += dp[i - 1][y][l - state[x]]; // 计算当前行的合法状态数
                }
            }
        }
    }
    long long ans = 0;
    for(int i = 1; i <= cnt; i++) ans += dp[n][i][k]; // 统计所有合法状态
    cout << ans << endl;
    return 0;
  }
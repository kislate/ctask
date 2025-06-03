#include <bits/stdc++.h>
using namespace std;
int n, m, ret = 0, a[22];
bool tf[22], f[2500];
void dp()
{
    memset(f, false, sizeof(f));
    f[0] = true;
    int tot = 0;
    for (int i = 0; i < n; i++)
    {
        if (tf[i]) continue;
        tot += a[i];
        for (int j = tot; j >= a[i]; j--)
        {
            if (f[j - a[i]]) f[j] = true;
        }
    }
    int ans = 0;
    for (int i = 1; i <= tot; i++)
    {
        if (f[i]) ans++;
    }
    ret = max(ret, ans);
}
void dfs(int cur, int cnt)
{
    if (cnt > m) return;
    if (cur == n)
    {
        if (cnt == m) dp();
        return;
    }
    // 不删当前
    tf[cur] = false;
    dfs(cur + 1, cnt);
    // 删当前
    tf[cur] = true;
    dfs(cur + 1, cnt + 1);
}
int main(void)
{
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> a[i];
    dfs(0, 0);
    cout << ret << endl;
    return 0;
}
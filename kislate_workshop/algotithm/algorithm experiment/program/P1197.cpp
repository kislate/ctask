#include <bits/stdc++.h>
using namespace std;
int cnt;
vector<int> fa, ans, damages;
vector<vector<int>> v;
vector<bool> planets;
// 实测'&'快20ms；
int find(int& i) {
    // cao， 忘了路径压缩
    return fa[i] = fa[i] == i ? i : find(fa[i]);
}

// '\n' 卡常数
int main(void) {
    ios::sync_with_stdio(false); cin.tie(0);
    int n, m, k;
    cin >> n >> m;
    cnt = n;
    fa.resize(n);
    planets.resize(n, true);
    v.resize(n);
    iota(fa.begin(), fa.end(), 0);
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    cin >> k;
    cnt -= k;
    while(k--) {
        int x; cin >> x;
        planets[x] = false; 
        damages.push_back(x);
    }

    // 摧毁后的星球不算在里面， 6
    for (int i = 0; i < n; ++i) {
        // cout << "Now: " << i << '\n';
        if (!planets[i]) {
            // cout << "pass1 " << i << '\n';
            continue;
        }
        for (int u : v[i]) {
            if (u < i) continue; // 剪枝
            if (!planets[u]) {
                // cout << "pass2 " << u << '\n';
                continue;
            }
            int rootx = find(u), rooty = find(i);
            if (rootx != rooty) {
                // cout << "merge " << u << " " << i << '\n';
                fa[rootx] = rooty;
                --cnt;
            }
        }
    }
    ans.push_back(cnt);
    for (int i = damages.size() - 1; i >= 0; --i) {
        int damage = damages[i];
        ++cnt;
        for (int u : v[damage]) {
            if (!planets[u]) continue;
            int rootx = find(u), rooty = find(damage);
            if (rootx != rooty) {
                // cout << "merge " << u << " " << i << '\n';
                fa[rootx] = rooty;
                --cnt;
            }
        }
        ans.push_back(cnt);
        planets[damage] = true;
    }
    for (int i = ans.size() - 1; i >= 0; --i) cout << ans[i] << '\n';
}
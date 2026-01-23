#include <bits/stdc++.h>
using namespace std;
int n, h, ans = 0;
struct region {
    int b, e, t;
};
vector<region> regions;
vector<bool> trees;
int main(void) {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n >> h;
    regions.resize(h);
    trees.resize(n + 1);
    for (int i = 0; i < h; ++i) {
        cin >> regions[i].b >> regions[i].e >> regions[i].t;
    }
    sort(regions.begin(), regions.end(), [](const region& a, const region& b) {
        return a.e < b.e;
    });
    // 尽可能填充右边的格子
    for (int i = 0; i < h; ++i) {
        int cnt = 0;
        for (int j = regions[i].b; j <= regions[i].e; ++j) {
            if (trees[j]) ++cnt;
        }
        if (cnt < regions[i].t) {
            int need = regions[i].t - cnt, pos = regions[i].e;
            while(need) {
                if (!trees[pos]) trees[pos] = true, ++ans, --need;
                --pos;
            }
        }
    }
    cout << ans << endl;
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
int n;
vector<int> tree, boss;
int lowbit(int x) {
    return x & -x;
}

void add(int x, int k) {
    while (x <= n) {
        tree[x] += k;
        x += lowbit(x);
    }
}

int main(void) {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    tree.resize(n + 1, 0);
    boss.resize(n + 1, 1);
    for (int i = 1; i <= n; ++i) {
        int k; cin >> k;
        add(i, k);
    }
    for (int i = 2; i <= n; ++i) cin >> boss[i];
    meizuowan
}
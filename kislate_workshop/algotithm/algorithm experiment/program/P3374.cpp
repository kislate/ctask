#include <bits/stdc++.h>
using namespace std;
int n, m;
vector<int> tree;
int lowbit(int &x) {
    return x & -x; // good
}
void add(int x, int &k) {
    while (x <= n) {
        tree[x] += k;
        x += lowbit(x);
    }
}

int query(int x) {
    int sum = 0;
    while (x > 0) {
        sum += tree[x];
        x -= lowbit(x);
    }
    return sum;
}

int main(void) {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    tree.resize(n + 1); // 必须从1开始
    for (int i = 1; i <= n; ++i) {
        int k; cin >> k;
        add(i, k);
    }
    while (m--) {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 1) {
            add(x, y);
        } else {
            cout << query(y) - query(x - 1) << '\n';
        }
    }
}
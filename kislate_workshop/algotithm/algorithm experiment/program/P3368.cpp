#include <bits/stdc++.h>
using namespace std;
int n, m;
vector<int> tree;
int lowbit(int &x) {
    return x & -x; // good
}
void add(int x, int k) {
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
    int last = 0;
    for (int i = 1; i <= n; ++i) {
        int k; cin >> k;
        add(i, k - last);
        last = k;
    }
    while (m--) {
        int op; cin >> op;
        if (op == 1) {
            int x, y, k;
            cin >> x >> y >> k;
            add(x, k);
            add(y + 1, -k);
        } else {
            int x; cin >> x;
            cout << query(x) << '\n';
        }
    }
}
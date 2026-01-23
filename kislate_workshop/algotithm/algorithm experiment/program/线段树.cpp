#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

const int MAXN = 100005;
ll a[MAXN], tree[MAXN << 2], add[MAXN << 2], mul[MAXN << 2];
int n, q;
ll m;

// 向上更新
void push_up(int rt) {
    tree[rt] = (tree[rt << 1] + tree[rt << 1 | 1]) % m;
}

// 建立线段树
void build(int rt, int l, int r) {
    mul[rt] = 1; // 乘法标记初始化为 1
    if (l == r) {
        tree[rt] = a[l] % m;
        return;
    }
    int mid = (l + r) >> 1;
    build(rt << 1, l, mid);
    build(rt << 1 | 1, mid + 1, r);
    push_up(rt);
}

// 核心：下传标记
void push_down(int rt, int l, int r) {
    int mid = (l + r) >> 1;
    int ln = mid - l + 1, rn = r - mid;

    // 更新左儿子
    tree[rt << 1] = (tree[rt << 1] * mul[rt] + add[rt] * ln) % m;
    mul[rt << 1] = (mul[rt << 1] * mul[rt]) % m;
    add[rt << 1] = (add[rt << 1] * mul[rt] + add[rt]) % m;

    // 更新右儿子
    tree[rt << 1 | 1] = (tree[rt << 1 | 1] * mul[rt] + add[rt] * rn) % m;
    mul[rt << 1 | 1] = (mul[rt << 1 | 1] * mul[rt]) % m;
    add[rt << 1 | 1] = (add[rt << 1 | 1] * mul[rt] + add[rt]) % m;

    // 重置父节点标记
    mul[rt] = 1;
    add[rt] = 0;
}

// 区间乘法
void update_mul(int rt, int l, int r, int L, int R, ll k) {
    if (L <= l && r <= R) {
        tree[rt] = (tree[rt] * k) % m;
        mul[rt] = (mul[rt] * k) % m;
        add[rt] = (add[rt] * k) % m; // 加法标记也要跟着乘
        return;
    }
    push_down(rt, l, r);
    int mid = (l + r) >> 1;
    if (L <= mid) update_mul(rt << 1, l, mid, L, R, k);
    if (R > mid) update_mul(rt << 1 | 1, mid + 1, r, L, R, k);
    push_up(rt);
}

// 区间加法
void update_add(int rt, int l, int r, int L, int R, ll k) {
    if (L <= l && r <= R) {
        tree[rt] = (tree[rt] + k * (r - l + 1)) % m;
        add[rt] = (add[rt] + k) % m;
        return;
    }
    push_down(rt, l, r);
    int mid = (l + r) >> 1;
    if (L <= mid) update_add(rt << 1, l, mid, L, R, k);
    if (R > mid) update_add(rt << 1 | 1, mid + 1, r, L, R, k);
    push_up(rt);
}

// 区间查询
ll query(int rt, int l, int r, int L, int R) {
    if (L <= l && r <= R) return tree[rt];
    push_down(rt, l, r);
    int mid = (l + r) >> 1;
    ll res = 0;
    if (L <= mid) res = (res + query(rt << 1, l, mid, L, R)) % m;
    if (R > mid) res = (res + query(rt << 1 | 1, mid + 1, r, L, R)) % m;
    return res;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n >> q >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build(1, 1, n);
    while (q--) {
        int op, x, y;
        ll k;
        cin >> op >> x >> y;
        if (op == 1) {
            cin >> k;
            update_mul(1, 1, n, x, y, k);
        } else if (op == 2) {
            cin >> k;
            update_add(1, 1, n, x, y, k);
        } else {
            cout << query(1, 1, n, x, y) << '\n';
        }
    }
    return 0;
}
// XOR_3
// 2025_3
// create by deepseek_R1
#include <iostream>
#include <string>
using namespace std;

const int MAXN = 2e5 + 10;

struct Node {
    int l, r;    // 区间范围
    int sum;     // 区间内1的个数
    int tag;     // 延迟标记（奇数次反转需要处理）
} tree[MAXN * 4];

string s;

void push_up(int p) {
    tree[p].sum = tree[p<<1].sum + tree[p<<1|1].sum;
}

void push_down(int p) {
    if (tree[p].tag) {
        int mid = (tree[p].l + tree[p].r) >> 1;
        // 处理左子树
        tree[p<<1].sum = (mid - tree[p].l + 1) - tree[p<<1].sum;
        tree[p<<1].tag ^= 1;
        // 处理右子树
        tree[p<<1|1].sum = (tree[p].r - mid) - tree[p<<1|1].sum; 
        tree[p<<1|1].tag ^= 1;
        // 清除标记
        tree[p].tag = 0;
    }
}

void build(int p, int l, int r) {
    tree[p].l = l;
    tree[p].r = r;
    tree[p].tag = 0;
    
    if (l == r) {
        tree[p].sum = s[l-1] - '0';
        return;
    }
    
    int mid = (l + r) >> 1;
    build(p<<1, l, mid);
    build(p<<1|1, mid+1, r);
    push_up(p);
}

void update(int p, int l, int r) {
    if (tree[p].l >= l && tree[p].r <= r) {
        tree[p].sum = (tree[p].r - tree[p].l + 1) - tree[p].sum;
        tree[p].tag ^= 1;
        return;
    }
    
    push_down(p);
    int mid = (tree[p].l + tree[p].r) >> 1;
    if (l <= mid) update(p<<1, l, r);
    if (r > mid) update(p<<1|1, l, r);
    push_up(p);
}

int query(int p, int l, int r) {
    if (tree[p].l >= l && tree[p].r <= r) {
        return tree[p].sum;
    }
    
    push_down(p);
    int mid = (tree[p].l + tree[p].r) >> 1;
    int res = 0;
    if (l <= mid) res += query(p<<1, l, r);
    if (r > mid) res += query(p<<1|1, l, r);
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n, m;
    cin >> n >> m >> s;
    
    build(1, 1, n);
    
    while (m--) {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 0) {
            update(1, l, r);
        } else {
            cout << query(1, l, r) << "\n";
        }
    }
    
    return 0;
}
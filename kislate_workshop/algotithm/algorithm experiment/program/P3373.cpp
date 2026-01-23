#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 100005;
ll a[MAXN], tree[MAXN << 2], add[MAXN << 2], mul[MAXN << 2];
int n, q;
ll m;

void push_up(int root) {
    tree[root] = (tree[root << 1] + tree[root << 1 | 1]) % m;
}

void build(int root, int l, int r) {
    mul[root] = 1;
    if (l == r) {
        tree[root] = a[l] % m; 
        return;
    }
    int mid = (l + r) >> 1;
    build(root << 1, l, mid);
    build(root << 1 | 1, mid + 1, r);
    push_up(root);
}

void push_down(int root, int l, int r) {
    int mid = (l + r) >> 1;
    int ln = mid - l + 1, rn = r - mid;

    tree[root << 1] = (tree[root << 1])
}
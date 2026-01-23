#include <bits/stdc++.h>
using namespace std;
typedef struct clerk{
    int happy;
    int master;
    vector<int> slaves;
}clerk;
vector<clerk> clerks;
int root = 0;
int n, ans = 0;
vector<vector<int>> memo;
int get_happy(int root, bool use) {
    if (use && memo[root][1]) return memo[root][1];
    if (!use && memo[root][0]) return memo[root][0];
    if (clerks[root].slaves.empty()) {
        if (use) {
            return clerks[root].happy;
        } else {
            return 0;
        }
    }
    int sum = 0;
    if (!use) {
        for (auto slave : clerks[root].slaves) {
            sum += max(get_happy(slave, true), get_happy(slave, false));
        }
    }
    else {
        for (auto slave : clerks[root].slaves) {
            sum += get_happy(slave, false);
        }
    }
    if (use) sum += clerks[root].happy;
    if (use) memo[root][1] = sum;
    else memo[root][0] = sum;
    return sum;
}   
int main(void) {
    cin >> n;
    clerks.resize(n + 1);
    memo.resize(n + 1, vector<int>(2, 0));
    for (int i = 1; i <= n; ++i) {
        cin >> clerks[i].happy;
        clerks[i].master = i;
    }
    for (int i = 1; i <= n - 1; ++i) {
        int l, k;
        cin >> l >> k;
        clerks[l].master = k;
        clerks[k].slaves.push_back(l);
    }
    for (int i = 1; i <= n; ++i) {
        if (clerks[i].master == i) {
            root = i;
            break;
        }
    }
    // cout << root << endl;
    ans = max(get_happy(root, false), get_happy(root, true));
    cout << ans << endl;
    return 0;
}
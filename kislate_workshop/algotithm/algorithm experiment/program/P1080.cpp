#include <bits/stdc++.h>
using namespace std;
int n, king_l, king_r;
typedef struct m {
    int l, r;
} m;
struct CompareM {
    bool operator()(const m& m1, const m& m2) const {
        if (m1.r != m2.r) {
            return m1.r < m2.r;
        }
        return m1.l < m2.l; 
    }
};
multiset<m, CompareM> ms;
bool check(int mid) {
    multiset<m, CompareM> tmp = ms;
    int all_l = king_l;
    for (int i = 0; i < n; i++) {
        m query = {0, (all_l / mid + ((all_l % mid > 0) ? 0 : -1))};
        auto it = tmp.lower_bound(query);
        if (it == tmp.end()) {
            return false;
        }
        all_l *= (*it).l;
        tmp.erase(it);
    }
    return true;
}

int main(void) {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n >> king_l >> king_r;
    int min_r = 1e9, all = king_l;
    for (int i = 1; i <= n; ++i) {
    }
    // 贪心的边界；
    // int l = all / max_r;
    int l = 1e9;
    for (int i = 1; i <= n; ++i) {
        m minister;
        cin >> minister.l >> minister.r;
        all *= minister.l;
        ms.insert(minister);
        min_r = min(min_r, minister.r);
    }

    // 找到左右边界
    for (auto minister : ms) {
        l = min(l, all / (minister.l * minister.r));
    }
    int r = all / min_r;
    while(l < r) {
        int mid = (l + r) / 2; // 取下界， 选r；
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    cout << r << endl;
}
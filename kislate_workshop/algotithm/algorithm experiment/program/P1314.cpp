#include <bits/stdc++.h>
using namespace std;
int main(void) {
    long long n , m, s, ans = 1e13;
    long long l = 0, r = 0, mid;
    cin >> n >> m >> s;
    vector<long long>prefix_weight(n + 1, 0), prefix_value(n + 1, 0); // weight * value = yi;
    vector<pair<long long, long long>> sections(m + 1), stones(n + 1);
    for (long long i = 1; i <= n; ++i) {
        // weight, value
        cin >> stones[i].first >> stones[i].second;
        r = max(stones[i].first, r);
    }
    for (long long i = 1; i <= m; ++i) {
        // li, ri
        cin >> sections[i].first >> sections[i].second;
    }
    while(l < r) {
        mid = (r + l + 1) >> 1;
        for (long long i = 1; i <= n; ++i) {
            if (stones[i].first >= mid) {
                prefix_weight[i] = prefix_weight[i - 1] + 1;
                prefix_value[i] = prefix_value[i - 1] + stones[i].second;
            } else {
                prefix_value[i] = prefix_value[i - 1];
                prefix_weight[i] = prefix_weight[i - 1];
            }
        }
        long long y = 0;
        for (long long i = 1; i <= m; ++i) {
            long long li = sections[i].first, ri = sections[i].second;
            y += (prefix_weight[ri] - prefix_weight[li - 1]) *
                (prefix_value[ri] - prefix_value[li - 1]);
        }
        if ((y - s) > 0) l = mid;
        else r = mid - 1;
        ans = min(ans, abs(y - s));
        if (ans == 0) break;
    }
    cout << ans << endl;
}
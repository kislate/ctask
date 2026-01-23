#include <bits/stdc++.h>
using namespace std;
vector<int> values;
int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int X, N, max_value = 0, count = 0;
    cin >> X >> N;
    values.resize(N);
    for (int i = 0; i < N; ++i) cin >> values[i];
    sort(values.begin(), values.end());
    for (int i = 1; i <= X; ++i) {
        if (max_value >= i) continue;
        auto it = upper_bound(values.begin(), values.end(), i);
        if (it == values.begin()) {
            cout << -1 << endl;
            return 0;
        }
        ++count, --it; max_value += *it;
    }
    cout << count << endl;
    return 0;
}
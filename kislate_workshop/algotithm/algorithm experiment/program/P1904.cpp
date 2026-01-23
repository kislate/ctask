#include <bits/stdc++.h>
using namespace std;
int main(void) {
    vector<int> ground(100001, 0);
    int L, H, R;
    while(cin >> L) {
        cin >> H >> R;
        for (int i = L; i < R; ++i) {
            ground[i] = max(ground[i], H);
        }
    }
    for (int i = 1; i < 100001; ++i) {
        if (ground[i] != ground[i - 1]) {
            cout << i << " " << ground[i] << " ";
        }
    }
    // for (int i = 0; i < 30; ++i) {
    //     cout << ground[i] << " ";
    // }
    return 0;
}
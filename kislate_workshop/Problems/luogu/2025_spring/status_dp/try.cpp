#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;

int main() {
    ull W, n;
    cin >> W >> n;
    vector<pair<ull, ull>> people(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> people[i].first >> people[i].second;

    // 按时间从大到小排序；时间相同时重量从大到小
    sort(people.begin() + 1, people.end(), [](const pair<ull, ull>& a, const pair<ull, ull>& b) {
        if (a.first != b.first) return a.first > b.first;
        return a.second > b.second;
    });

    ull total_time = 0;
    vector<bool> used(n + 1, false);

    while (true) {
        ull weight = 0, time = 0;
        bool found = false;

        // 第一次遍历：优先装填
        for (int i = 1; i <= n; ++i) {
            if (used[i]) continue;
            if (weight + people[i].second <= W) {
                weight += people[i].second;
                if (!found) {
                    time = people[i].first;
                    found = true;
                }
                used[i] = true;
            }
        }

        // 如果这一轮没人过桥，结束
        if (!found) break;

        total_time += time;
    }

    cout << total_time << endl;
    return 0;
}
#include <bits/stdc++.h>
#define lld long double
using namespace std;
int n;
lld ans = 0;
vector<int> times;
priority_queue<pair<int, int>> heap;
int main()
{
    cin >> n;
    times.resize(n + 1, 0);
    for(int i = 1; i <= n; i++)
    {
        cin >> times[i];
        heap.push({-times[i], -i});
    }
    int cnt = 0;
    while(!heap.empty())
    {
        auto [time, id] = heap.top();
        heap.pop();
        cout << -id << " ";
        cnt++;
        ans += -time * (n - cnt);
    }
    cout << endl << fixed << setprecision(2) << ans / n << endl;
    return 0;
}
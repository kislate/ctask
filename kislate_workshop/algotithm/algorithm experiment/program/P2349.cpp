#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> v, w, ws;   
int main(void) {
    ios::sync_with_stdio(false); cin.tie(0);
    int N, M, ans = 1e9;
    cin >> N >> M;
    v.resize(N + 1);
    w.resize(N + 1);
    set<int> weights;
    for (int i = 1; i <= M; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        v[a].push_back(b);
        v[b].push_back(a);
        w[a].push_back(c);
        w[b].push_back(c);
        weights.insert(c);
    }
    
    for (auto max_e : weights) {
        vector<int> dist(N + 1, 1e9);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heapq;
        heapq.push({0, 1}); // dist, u;
        while(!heapq.empty()) {
            auto [d, u] = heapq.top(); heapq.pop();
            if (dist[u] != 1e9) continue;
            dist[u] = d;

            for (int i = 0; i < v[u].size(); ++i) {
                int x = v[u][i], weight = w[u][i];
                if (dist[x] != 1e9) continue;
                if (weight <= max_e) {
                    heapq.push({dist[u] + weight, x});
                }
            }
        }

        ans = min(ans, dist[N] + max_e);
    }
    cout << ans << endl;
    return 0;
} 
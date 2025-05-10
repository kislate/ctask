#include <bits/stdc++.h>
using namespace std;
vector<vector<pair<int, int>>> adjacent_list;// 有向
vector<int> min_distance, visited;
struct cmp{
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        return a.first > b.first; // 小顶堆
    }
};
int main(void)
{
    int n, m, s;
    cin >> n >> m >> s;
    min_distance.resize(n + 1, INT_MAX);
    visited.resize(n + 1, 0);
    adjacent_list.resize(n + 1);
    for(int i = 1; i <= m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adjacent_list[u].push_back({v, w});
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> heapq;
    heapq.push({0, s});
    while(!heapq.empty())
    {
        auto [dis, u] = heapq.top();
        heapq.pop();
        if(visited[u]) continue;
        visited[u] = 1, min_distance[u] = dis;
        for(auto [v, w] : adjacent_list[u]) if(!visited[v]) heapq.push({dis + w, v});
    }
    for(int i = 1; i <= n; i++) cout << min_distance[i] << " ";
    return 0;
}
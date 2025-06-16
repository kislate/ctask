#include <bits/stdc++.h>
using namespace std;
long long n, root = 0;
typedef struct{
    vector<long long> children;
    vector<long long> weights;
} Node;
vector<Node> tree;
vector<long long> dp;
int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    tree.resize(n + 1);
    dp.resize(n + 1, -1);
    for(long long i =1; i < n; i++)
    {
        long long u, v, w;
        cin >> u >> v >> w;
        // when u == v, it is wrong;
        root ^= (u ^ v); // XOR to find the root node
        tree[u].children.push_back(v);
        tree[u].weights.push_back(w);
        tree[v].children.push_back(u);
        tree[v].weights.push_back(w);
    }
    root = 1; // Set root to 1, as the problem states the tree is rooted at node 1
    queue<pair<long long, long long>> heap;
    heap.push({root, 0});
    while(!heap.empty())
    {
        auto [u, d] = heap.front();
        heap.pop();
        if(dp[u] != -1) continue; // If already visited, skip
        dp[u] = d; // Set the distance for node u
        // XOR distance for the root node
        for(size_t i = 0; i < tree[u].children.size(); i++)
        {
            long long v = tree[u].children[i];
            long long w = tree[u].weights[i];
            if(dp[v] == -1)
            {
                heap.push({v, d ^ w}); // Push the child node with XOR distance
            }
            else
            {
                continue;
            }
        }
    }
    long long ans = 0;
    for(long long i = 1; i <= n; i++)
    {
        for(long long j = 1; j <= n; j++)
        {
            // cout << i << " " << j << " " << (dp[i] ^ dp[j]) << endl;
            ans = max(ans, (dp[i] ^ dp[j]));
        }
    }
    cout << ans << endl;
    return 0;
}
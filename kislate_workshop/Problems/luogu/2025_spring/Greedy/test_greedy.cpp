#include <bits/stdc++.h>
using namespace std;
struct cmp{
    bool operator()(pair<int, int> a, pair<int, int> b){
        return a.second > b.second;
    }
    
};
int main(void)
{
    int n, s, a, b, max_height = 0, cnt = 0;
    cin >> n >> s >> a >> b;
    max_height = a + b;
    priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> heapq;
    for(int i = 0; i < n; i++){
        int x, y;
        cin >> x >> y;
        if(x > max_height || y > s) continue;
        heapq.push({x, y});
    }
    while(!heapq.empty()){
        auto [x, y] = heapq.top();
        heapq.pop();
        if(s - y < 0) continue;
        s -= y;
        cnt++;
    }
    cout << cnt << endl;
}
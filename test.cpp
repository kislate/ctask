#include <bits/stdc++.h>
using namespace std;
struct cmp
{
    bool operator()(const int&a, const int& b){
        return a > b;
    }
};
int main(void){
    priority_queue<int, vector<int>, cmp> heapq;
    int n;
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        heapq.push(x);
    }
    int ans = 0;
    while(heapq.size() > 1)
    {
        int x = heapq.top(); heapq.pop();
        int y = heapq.top(); heapq.pop();
        ans += (x + y);
        heapq.push(x + y);
    }
    cout << ans << endl;
}
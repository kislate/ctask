#include <bits/stdc++.h>
using namespace std;
int main(void)
{
    priority_queue<int> heapq;
    int n;
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        heapq.push(-x);
    }
    int ans = 0;
    while(1)
    {
        int x = -heapq.top();
        heapq.pop();
        int y = -heapq.top();
        heapq.pop();
        ans += (x + y);
        int temp = x + y;
        if(heapq.empty())
            break;
        heapq.push(temp);
    }
    cout << ans << endl;
    return 0;
}
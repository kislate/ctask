#include <iostream>
#include <queue>

using namespace std;

int main(void)
{
    int n, m, k;
    cin >> n >> m >> k;
    priority_queue<pair<int, int>> pq;
    for(int i = 0; i < n; i++)
    {
        int t, c;
        cin >> t >> c;
        pq.push(make_pair(t,-c));
    }
    while(m > 0)
    {
        pair<int, int> p = pq.top();
        pq.pop();
        int t = p.first;
        int c = -p.second;
        if( t <= k || c > m)
        {
            pq.push(make_pair(t, -c));
            break;
        }
        m -= c;
        pq.push(make_pair(t-1,-c));
    }
    cout << pq.top().first << endl;
}

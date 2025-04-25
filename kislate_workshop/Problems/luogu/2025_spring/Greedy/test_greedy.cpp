#include <bits/stdc++.h>
using namespace std;
int main(void)
{
    unsigned long long n, ans = 0;
    cin >> n;
    vector<unsigned long long> heights(n + 1, 0);
    for(unsigned long long i = 1; i <= n; i++) cin >> heights[i];
    sort(heights.begin() + 1, heights.end());
    unsigned long long _left = 0, _right = n, cnt = 0;
    while(_left < _right)
    {
        ans += pow(heights[_right] - heights[_left], 2);
        if(cnt % 2 == 0) _left++;
        else _right--;
        cnt++;
    }
    cout << ans << endl;
    return 0;
}
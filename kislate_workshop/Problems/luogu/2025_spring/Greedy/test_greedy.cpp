#include <bits/stdc++.h>
using namespace std;
int main(void)
{
    int n;
    cin >> n;
    vector<pair<double, double>> randians;
    for(int i = 0; i < n; i++)
    {
        double cx, cy, radius;
        cin >> cx >> cy >> radius;
        double theta = atan2(cy, cx);
        double phi = asin(radius / sqrt(cx * cx + cy * cy));
        randians.push_back({theta - phi, theta + phi});
    }
    sort(randians.begin(), randians.end());
    double _left = 0, _right = 0, ans = 0;// 不用考虑超出90度的情况;
    for(int i = 0; i < n; i++)
    {
        double l = randians[i].first, r = randians[i].second;
        if(_right < l) ans += _right - _left, _left = l, _right = r;
        else if(_right < r) _right = r;
    }
    ans += _right - _left;
    cout << fixed << setprecision(3) << 1 - ans / atan2(1, 0) << endl;
    return 0;
}
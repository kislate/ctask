#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
// using ull = unsigned long long;

int n, p;
vector<double> a, b;
bool check(double mid);
int main(void)
{
    cin >> n >> p;
    a.resize(n + 1);
    b.resize(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i] >> b[i];
    double left = 0, right = 1e12;
    if(check(right)){
        cout << -1 << endl;
        return 0;
    }
    while(left < right)
    {
        double mid = (left + right) / 2;
        if(check(mid)) left = mid;
        else right = mid;
        if(right - left < 1e-4) break;
    }
    cout << fixed << setprecision(6) << left << endl;
    return 0;
}
bool check(double mid)
{
    double total = mid * p;
    for(int i = 1; i <= n; i++)
    {
        if(b[i] < mid * a[i]) total -= mid * a[i] - b[i];
        if(total < 0) return false;
    }
    return true;
}
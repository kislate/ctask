#include <bits/stdc++.h>
using namespace std;
int n,p;
vector<int> a(100005),b(100005);
int check(double mid); //函数声明
int main(){
    cin >> n >> p;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        cin >> b[i];
    }
    double l = 0, r = 1e12;
    double num = r;
    while(r-l>1e-6){
        double mid = (l+r)/2;
        if(check(mid)){
            l = mid;
        }
        else{
            r = mid;
        }
    }
    if(num - l < 1) cout << -1 << endl;
    else cout << l << endl;

}
int check(double mid){
    double add = mid * p;
    double sum = 0;
    for(int i=1;i<=n;i++){
        double temp = mid * a[i];
        if(temp > b[i]) sum += temp - b[i];
    }
    if(add >= sum) return 1;
    else return 0;
}
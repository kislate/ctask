#include <bits/stdc++.h>
using namespace std;
int main(void) {
    int k;
    cin >> k;
    for (int i = 0; i < k; i++) {
        int x, y, z;
        float num;
        cin >> x >> y >> z;
        num = (z - x) / (float)y;
        int temp = (int)(num * 100);
        cout << temp / 10 + 1 << " " << temp % 10 + 1 << endl;
    }
}
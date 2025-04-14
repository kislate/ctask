#include <bits/stdc++.h>
using namespace std;
int main(void)
{
    int n, m;
    cin >> n >> m;
    // 0 是朝内, 1 是朝外
    vector<int> types(n + 1, 0);// 虽然是n+1, 但是还是从0开始;
    vector<string> names(n + 1, "");
    for(int i = 0; i < n; i++)
    {
        cin >> types[i] >> names[i];
    }
    int index = 0;
    for(int i = 0; i < m; i++)
    {
        // 00          01         10         11
        // 内左顺时针, 内右逆时针, 外左逆时针, 外右顺时针
        // 0 是向左, 1 是向右
        int type, step;
        cin >> type >> step;
        // 顺时针, 减去
        if(type == types[index])
        {
            index -= step;
            index = ((index + n) % n + n) % n;
        } 
        else
        {
            index += step;
            index =  index % n;
        }
    }
    cout << names[index] << endl;
}
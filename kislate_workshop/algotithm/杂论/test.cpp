// 重写导弹拦截:
#include <bits/stdc++.h>
using namespace std;
int main(void)
{
    string line;
    getline(cin, line);
    int height;
    vector<int> heights;
    istringstream my_stream(line);
    while(my_stream >> height){
        heights.push_back(height);
    }
    vector<int> tail;
    for(int num : heights){
        auto it = upper_bound(tail.begin(), tail.end(), num, greater<int>());
        if(it == tail.end())
        {
            tail.push_back(num);
        }
        else{
            *it = num;
        }
    }
    int ans1 = tail.size();
    tail.clear();
    for(int num : heights){
        auto it = lower_bound(tail.begin(), tail.end(), num);
        if(it == tail.end())
        {
            tail.push_back(num);
        }
        else{
            *it = num;
        }
    }
    int ans2 = tail.size();
    cout << ans1 << endl; 
    cout << ans2 << endl;
    return 0;
}
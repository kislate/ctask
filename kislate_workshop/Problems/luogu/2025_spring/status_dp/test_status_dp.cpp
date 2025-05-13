#include<bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
ull max_weight, sum_people;
vector<pair<ull, ull>> peoples;
int main(void)
{
    cin >> max_weight >> sum_people;
    peoples.resize(sum_people + 1, {0, 0});
    // first 是时间, second 是重量
    for(int i = 1; i <= sum_people; i++) cin >> peoples[i].first >> peoples[i].second;
    sort(peoples.begin() + 1, peoples.end(), [](const pair<ull, ull>& a, const pair<ull, ull>& b) {
        if(a.first != b.first) return a.first > b.first;
        return a.second > b.second;
    });
    ull ans = 0;
    for(int i = 1; i <= sum_people; )
    {
        ull now_weight = 0, now_time = 0;
        bool flag = false;
        while(i <= sum_people && now_weight + peoples[i].second <= max_weight)
        {
            if(!flag && (peoples[i].first != 0 && peoples[i].second != 0)) now_time = peoples[i].first, flag = true;
            now_weight += peoples[i].second;
            peoples[i].first = 0, peoples[i].second = 0;
            i++;
        }
        int j = i;
        while(j <= sum_people)
        {
            if(now_weight + peoples[j].second > max_weight)
            {
                j++;
                continue;
            }
            now_weight += peoples[j].second;
            peoples[j].first = 0, peoples[j].second = 0;
            j++;
        }
        ans += now_time;
    }
    cout << ans << endl;
    return 0;
}
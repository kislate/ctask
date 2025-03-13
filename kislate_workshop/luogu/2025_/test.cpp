// Creator: kislate
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int main(void)
{
   int MAX_MONEY, SUM_GOODS;
   cin >> MAX_MONEY >> SUM_GOODS;
   vector<vector<pair<int, int>>> all_goods(SUM_GOODS + 1, vector<pair<int, int>>(3, make_pair(0, 0)));
   for(int i = 1; i <= SUM_GOODS; i++)
   {
        int price, value, type;
        cin >> price >> value >> type;
        if(type == 0)
        {
            all_goods[i][0].first = price;
            all_goods[i][0].second = value*price;
        }
        else
        {
            if(all_goods[type][1].first == 0)
            {
                all_goods[type][1].first = price;
                all_goods[type][1].second = value*price;
            }
            else
            {
                all_goods[type][2].first = price;
                all_goods[type][2].second = value*price;
            }
        }
   }
   vector<int> dp_value(MAX_MONEY + 1, 0);
    for(int i = 1; i <= SUM_GOODS; i++)
    {
        for(int j = MAX_MONEY; j >= 0; j--)
        {
            if(j >= all_goods[i][0].first)
            {
                dp_value[j] = max(dp_value[j], dp_value[j - all_goods[i][0].first] + all_goods[i][0].second);
            }
            if(j >= all_goods[i][0].first + all_goods[i][1].first)
            {
                dp_value[j] = max(dp_value[j], dp_value[j - all_goods[i][0].first - all_goods[i][1].first] + all_goods[i][0].second + all_goods[i][1].second);
            }
            if(j >= all_goods[i][0].first + all_goods[i][2].first)
            {
                dp_value[j] = max(dp_value[j], dp_value[j - all_goods[i][0].first - all_goods[i][2].first] + all_goods[i][0].second + all_goods[i][2].second);
            }
            if(j >= all_goods[i][0].first + all_goods[i][1].first + all_goods[i][2].first)
            {
                dp_value[j] = max(dp_value[j], dp_value[j - all_goods[i][0].first - all_goods[i][1].first - all_goods[i][2].first] + all_goods[i][0].second + all_goods[i][1].second + all_goods[i][2].second);
            }
            
        } 
    }
    cout << dp_value[MAX_MONEY] << endl;
}
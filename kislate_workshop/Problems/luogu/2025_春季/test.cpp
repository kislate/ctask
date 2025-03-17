#include <iostream>
#include <vector>
#include <queue>
typedef struct{
    int cost, gain, need;
}node;

using namespace std;

int main(void)
{
    int n;
    cin >> n;
    int sum_cost = 0;
    int sum_gain = 0;
    vector<node> nodes(n + 1);
    for (int i = 0; i < n+1; i++)
    {
        cin >> nodes[i].cost;
    }
    
}

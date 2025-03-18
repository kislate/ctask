#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct{
    int cost, gain, need, max_need_forward, max_need_backward, sum_cost, sum_gain;
}node;

int main(void)
{
    int n;
    cin >> n;
    vector<int> cost(n + 1);
    vector<int> gain(n);

    for (int i = 0; i < n + 1; ++i) cin >> cost[i];
    for (int i = 0; i < n; ++i) cin >> gain[i];

    vector<int> result(n);

    for (int i = 0; i < n; ++i) {
        int min_energy = cost[0];
        int current_energy = cost[0];

        for (int j = 0; j < n; ++j) {
            if (j == i) {
                current_energy -= cost[j+1];
            } else {
                current_energy += gain[j] - cost[j+1];
            }

            min_energy = min(min_energy, current_energy);
        }
        min_energy -= cost[n];

        result[i] = max(0, -min_energy);
    }

    for (int i = 0; i < n; ++i) {
        cout << result[i] << (i == n - 1 ? "" : " ");
    }
    cout << endl;

    return 0;
}
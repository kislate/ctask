#include <bits/stdc++.h>
using namespace std;
int main(void){
    int num_of_problems[4]; // 存储4科的题目数量
    int total_time[4] = {0}; // 每科题目的总时间
    for(int i = 0; i < 4; i++) cin >> num_of_problems[i];// 获取题目的数量
    vector<vector<int>> time(4, vector<int>(1000, 0));// 存储每道题的时间
    for(int i = 0; i < 4; i++) for(int j = 0; j < num_of_problems[i]; j++){
        cin >> time[i][j];// 获取每道题的时间
        total_time[i] += time[i][j]; // 计算总时间
    }
    int min_time = 0;// 最少的耗时
    vector<int> dp(100000, 0);// dp数组
    for(int i = 0; i < 4; i++)// 简化的一维线性动态规划
    {
        fill(dp.begin(), dp.end(), 0);
        for(int j = 0; j < num_of_problems[i]; j++)
        {
            for(int k = total_time[i]/2; k >= time[i][j]; k--)
            {
                dp[k] = max(dp[k], dp[k - time[i][j]] + time[i][j]);
            }
        }
        min_time += (total_time[i] - dp[total_time[i]/2]);
    }
    cout << min_time << endl;
    return 0;
}
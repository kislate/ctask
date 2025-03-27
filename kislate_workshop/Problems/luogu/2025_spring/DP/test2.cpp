#include <bits/stdc++.h>
using namespace std;
int main(void){
    int row, col;
    cin >> row >> col;
    vector<vector<int>> map_height(row+2, vector<int>(col+2, 0));
    priority_queue<int> hq;
    for(int i = 1; i <= row; i++) for(int j = 1; j <= col; j++) cin >> map_height[i][j];
    for(int i = 1; i <= row; i++)
    {
        for(int j = 1; j <= col; j++)
        {
            if(map_height[i+1][j] > map_height[i][j])    hq.push(map_height[i+1][j]);
            if(map_height[i-1][j] > map_height[i][j])    hq.push(map_height[i-1][j]);
            if(map_height[i][j+1] > map_height[i][j])    hq.push(map_height[i][j+1]);
            if(map_height[i][j-1] > map_height[i][j])    hq.push(map_height[i][j-1]);
        }
    }
    cout << hq.top() << endl;
    return 0;
}
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> tasks(n + 1);

    for(int i = 1; i <= n; i++)
    {
        int ci;
        cin >> ci;
        tasks[i].resize(ci);
        for(int j = 0 ; j < ci; j++)
        {
            cin >> tasks[i][j];
        }
    }
    vector<bool> visited(n + 1, false);
    queue<int> q;
    int count = 1;

    visited[1] = true;
    q.push(1);
    
    while(!q.empty())
    {
        int now = q.front();
        q.pop();
        for(int p : tasks[now])
        {
            if(!visited[p])
            {
                visited[p] = true;
                count++;
                q.push(p);
            }
        }
    }
    cout << count << endl;
}
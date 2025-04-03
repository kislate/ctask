#include <bits/stdc++.h>
using namespace std;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
int n;
vector<vector<int>> matrix, visited, mem;
bool search(int x, int y);
int main(void)
{
    cin >> n;
    matrix.resize(n + 1, vector<int>(n + 1, 0));
    visited.resize(n + 1, vector<int>(n + 1, 0));
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            cin >> matrix[i][j];
        }
    }
    for(int i = 2; i <= n-1; i++)
    {
        for(int j = 2; j <= n-1; j++)
        {
            visited[i][j] = 1;
            search(i, j);
            visited[i][j] = 0;
        }
    }
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
bool search(int x, int y)
{
    bool flag = true;
    if(matrix[x][y] == 1) return true;
    if(x == 1 || x == n || y == 1 || y == n) return false;
    visited[x][y] = 1;
    for(int i = 0; i < 4; i++)
    {
        int nx = x + dx[i], ny = y + dy[i];
        if(visited[nx][ny]) continue;
        visited[nx][ny] = 1;
        flag &= search(nx, ny);
        visited[nx][ny] = 0;
        if(flag == false) break;
    }
    if(flag) matrix[x][y] = 2;
    else matrix[x][y] = 0;
    return flag;
}

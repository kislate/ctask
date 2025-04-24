#include <bits/stdc++.h>
using namespace std;
double n, cnt = 0;
vector<pair<double, double>> cheeses;
vector<double> visited;
vector<vector<double>> predistance;
double cal_distanc(double x1, double x2)
{
    return sqrt((cheeses[x1].first - cheeses[x2].first) * (cheeses[x1].first - cheeses[x2].first) + (cheeses[x1].second - cheeses[x2].second) * (cheeses[x1].second - cheeses[x2].second));
}
double min_distance = 1e9;
void dfs(double x, double dis);
int main(void){
    cin >> n;
    cheeses.resize(n+1, {0, 0});
    visited.resize(n, 0);
    predistance.resize(n+1, vector<double>(n+1, 0));
    for(double i = 0; i < n; i++) cin >> cheeses[i].first >> cheeses[i].second;
    for(double i = 0; i <= n; i++)
        for(double j = 0; j <= n; j++)
            predistance[i][j] = cal_distanc(i, j);
    for(double i = 0; i < n; i++)
    {
        visited[i] = 1, cnt++;
        dfs(i, predistance[n][i]);
        visited[i] = 0, cnt--;
    }
    cout << fixed << setprecision(2) << min_distance << endl;
    return 0;
}
void dfs(double x, double dis)
{
    if(cnt == n)
    {
        min_distance = min(min_distance, dis);
        return;
    }
    for(double i = 0; i < n; i++)
    {
        if(visited[i] == 0)
        {
            double distance = predistance[x][i];
            if(dis + distance > min_distance) return;
            visited[i] = 1, cnt++;
            dfs(i, dis + distance);
            visited[i] = 0, cnt--;
        }
    }
}
#include <bits/stdc++.h>
using namespace std;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
int n, m;
vector<vector<int>> maze, memo;
void bfs(int x, int y) {
    vector<pair<int, int>> node;
    queue<pair<int, int>> pq;
    pq.push({x, y});
    memo[x][y] = -1; // 用-1标记正在访问
    while(!pq.empty()) {
        auto [cur_x, cur_y] = pq.front(); pq.pop();
        node.push_back({cur_x, cur_y});
        for (int d = 0; d < 4; ++d) {
            int nx = cur_x + dx[d], ny = cur_y + dy[d];
            if (nx >= 1 && nx <= n && ny >= 1 && ny <= n && !memo[nx][ny] && (maze[cur_x][cur_y] ^ maze[nx][ny])) {
                memo[nx][ny] = -1;
                pq.push({nx, ny});
            }
        }
    }
    int cnt = node.size();
    for (auto [vx, vy] : node) {
        memo[vx][vy] = cnt;
    }
    cout << cnt << '\n'; 
}

// 凹常数
int main(void) {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    maze.resize(n + 1, vector<int>(n + 1));
    memo.resize(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            char ch;
            cin >> ch;
            maze[i][j] = ch - '0';
        }
    }
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        if (memo[x][y] > 0) {
            cout << memo[x][y] << '\n';
            continue;
        }
        bfs(x, y);
    }
    return 0;
}
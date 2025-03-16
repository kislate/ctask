//已经老实
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    ios::sync_with_stdio(false);  // 禁用同步，加速输入输出
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> pre(n + 1);  // 前置任务列表

    // 读取输入
    for (int i = 1; i <= n; ++i) {
        int ci;
        cin >> ci;
        pre[i].resize(ci);
        for (int j = 0; j < ci; ++j) {
            cin >> pre[i][j];
        }
    }

    vector<bool> visited(n + 1, false);
    queue<int> q;
    int count = 1;  // 包含任务1

    q.push(1);
    visited[1] = true;

    // BFS 遍历
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        for (int p : pre[current]) {
            if (!visited[p]) {
                visited[p] = true;
                count++;
                q.push(p);
            }
        }
    }

    cout << count << endl;
    return 0;
}
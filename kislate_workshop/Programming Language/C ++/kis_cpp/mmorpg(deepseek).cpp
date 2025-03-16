#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);  // 关闭同步，加速输入输出
    cin.tie(nullptr);             // 进一步优化输入

    int n, m, k;
    cin >> n >> m >> k;

    vector<string> yesterday(n);
    unordered_set<string> completed;  // 用哈希集合存储“已完全发现的节点”
    vector<string> new_nodes(k);

    // 读取昨天派遣的节点
    for (int i = 0; i < n; ++i) {
        cin >> yesterday[i];
    }

    // 读取并存储“已完全发现的节点”
    string tmp;
    for (int i = 0; i < m; ++i) {
        cin >> tmp;
        completed.insert(tmp);  // O(1) 插入
    }

    // 读取新发现的节点
    for (int i = 0; i < k; ++i) {
        cin >> new_nodes[i];
    }

    vector<string> ans;
    ans.reserve(n + k);  // 预分配空间避免频繁扩容

    // 遍历昨天派遣的节点，保留未标记为“已完全发现”的节点
    for (const auto& node : yesterday) {
        if (!completed.count(node)) {  // O(1) 查找
            ans.push_back(node);
        }
    }

    // 加入新发现的节点
    ans.insert(ans.end(), new_nodes.begin(), new_nodes.end());

    // 按字典序排序并输出
    sort(ans.begin(), ans.end());
    for (const auto& node : ans) {
        cout << node << "\n";
    }

    return 0;
}
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    cin.ignore(); // 清除输入缓冲区的换行符

    // 创建哈希表，键为 string，值为 int
    unordered_map<string, int> dict;

    // 读取字典到哈希表
    for (int i = 0; i < n; ++i) {
        string key;
        int value;
        cin >> key >> value;
        dict[key] = value; // 插入键值对
    }

    cin.ignore(); // 清除换行符

    // 处理每个句子
    for (int i = 0; i < m; ++i) {
        string sentence;
        getline(cin, sentence); // 读取整行
        string output;

        size_t pos = 0;
        while (pos < sentence.size()) {
            size_t left = sentence.find('{', pos);
            if (left == string::npos) { // 没有找到左括号
                output += sentence.substr(pos);
                break;
            }
            output += sentence.substr(pos, left - pos); // 添加括号前的内容

            size_t right = sentence.find('}', left);
            if (right == string::npos) { // 没有找到右括号
                output += sentence.substr(left);
                break;
            }

            string key = sentence.substr(left + 1, right - left - 1); // 提取 {} 内的 key
            output += to_string(dict[key]); // 替换为哈希表中的值

            pos = right + 1; // 继续处理剩余部分
        }

        cout << output << endl;
    }

    return 0;
}
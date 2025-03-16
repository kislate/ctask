/*
向量（vector）
【题目描述】
现在给你 n 个 m 维向量，你先对每一个向量找一个所有维度都比他大的向量，如
果有多个这样的向量，则输出编号最小的。
【输入格式】
输入共 n + 1 行。
输入的第一行包含两个正整数 n 和 m，分别表示向量个数和维数。
接下来 n 行依次输入 m 个向量。
【输出格式】
输出共 n 行，每行一个整数，表示找到的向量编号，如果没有，输出 0 。
【样例 1 输入】
4 2
0 0
‐1 ‐1
1 2
0 ‐1
【样例 1 输出】
3
1
0
3
【子任务】
对于 100% 的测试数据，保证 0 < m ≤10，0 < n ≤1000，所有元素的绝对值均为
不大于 106 的整数。
*/
#include <iostream>
#include <vector>

using namespace std;
int main(void)
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> vectors(n, vector<int>(m));
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            cin >> vectors[i][j];
        }
    }

    for(int i = 0; i < n; i++){//
        bool flag = false;
        for(int j = 0; j < n; j++){//
            bool bigger = true;
            if(i == j)
                continue;
            for(int k = 0; k < m; k++){
                if(vectors[i][k] >= vectors[j][k]){
                    bigger = false;
                    break;
                }
            }
            if(bigger){
                cout << j+1 << endl;
                flag = true;
                break;
            }
        }//
        if(!flag)
            cout << 0 << endl;
    }//
    return 0;
}
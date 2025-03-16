/*
自助售货机（vem）
【题目描述】
你运营了一个自助售货机，售货机共有 n 层，每层 m 个货槽，每个货槽中放置一
种商品。
顾客购买商品后，对应货槽吐出商品，商品经过自由落体摔落到自助售货机的底部。
如果商品摆放在 .从 .下 .向 .上数第 i 层的货槽，商品的摔落距离即为 i。如果摔落距离过高，
则可能损坏商品。
现在小 F 需要安排 k(k ≤n ·m) 种商品在自助售货机上的摆放位置。第 i 种商品的
摔落距离不能超过 Hi。请你判断是否存在这样的一种摆放方式。
【输入格式】
输入共两行。
输入的第一行为三个正整数 n, m, k。
输入的第二行为 k 个正整数，第 i 个代表 Hi。
【输出格式】
输出一行一个字符串，表示是否存在合法的摆放方式：
• 若存在，输出 Yes。
• 若不存在，输出 No。
【样例 1 输入】
5 5 5
20 20 20 20 20
【样例 1 输出】
Yes
【样例 2 输入】
5 5 6
1 1 1 1 1 1
第 45 页 共 67 页
【样例 2 输出】
No
【子任务】
.本 .题 .使 .用 Subtask， .仅 .有 .通 .过 .该 Subtask .中 .全 .部 .的 .测 .试 .点 .方 .可 .获 .得 .该 Subtask
.的 .分 .数。
对于100% 的测试数据，1 ≤n, m ≤5000，1 ≤k ≤min{n ·m, 105}，1 ≤Hi ≤10000。
• Subtask 1(7 pts)：Hi = 1；
• Subtask 2(8 pts)：n = 1；
• Subtask 3(15 pts)：m = 1；
• Subtask 4(15 pts)：k ≤5000；
• Subtask 5(15 pts)：Hi 单调不降给出。
• Subtask 6(40 pts)：无特殊限制。
## hints
冒泡排序的时间复杂度为 O(n2)，一般来说，在时间限制为 1s 的情况下，只能通过
n ≤5000 的数据。
在本题中，你可能需要使用时间复杂度为 O(n logn) 的排序算法，你可以尝试搜索
sort 函数相关的资料，这是 C++ algorithm 头文件中提供的一个函数。
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(void)
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> Hights(k);
    for(int i = 0; i < k ; i++)
    {
        cin >> Hights[i];
    }
    sort(Hights.begin(), Hights.end());
    for(int i = 1; i <= n ; i++)
    {
        if(i*m >= k)
        {
            if(Hights[k-1] < i)
            {
                cout << "No" << endl;
                return 0;
            }
            else
            {
                cout << "Yes" << endl;
                return 0;
            }
        }
        if(Hights[i*m-1] < i)
        {
            cout << "No" << endl;
            return 0;
        }
    }
    cout << "Yes" << endl;
    return 0;
}
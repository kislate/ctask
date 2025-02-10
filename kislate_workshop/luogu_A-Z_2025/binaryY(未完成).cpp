/*
世界是一个巨大的二分（binary）
【题目描述】
小 F 会给出一个长度为 n 的数列 a，并进行以下五种询问：
• 1 x：查询数列中有多少个数 .刚 .好 .等 .于 x 。
• 2 x y：查询数列中有多少个数 .大 .于 .等 .于 x 并且 .小 .于 .等 .于 y 。
• 3 x y：查询数列中有多少个数 .大 .于 .等 .于 x 并且 .小 .于 y 。
• 4 x y：查询数列中有多少个数 .大 .于 x 并且 .小 .于 .等 .于 y 。
• 5 x y：查询数列中有多少个数 .大 .于 x 并且 .小 .于 y 。
【输入格式】
第一行读入两个整数 n, m，表示数列的长度为 n，一共有 m 次询问。
第二行读入 n 个整数表示数列 a。
接下来 m 行，每行输入 p x 或 p x y，表示一个询问，其中 p 表示询问类型。
【输出格式】
对于每次询问输出一行一个整数表示询问的答案。
【样例 1 输入】
6 6
3 ‐7 3 6 ‐2 3
1 3
1 999
2 ‐2 3
3 ‐2 3
4 ‐2 3
5 ‐2 3
【样例 1 输出】
3
0
4
1
3
0
【样例 2 输入】
5 1
0 0 0 50 105
5 100 1
【样例 2 输出】
1 0
【样例 3 输入】
5 1
0 50 50 50 105
5 100 1
【样例 3 输出】
0
【子任务】
对于 100% 的数据：1 ⩽n, m ⩽105, −109 ⩽ai, x, y ⩽109。
【hints】
如果你直接通过了本题，请尝试使用同一个自定义函数完成全部操作。
STL 为我们提供了二分查找的强大利器 lower_bound 函数与 upper_bound 函数，
请你自行查阅资料，学习前面两个函数的用法，并尝试使用这两个函数通过本题。
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void)
{
    int n, m;
    cin >> n >> m;
    vector<int> arr(n);
    for(int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    sort(arr.begin(), arr.end());
    for(int i = 0; i < m; i++)
    {
        int pro, x, y;//1 2 2 2 2 2 3 4 5 6 7 8 9 9 9 9 9 9 10
        cin >> pro;
        switch(pro)
        {
            case 1:
                cin >> x;
                cout << upper_bound(arr.begin(), arr.end(), x) - lower_bound(arr.begin(), arr.end(), x) << endl;
                break;
            case 2:// 大于等于x并且小于等于y
                cin >> x >> y;
                if(x > y)
                {
                    cout << 0 << endl;
                    break;
                }
                cout << upper_bound(arr.begin(), arr.end(), y) - lower_bound(arr.begin(), arr.end(), x) << endl;
                break;
            case 3:// 大于等于x并且小于y
                cin >> x >> y;
                if(x >= y)
                {
                    cout << 0 << endl;
                    break;
                }
                cout << lower_bound(arr.begin(), arr.end(), y) - lower_bound(arr.begin(), arr.end(), x) << endl;
                break;
            case 4:// 大于x并且小于等于y
                cin >> x >> y;
                if(x >= y)
                {
                    cout << 0 << endl;
                    break;
                }
                cout << upper_bound(arr.begin(), arr.end(), y) - upper_bound(arr.begin(), arr.end(), x) << endl;
                break;
            case 5:// 大于x并且小于y
                cin >> x >> y;
                if(x >= y)
                {
                    cout << 0 << endl;
                    break;
                }
                cout << lower_bound(arr.begin(), arr.end(), y) - upper_bound(arr.begin(), arr.end(), x) << endl;
                break;
        }
    }
}
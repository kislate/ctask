
/*
跳跃（jump）
【题目描述】
现在给你平面直角坐标系上的 m 个点 (xi, yi) , 现在让这些坐标做 n 次位移，每次
位移由两个参数 (dxi, dyi) 表示，将 (x, y) 变化为 (x + dxi, y + dyi) ，现在让你求出这 m
个点经过这 n 次位移之后的坐标。
【输入格式】
输入共 n + m + 1 行。
输入的第一行包含空格分隔的两个正整数 n 和 m，分别表示位移和点个数。
接下来 n 行依次输入 n 个操作，其中第 i(1 ≤i ≤n) 行包含空格分隔的两个整数
dxi、dyi。
接下来 m 行依次输入 m 个坐标，其中第 i(1 ≤i ≤m) 行包含空格分隔的两个整数
xi、yi。
【输出格式】
输出共 m 行，每行两个整数，表示经过位移变化后的坐标。
【样例 1 输入】
3 2
10 10
0 0
10 ‐20
1 ‐1
0 0
【样例 1 输出】
21 ‐11
20 ‐10
【子任务】
对于 100% 的测试数据，1 ≤n, m ≤100，x, y, dx, dy 均为整数且绝对值不超过
10000。
第 51 页 共 67 页
*/
#include <iostream>

using namespace std;

int main(void)
{
    int n, m;
    cin >> n >> m;
    int dx =0, dy = 0;
    for(int i = 0; i < n; i++)
    {
        int dx_part, dy_part;
        cin >> dx_part >> dy_part;
        dx += dx_part;
        dy += dy_part;
    }
    for(int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        cout << x + dx << " "<< y + dy << endl;
    }
}
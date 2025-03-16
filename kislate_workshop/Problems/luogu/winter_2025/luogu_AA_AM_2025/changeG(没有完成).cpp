/*
变换（change）
【题目描述】
对于平面直角坐标系上的点(x, y) , 我们现在有两种坐标变换的方法，方法一是拉伸
k 倍，把坐标变换成(kx, ky)，方法二是通过旋转θ，把坐标变换为(x cosθ−y sinθ, x sinθ+
y cosθ)。其中，θ 的单位为 rad。
现在有一个包含了 n 个坐标变换的序列 (t1, t2, t3, ..., tn) ，其中 ti 表示了一个坐
标变换, 然后现在又定义了一个询问，给定 (i, j, x, y) 四元组，询问坐标 (x, y) 经过
(ti, ti+1, ..., tj ) 坐标变换后的坐标, 共有 m 个这样的询问, 计算出每个询问的结果。
【输入格式】
输入共 n + m + 1 行。
输入的第一行包含空格分隔的两个正整数 n 和 m，分别表示坐标变换和询问个数。
接下来 n 行依次输入 n 个坐标变换，第一个数表示采用的方法 (1 表示拉伸，2 表
示旋转)，第二个实数表示 k 或 θ
接下来 m 行依次输入 m 个询问，每行包含空格分隔的四个整数 i, j, x, y。
【输出格式】
输出共 m 行，每行两个实数，表示经过位移变化后的坐标, 需要保证绝对误差不大
于 0.1。
【样例 1 输入】
10 5
2 0.59
2 4.956
1 0.997
1 1.364
1 1.242
1 0.82
2 2.824
1 0.716
2 0.178
2 4.094
1 6 ‐953188 ‐946637
1 9 969538 848081
4 7 ‐114758 522223
1 9 ‐535079 601597
8 8 159430 ‐511187
【样例 1 输出】
‐1858706.758 ‐83259.993
‐1261428.46 201113.678
‐75099.123 ‐738950.159
‐119179.897 ‐789457.532
114151.88 ‐366009.892
【子任务】
对于100% 的测试数据，0 ≤n, m ≤100000，x, y 均为整数且绝对值不超过1000000，
单个拉伸操作系数 0.5 ≤k ≤2，任意区间的拉伸系数 k 的乘积满足 0.001 ≤k ≤1000。
【提示】
前缀和、前缀积及其思想是处理区间可加性问题的利器，请自行查阅资料学习。
在本题中，容易发现拉伸和旋转两种操作顺序无关，可对拉伸和旋转分别应用前缀
积、前缀和处理。
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
int main(void)
{
    int n, m;
    cin >> n >> m;
    vector<long double> prefix_product(n+1, 1.0), prefix_rotate(n+1, 0.0);
    for(int i = 1; i <= n; i ++)
    {
        long double type, value;
        cin >> type >> value;
        if(type == 1)
        {
            prefix_product[i] = prefix_product[i-1] * value;
            prefix_rotate[i] = prefix_rotate[i-1];
        }
        else
        {
            prefix_product[i] = prefix_product[i-1];
            prefix_rotate[i] = prefix_rotate[i-1] + value;
        }
    }
    for(int i = 0; i < m; i++)
    {
        int l, r, x, y;
        cin >> l >> r >> x >> y;
        long double x1 = x * prefix_product[r] / prefix_product[l-1];
        long double y1 = y * prefix_product[r] / prefix_product[l-1];
        long double rotate = prefix_rotate[r] - prefix_rotate[l-1];
        long double new_x = x1 * cos(rotate) - y1 * sin(rotate);
        long double new_y = x1 * sin(rotate) + y1 * cos(rotate);
        printf("%.3Lf %.3Lf\n", new_x, new_y);
    }
}


//Gemini 2.0
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<pair<int, double>> transformations(n);
    for (int i = 0; i < n; ++i) {
        cin >> transformations[i].first >> transformations[i].second;
    }

    for (int i = 0; i < m; ++i) {
        int start, end, x, y;
        cin >> start >> end >> x >> y;
        start--; // Adjust to 0-based indexing
        end--;   // Adjust to 0-based indexing

        double current_x = x;
        double current_y = y;

        for (int j = start; j <= end; ++j) {
            if (transformations[j].first == 1) {
                // Scale transformation
                current_x *= transformations[j].second;
                current_y *= transformations[j].second;
            } else {
                // Rotation transformation
                double theta = transformations[j].second;
                double new_x = current_x * cos(theta) - current_y * sin(theta);
                double new_y = current_x * sin(theta) + current_y * cos(theta);
                current_x = new_x;
                current_y = new_y;
            }
        }

        cout << fixed << setprecision(3) << current_x << " " << current_y << endl;
    }

    return 0;
}

/*

你是对的，逐个应用变换在最坏情况下复杂度为 O(n*m), 其中 n 是变换的数量，m 是查询的数量。 优化的方向是要将区间查询问题，转换成数据预处理，一次计算结果，之后只用合并就可以，避免每一次进行很多次的重复计算。这道题目不能够完全使用前缀和与前缀积，可以尝试矩阵运算与矩阵快速幂。

但是，因为这里n, m 的数据量是 n, m ≤100000, 单纯这样优化可能收益不高。因此更好的方法是用上 分块思想。

基本思路：

分块: 将 n 个变换分成 sqrt(n) 块。

预处理块信息: 预先计算好每一块的累积变换（先进行块内的所有旋转变换，然后累乘所有缩放系数）。

处理查询: 对于每一个查询 (i, j, x, y)：

找到 i 和 j 所属的块。

对于完全包含在 (i, j) 范围内的块，直接应用预处理好的累积变换。

对于 i 和 j 所在的残余块，顺序应用变换。

分块的优势是能够在预处理和查询之间做一个权衡。 预处理花费 O(n * sqrt(n)) 的时间（因为计算每一块的累积变换需要遍历块内的变换）。 每个查询需要的时间最多为 O(sqrt(n))（至多 2 个残余块，每个长度不超过 sqrt(n)，以及完全覆盖的块也是 O(sqrt(n))）。总体复杂度变成 O(n*sqrt(n) + m * sqrt(n))，可能降低总体的运行时间。
如果实际运行后效果还不佳，再去尝试矩阵，以及相关更加复杂的算法。

下面给出核心代码实现的例子，假设sqrtSize代表每一块的大小。

// 预处理:计算每一块的累积变换
    int sqrtSize = sqrt(n);
    vector<pair<double, double>> blockTransformations(n / sqrtSize + 1, {1.0, 0.0}); // (scale, rotate)

    for (int blockIdx = 0; blockIdx <= n / sqrtSize; ++blockIdx) {
        double scale = 1.0;
        double rotate = 0.0;
        int blockStart = blockIdx * sqrtSize;
        int blockEnd = min((blockIdx + 1) * sqrtSize, n);

        for (int i = blockStart; i < blockEnd; ++i) {
            if (transformations[i].first == 1) {
                scale *= transformations[i].second;
            } else {
                rotate += transformations[i].second;
            }
        }
        blockTransformations[blockIdx] = {scale, rotate};
    }
//查询的部分，用累积的结果。
// 计算横跨块的变换
        double current_x = x;
        double current_y = y;

        int startBlock = start / sqrtSize;
        int endBlock = end / sqrtSize;

        // 处理起始块内的残余部分
        for (int j = start; j < (startBlock + 1) * sqrtSize && j <= end; ++j) {
            if (transformations[j].first == 1) {
                current_x *= transformations[j].second;
                current_y *= transformations[j].second;
            } else {
                double theta = transformations[j].second;
                double new_x = current_x * cos(theta) - current_y * sin(theta);
                double new_y = current_x * sin(theta) + current_y * cos(theta);
                current_x = new_x;
                current_y = new_y;
            }
        }
// 使用块转换处理中间完全包含的块
        for (int blockIdx = startBlock + 1; blockIdx < endBlock; ++blockIdx) {
            double scale = blockTransformations[blockIdx].first;
            double rotate = blockTransformations[blockIdx].second;

            current_x *= scale;
            current_y *= scale;

            double new_x = current_x * cos(rotate) - current_y * sin(rotate);
            double new_y = current_x * sin(rotate) + current_y * cos(rotate);
            current_x = new_x;
            current_y = new_y;

        }

                // 处理末尾块内的残余部分
        for (int j = endBlock * sqrtSize; j <= end; ++j) {
            if (transformations[j].first == 1) {
                current_x *= transformations[j].second;
                current_y *= transformations[j].second;
            } else {
                double theta = transformations[j].second;
                double new_x = current_x * cos(theta) - current_y * sin(theta);
                double new_y = current_x * sin(theta) + current_y * cos(theta);
                current_x = new_x;
                current_y = new_y;
            }
        }
Use code with caution.
C++
完整实现的代码比较复杂，需要实现好分块相关的操作和累积信息的记录，并需要进行比较仔细的调试来确保结果正确， 如果使用有难度可以逐个击破， 如果遇到其他问题可以继续提出， 希望能够帮助到你。
*/
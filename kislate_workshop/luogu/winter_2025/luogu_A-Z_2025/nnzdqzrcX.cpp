/*大物要挂了（nnzdqzrc）
【题目描述】
期末到了，盖亚开始搞学习了。于是在“你能做的，岂止如此”的恐吓下，盖亚开
始刷习题集，每科都有一个习题集，一共有四科，分别有 s1, s2, s3, s4 道题目。虽然盖
亚已经完成了超进化，但是完成每道题目都需要一些时间，这些时间并不相等，分别用
Ai, Bi, Ci, Di 表示。
盖亚有一个能力，他可以拉雷伊过来做题，于是他可以同时计算 2 道不同的题目，
但是仅限于同一科。因此，盖亚必须一科一科的复习。
因为大二下要到了，因此盖亚非常急，希望在不挂科的情况下尽快把事情做完，所
以他希望知道能够完成复习的最短时间。
【输入格式】
本题包含 5 行数据：第 1 行，为四个正整数 s1, s2, s3, s4。
第 2 行，为 A1, A2, . . . , As1 共 s1 个数，表示第一科习题集每道题目所消耗的时间。
第 3 行，为 B1, B2, . . . , Bs2 共 s2 个数。
第 4 行，为 C1, C2, . . . , Cs3 共 s3 个数。
第 5 行，为 D1, D2, . . . , Ds4 共 s4 个数，意思均同上。
【输出格式】
输出一行，为盖亚复习完毕最短时间。
【样例 1 输入】
1 2 1 3
5
4 3
6
2 4 3
【样例 1 输出】
20
【子任务】
数据保证：1 ≤s1, s2, s3, s4 ≤20，1 ≤Ai, Bi, Ci, Di ≤60。
*/


// 上面的是错误的，下面的是正确的
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int mintime_Calculation(vector<int>& sorted_Arr, int index);
void build_Sort_Vector(vector<int>& a,int index);
int main(void)
{
    int s1, s2, s3, s4;
    cin >> s1 >> s2 >> s3 >> s4;
    vector<int> A(s1), B(s2), C(s3), D(s4);
    build_Sort_Vector(A, s1);
    build_Sort_Vector(B, s2);
    build_Sort_Vector(C, s3);
    build_Sort_Vector(D, s4);
    int mintime = 0;
    int mintimeA = mintime_Calculation(A, s1);
    int mintimeB = mintime_Calculation(B, s2);
    int mintimeC = mintime_Calculation(C, s3);
    int mintimeD = mintime_Calculation(D, s4);
    mintime = mintimeA + mintimeB + mintimeC + mintimeD;
    cout << mintime << endl;
    return 0;
}

int mintime_Calculation(vector<int>& sorted_Arr, int index)
{
    int sum = 0;
    for(int i = 0 ; i < index; i++)
    {
        sum += sorted_Arr[i];
    }
    float mid_time = sum / 2.0;
    int time = 0;
    for(int i = 0; i < index; i++)
    {
        time += sorted_Arr[i];
        if(time >= mid_time)
        {
            return min(time, sum-(time - sorted_Arr[i]));
        }
    }
}

void build_Sort_Vector(vector<int>& a,int index)
{
    for(int i = 0; i < index; i++)
    {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
}


#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int min(int a, int b) {
    return a < b ? a : b;
}

int mintime_Calculation(vector<int>& sorted_Arr, int index) {
    int sum = 0;
    for (int i = 0; i < index; i++) {
        sum += sorted_Arr[i];
    }

    int half = sum / 2;
    vector<int> dp(half + 1, 0);

    for (int i = 0; i < index; i++) {
        //这里类比0-1背包问题，里边的重量和价值都是sorted_Arr[i]，都相等的意思
        for (int j = half; j >= sorted_Arr[i]; j--) {
            dp[j] = max(dp[j], dp[j - sorted_Arr[i]] + sorted_Arr[i]);
        }
    }

    return sum - dp[half];
}

void build_Sort_Vector(vector<int>& a, int index) {
    for (int i = 0; i < index; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
}

int main(void) {
    int s1, s2, s3, s4;
    cin >> s1 >> s2 >> s3 >> s4;
    vector<int> A(s1), B(s2), C(s3), D(s4);
    build_Sort_Vector(A, s1);
    build_Sort_Vector(B, s2);
    build_Sort_Vector(C, s3);
    build_Sort_Vector(D, s4);

    int mintime = 0;
    int mintimeA = mintime_Calculation(A, s1);
    int mintimeB = mintime_Calculation(B, s2);
    int mintimeC = mintime_Calculation(C, s3);
    int mintimeD = mintime_Calculation(D, s4);
    mintime = mintimeA + mintimeB + mintimeC + mintimeD;

    cout << mintime << endl;
    return 0;
}



//下面是暴力解法 
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 计算每科的最短时间（穷举法）
int calculateMinTime(const vector<int>& tasks, int count) {
    int total = 0;
    for (int t : tasks) total += t;
    int half = total / 2;
    int best = 0;

    // 遍历所有可能的子集组合（位运算）
    for (int mask = 0; mask < (1 << count); mask++) {
        int sum = 0;
        for (int i = 0; i < count; i++) {
            if (mask & (1 << i)) { // 检查第i位是否为1
                sum += tasks[i];
            }
        }
        if (sum <= half && sum > best) {
            best = sum; // 更新最佳值
        }
    }

    return total - best; // 较大组的时间
}

// 读取输入并排序（从大到小）
void readAndSort(vector<int>& tasks, int count) {
    for (int i = 0; i < count; i++) {
        cin >> tasks[i];
    }
    sort(tasks.begin(), tasks.end(), greater<int>());
}

int main() {
    int s1, s2, s3, s4;
    cin >> s1 >> s2 >> s3 >> s4;

    vector<int> A(s1), B(s2), C(s3), D(s4);
    readAndSort(A, s1);
    readAndSort(B, s2);
    readAndSort(C, s3);
    readAndSort(D, s4);

    // 计算各科时间
    int timeA = calculateMinTime(A, s1);
    int timeB = calculateMinTime(B, s2);
    int timeC = calculateMinTime(C, s3);
    int timeD = calculateMinTime(D, s4);

    // 总时间
    cout << timeA + timeB + timeC + timeD << endl;

    return 0;
}
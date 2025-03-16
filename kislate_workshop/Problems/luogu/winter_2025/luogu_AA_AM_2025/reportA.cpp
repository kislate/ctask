/*
IT 中国课程报告（report）
【题目描述】
你的桌子被沁苑鼠鼠啃坏了！但是现在是 1 月 17 日 23:00，距离 IT 中国报告截止
还有 1 小时，你必须找一块平整的地方来放置电脑撰写报告。
你决定用你的书摞起书堆，直到书堆 .不 .低 .于你的身高。你一共有 N 本书，第 i 本
书的厚度为 Hi，你的身高为 B。
显而易见，书的数目越多，书堆越不稳定。请问你至少使用多少本书，可以达到目
标。
【输入格式】
输入共两行。
输入的第一行为两个正整数 N, B。
输入的第二行为 N 个正整数，第 i 个代表 Hi。
【输出格式】
输出一行一个整数，表示最少使用的书的本数。
【样例 1 输入】
6 40
6
18
11
13
19
11
【样例 1 输出】
3
【子任务】
对于100% 的测试数据，1 ≤N ≤20000，1 ≤Hi ≤10000，1 ≤B ≤∑ Hi ≤2×109。
第 44 页 共 67 页
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(void){
    int N, B;
    cin >> N >> B;
    vector<int> Hights(N);
    for(int i = 0; i < N; i++){
        cin >> Hights[i];
    }
    sort(Hights.begin(), Hights.end());
    int sum_Height = 0;
    int cnt = 0;
    for(int i = N-1; i >= 0; i--)
    {
        sum_Height +=Hights[i];
        cnt++;
        if(sum_Height >=B)
            break;
    }
    printf("%d\n",cnt);
    return 0;
}

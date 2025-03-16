/*
图案重现（pattern）
【题目描述】
现在给你 n 个 8 ×8 的字符矩阵, 仅由大小写的 *、k、q、r、b、n、q 组成，你需
要判断第 i 个字符矩阵在之前出现过几次。
【输入格式】
输入共 8 ·n + 1 行。
输入的第一行包含两个正整数 n ，分别表示有 n 个字符矩阵。
接下来 8 ·n 行, 依次表示这 n 个字符矩阵。
【输出格式】
输出共 n 行，表示这个字符矩阵是第几次出现。
【样例 1 输入】
8
********
******pk
*****r*p
p*pQ****
********
**b*B*PP
****qP**
**R***K*
********
******pk
*****r*p
p*pQ****
*b******
****B*PP
****qP**
**R***K*
********
******pk
*****r*p
p*p*****
*b**Q***
****B*PP
****qP**
**R***K*
******k*
******p*
*****r*p
p*p*****
*b**Q***
****B*PP
****qP**
**R***K*
******k*
******p*
*****r*p
p*pQ****
*b******
****B*PP
****qP**
**R***K*
********
******pk
*****r*p
p*pQ****
*b******
****B*PP
****qP**
**R***K*
********
******pk
*****r*p
p*p*****
*b**Q***
****B*PP
****qP**
**R***K*
********
******pk
******rp
p*p*****
*b**Q***
****B*PP
****qP**
**R***K*s
【样例 1 输出】
1
1
1
1
1
2
2
1
【子任务】
对于 100% 的测试数据，1 ≤n ≤100。
【hints】
可用字符串哈希进行判断。
亦可以使用 STL 提供的 map、set、unordered_map 等容器进行去重，请自行查找
资料学习。
第 56 页 共 67 页
*/
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;
int main(void)
{
    int n;
    cin >> n;
    cin.ignore();

    unordered_map<string, int> pattern_map;
    for(int i = 0; i < n; i++)
    {
        string pattern, temp;
        for(int j = 0; j < 8; j++)
        {
            //getline(cin, temp);
            cin >> temp;//getline不通过可能是因为输入的数据有问题
            pattern += temp;
        }
        if(!pattern_map.count(pattern))
        {
            pattern_map[pattern] =1;
        }
        else
        {
            pattern_map[pattern]++;
        }
        cout << pattern_map[pattern] << endl;
    }
    return 0;
}
/*
选择（choose）
【题目描述】
给你 n 个数和一个整数 k。
问有你有多少种方法从 n 个数里面选 k 个数使得和为质数？
【输入格式】
第一行两个空格隔开的整数 n, k。
第二行 n 个整数，分别为 x1, x2, ···, xn。
【输出格式】
输出一个整数，表示种类数。
【样例 1 输入】
4 3
3 7 12 19
【样例 1 输出】
1
【子任务】
数据保证：1 ≤n ≤20，k < n，1 ≤xi ≤5 ×106。
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
bool isPrime(int n){
    if(n==1)
        return false;
    for(int i = 2; i < sqrt(n); i++){
        if(n%i == 0)
            return false;
    }
    return true;
}

void countCombinationPrime(vector<int>&array, int n, int k, int& ret, int sum, int index){
    if(k == 0){
        if(isPrime(sum))
            ret++;
        return;
    }
    for(int i = index; i < n; i++){
        countCombinationPrime(array, n, k - 1, ret, sum + array[i], i + 1);
    }
}
int main(void){
    int n, k;
    cin >> n >> k;
    vector<int> array(n);
    for(int i = 0; i < n; i++){
        cin >> array[i];
    }
    int ret = 0;
    countCombinationPrime(array, n, k, ret, 0, 0);
    printf("%d\n", ret);
    return 0;
}
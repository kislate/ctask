/*
矩阵加速（matrix）
【题目描述】
假设有数列 f ，f (i) 为数列的第 i 项，f (i) = a ·f (i −1) + b ·f (i −2) + c(i > 2)。
求 f (n)，由于答案可能很大，只需要输出答案对 998244353 取模的结果。
【输入格式】
输入共三行。
输入的第一行为一个正整数 n。
输入的第二行为两个正整数，依次表示 f (1), f (2)。
输入的第三行为三个非负整数 a, b, c。
【输出格式】
输出一行一个整数，表示答案。
【样例 1 输入】
4
2 2
1 2 3
【样例 1 输出】
16
【子任务】
对于 100% 的测试数据，1 ≤n ≤1018，1 ≤f (1), f (2) < 998244353，0 ≤a, b, c <
998244343。
【hints】
计算 ab，存在 O(logb) 的算法，请自行查找资料学习 .快 .速 .幂算法。
假设 A 是 n 阶方阵，Ak 亦可使用快速幂计算，只需要将快速幂中的普通乘法全部
换为矩阵乘法。
有递推公式，f (i) = a ·f (i −1) + b ·f (i −2) + c，我们可以用矩阵来表示这个递推
式。 [
f (i) f (i −1) c
]T
= A ×
[
f (i −1) f (i −2) c
]T
容易发现，A 一定是一个 3 ×3 的方阵，那么核心就是得到 A，请自行进行推导。
求出 A 后，容易得到，
[
f (n) f (n −1) c
]T
= An−2 ×
[
f (2) f (1) c
]T
即可在 O(Σ2 logn) 的时间复杂度求得答案，其中 Σ 代表 A 的阶。
*/

/*超时的答案：
#include <iostream>
using namespace std;

int memery[100000000] = {-1};
long long f(long long n,long long f1,long long f2,long long a,long long b,long long c){
    if(memery[n] != -1)
        return memery[n];
    if(n == 1)
        return f1;
    if(n == 2)
        return f2;
    return memery[n] = (a*f(n-1,f1,f2,a,b,c)%998244353 + b*f(n-2,f1,f2,a,b,c)%998244353 + c)%998244353;
}
int main(void)
{
    long long n, f1, f2, a, b, c;
    cin >> n >> f1 >> f2 >> a >> b >> c;
    long long ans = f(n, f1, f2, a, b, c);
    cout << ans%998244353 << endl;
    return 0;
}
*/

/*
A=
[a, b, 1]
[1, 0, 0]
[0, 0, 1]

A^n = 
*/
#include <iostream>
#include <array>
#include <algorithm>
using namespace std;

typedef array<array<long long, 3>, 3> Matrix;//3 *3 
const long long MOD = 998244353;
Matrix multiply_Matrix(const Matrix &A, const Matrix &B){
    Matrix C;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            C[i][j] = 0;
            for(int k = 0; k < 3; k++)
            {
                C[i][j] += (A[i][k]%MOD) * (B[k][j]%MOD);
                C[i][j] %= MOD;
            }
        }
    }
    return C;
}
Matrix pow_Matrix(Matrix A, long long n){
    Matrix ret;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            ret[i][j] = (i == j);
        }
    }
    while(n > 0)
    {
        if(n & 1)
            ret = multiply_Matrix(ret, A);
        A = multiply_Matrix(A, A);
        n /= 2;
    }
    return ret;
}
int main(void)
{
    long long n, f1, f2, a, b, c;
    cin >> n >> f1 >> f2 >> a >> b >> c;
    Matrix A = {a, b, 1, 1, 0, 0, 0, 0, 1};
    Matrix B = pow_Matrix(A, n-2);
    long long ans = (B[0][0]*f2%MOD + B[0][1]*f1%MOD + B[0][2]*c%MOD)%MOD;
    cout << ans << endl;
}
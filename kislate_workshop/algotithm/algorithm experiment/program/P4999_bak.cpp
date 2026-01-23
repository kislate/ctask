#include <bits/stdc++.h>
#define MOD 1000000007
// 优化方向；
/*
1.用前缀和记忆化（感觉map更好）
2.数位dp 求出每个数出现的次数然后直接求解
*/
using namespace std;
vector<vector<long long>> table(100, vector<long long>(100, 0));
vector<long long> digs(100);
long long digit_sum(long long num) {
    long long sum = 0;
    while(num) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}
void generate_table(){
    for (long long i = 0; i < 100; ++i) table[i][i] = digs[i];
    for (long long i = 1; i < 100; ++i) table[0][i] = table[0][i - 1] + digs[i];
    for (long long i = 1; i < 100; ++i) {
        for (long long j = i + 1; j < 100; ++j) {
            table[i][j] = table[i - 1][j] - digs[i - 1];
        }
    }
}
long long query(long long l, long long r) {
    if (l > r) return 0;
    long long low = l % 100, hight = r % 100;
    long long low_block = l / 100, hight_block = r / 100;
    // cout << low_block << " " << hight_block << endl;
    // if (low_block == hight_block) return (table[low][hight] + low_block * (hight - low + 1) % MOD) % MOD;
    // // else if (hight_block - low_block == 1) return table[low][99] + low_block * (99 - low + 1) + table[0][hight] + hight_block * (hight + 1);
    // else return (table[low][99] + low_block * (99 - low + 1) % MOD + table[0][hight] + hight_block * (hight + 1) % MOD +
    //         ((hight_block - low_block - 1) % MOD) * ((hight_block + low_block) % MOD) * 500000004 * 100 + ((hight_block - low_block - 1) % MOD) * table[0][99]) % MOD;
    if (low_block == hight_block) return (table[low][hight] + digit_sum(low_block) * (hight - low + 1) % MOD) % MOD;
    //else if (hight_block - low_block == 1) return table[low][99] + low_block * (99 - low + 1) + table[0][hight] + hight_block * (hight + 1);
    else return (table[low][99] + digit_sum(low_block) * (99 - low + 1) % MOD + table[0][hight] + digit_sum(hight_block) * (hight + 1) % MOD +
                (query(low_block + 1, hight_block - 1) * 100 % MOD) + ((hight_block - low_block - 1) % MOD) * table[0][99] % MOD) % MOD; 
}
int main(void) {
    ios::sync_with_stdio(false); cin.tie(0);

    // precompute
    for(long long i = 0; i < 100; ++i) digs[i] = digit_sum(i);
    generate_table();
    long long Q; cin >> Q;
    while(Q--) {
        long long l, r;
        cin >> l >> r;
        cout << query(l, r) << endl;
    }
    return 0;
}

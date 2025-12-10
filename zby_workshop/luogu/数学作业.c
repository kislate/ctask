#include <stdio.h>
#include <inttypes.h>

const long long MOD = 1000000007LL;

long long mod_mul(long long a, long long b) {
    __int128 t = (__int128)a * b;
    t %= MOD;
    return (long long)t;
}

long long F(unsigned long long N) {
    if (N == (unsigned long long)(-1)) return 0; // not used, safe-guard
    long long res = 0;
    unsigned long long ten = 1;
    for (int p = 0; ; p++) {
        unsigned long long tenp1 = ten * 10ULL;
        if (ten > N && tenp1 > N) {
            // if ten > N, further positions will have high=0, cur=0, low=N -> contributions zero
            // but we still need to break when ten > N to avoid overflow in ten*10
            break;
        }
        unsigned long long high = N / tenp1;
        unsigned long long cur = (N / ten) % 10ULL;
        unsigned long long low = N % ten;

        // term1 = high * ten * 45
        long long term1 = mod_mul((long long)(high % MOD), (long long)(ten % MOD));
        term1 = mod_mul(term1, 45LL);

        // term2 = ten * cur*(cur-1)/2
        long long cur_ll = (long long)cur;
        long long c2 = (cur_ll * (cur_ll - 1) / 2) % MOD; // small, no overflow
        long long term2 = mod_mul((long long)(ten % MOD), c2);

        // term3 = cur * (low + 1)
        long long term3 = mod_mul((long long)(cur % MOD), (long long)((low + 1ULL) % MOD));

        res += term1;
        if (res >= MOD) res -= MOD;
        res += term2;
        if (res >= MOD) res -= MOD;
        res += term3;
        if (res >= MOD) res -= MOD;

        // prepare next position
        if (ten > (unsigned long long)(~0ULL / 10ULL)) break; // avoid overflow
        ten = tenp1;
        if (ten > N && high == 0 && cur == 0) break;
    }
    return res % MOD;
}

int main() {
    int T;
    if (scanf("%d", &T) != 1) return 0;
    while (T--) {
        unsigned long long L, R;
        scanf("%llu %llu", &L, &R);
        long long FR = F(R);
        long long FLm1 = (L == 0) ? 0 : F(L - 1);
        long long ans = FR - FLm1;
        ans %= MOD;
        if (ans < 0) ans += MOD;
        printf("%lld\n", ans);
    }
    return 0;
}

###### 前言：能够使用`C/C++`的时候尽量不要使用`python`
### 预素数表（具体逻辑尚未清楚）
```c
// Sieve of Eratosthenes 来生成素数
// 这个狗算法，我还以为是基于某个高深数学原理，原来是提前只进行一次素数判断
// 或许哥德巴赫有机会（确信
void sieve() {
    char is_prime[MAX_PRIME + 1];
    for (int i = 2; i <= MAX_PRIME; i++) is_prime[i] = 1; //Initialize array

    for (int p = 2; p * p <= MAX_PRIME; p++) {
        if (is_prime[p]) {
            for (int i = p * p; i <= MAX_PRIME; i += p) {
                is_prime[i] = 0;
            }
        }
    }
    for (int p = 2; p <= MAX_PRIME; p++) {
        if (is_prime[p]) {
            primes[prime_count++] = p;
        }
    }
}
```

*具体实现逻辑如下(待补充)*:
```
(待补充)
```

### 这是`洛谷_winter`中出现的一道题：
```c
/*
有意义的组成部分（meaningless）
【题目描述】
已知每个数都可以通过唯一分解定理分解成若干个质数相乘的形式, 形如 a = pa1
1 ×
pa2
2 ×... ×pan
n , 现在我们想求出通过分解 a，忽略的指数小于 k 的质数，剩下数的乘积。
【输入格式】
输入共 q + 1 行
输入的第一行包含一个正整数 q ，表示询问个数
接下来 q 行每行包含两个整数 a , k 表示一个询问
【输出格式】
输出共 q 行，每行一个整数，表示所求的数。
【样例 1 输入】
3
2155895064 3
2 2
10000000000 10
【样例 1 输出】
2238728
1
10000000000
【子任务】
对于 100% 的测试数据，1 < k, q ≤10，0 < a ≤1010。
第 50 页 共 67 页
*/
#include <stdio.h>

#define MAX_PRIME 1000000

int primes[MAX_PRIME + 1];
int prime_count = 0;

void sieve() {
    char is_prime[MAX_PRIME + 1];
    for (int i = 2; i <= MAX_PRIME; i++)
        is_prime[i] = 1;

    for (int p = 2; p * p <= MAX_PRIME; p++) {
        if (is_prime[p]) {
            for (int i = p * p; i <= MAX_PRIME; i += p) {
                is_prime[i] = 0;
            }
        }
    }
    for (int p = 2; p <= MAX_PRIME; p++) {
        if (is_prime[p]) {
            primes[prime_count++] = p;
        }
    }
}

void find_prime_Meaningless(long long num,  int k)
{
    long long ret = num;
    long long temp = num;
    long long origin = num;
    for(int i = 0; i < prime_count && (long long)primes[i] * primes[i] <= origin; i++) // Correction is Here : i=0!
    {
        long long prime = primes[i];
        long long count = 0;
        if( num % prime == 0)
        {
            while( num % prime == 0)
            {
                count++;
                num /= prime;
                temp /= prime;
            }
            if( count < k)
            {
                ret = temp;
            }
            else
            {
                temp = ret;
            }
        }
    }
    if (num > 1 ) {
        ret /= num;
    }
    printf("%lld\n", ret);
}

int main(void)
{
    sieve();
    int q;
    scanf("%d", &q);
    for(int i = 0; i < q; i++)
    {
        long long a, k;
        scanf("%lld %lld", &a, &k);
        find_prime_Meaningless(a, k);
    }
    return 0;
}
```

#### 以下是代码实现的演化过程：
- 一开始的方案是直接加入Prime验证函数，一边遍历，一遍判断，
```c
int is_Prime(long long num)
{
    if(num == 1)
        return 0;
    for(long long i = 2; i * i <= num; i++)
    {
        if(num % i == 0)
            return 0;
    }
    return 1;
}

void find_prime_Meaningless(long long num, int size_Numbers, int k)
{
    //
    for(int i = 0; i * i < num; i++)
    {
        if(num % i == 0 && is_Prime(i))
    }
    //
}
```

实际上上面的`is_Prime`判断完全是多此一举，因为逐个判断`因数`已经决定了后续因数必定为质数：
```c
    //完全可以省略为：
    for(int i = 0; ------)
    {
        if(!num % i)
    }
```

此时还是面临`超时`问题，这是一开始的算法：
- `快速幂`其实也是后面才加的，前面也是用普通的幂求法，但实际上还是快不了；
```c
void find_prime_Meaningless(long long num, int size_Numbers, int k)
{
    long long ret = 1;
    for(int i = 2; i * i<= num; i++)
    {
        long long count = 0;
        if( num % i == 0)//分解本身就会帮我们判断其是否是质数，所以无需判断
        {
            while( num % i == 0)
            {
                count++;
                num /= i;
            }
            if( count < k)
                continue;
            else
            {
                ret *= quck_Pow(i, count);
            }
        }
    }
    printf("%lld\n", ret);
}
```

- 这里是`快速幂`求法(没用)：
```c
  long long quck_Pow(long long a, long long b)
{
    long long ret = 1;
    while(b > 0)
    {
        if(b & 1)
            ret *= a;
        a *= a;
        b >>= 1;
    }
    return ret;
}
```

下面采用避免`幂`计算(很好笑的是`c语言`优化到这一步其实已经是可以得了)：
- 使用`temp`保存是否消除某个因数的两种状态，随计算验证逐步保存
```c
{
 while( num % prime == 0){
            {
                count++;
                num /= prime;
                temp /= prime;
            }
            if( count < k)
            {
                ret = temp;
            }
            else
            {
                temp = ret;
            }
        }
    if (num > 1 ) {
        ret /= num;
    }
}
```    

##### 此时已经到了我能做到的顶峰了，剩下是`Gemini 2.0`大哥引入的质数预运算：
*这个优化直接秒杀本题*
*(值得注意的是之前的循环是从2，开始的，现在要从0开始，因为是从`下标0`开始)*
```c
// Sieve of Eratosthenes 来生成素数
void sieve() {
    char is_prime[MAX_PRIME + 1];
    for (int i = 2; i <= MAX_PRIME; i++) is_prime[i] = 1; //Initialize array

    for (int p = 2; p * p <= MAX_PRIME; p++) {
        if (is_prime[p]) {
            for (int i = p * p; i <= MAX_PRIME; i += p) {
                is_prime[i] = 0;
            }
        }
    }
    for (int p = 2; p <= MAX_PRIME; p++) {
        if (is_prime[p]) {
            primes[prime_count++] = p;
        }
    }
}
```












import math

def is_prime(n):
    if n == 1:
        return False
    for i in range(2, int(math.sqrt(n)) + 1):
        if n % i == 0:
            return False
    return True

def countSum_Prime(array, n, k, ans, sum, index):
    if k == 0:
        if is_prime(sum):
            ans[0] += 1
        return
    for i in range(index, n):
        countSum_Prime(array, n, k - 1, ans, sum + array[i], i + 1)

n, k = map(int, input().split())
array = [int(x) for x in input().split()]
ans = [0]
countSum_Prime(array, n, k, ans, 0, 0)
print(ans[0])

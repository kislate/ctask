'''
Problem Context
The Fibonacci sequence is traditionally used to explain tree recursion.

def fibonacci(n):
    if n in [0, 1]:
        return n
    return fibonacci(n - 1) + fibonacci(n - 2)
This algorithm serves welll its educative purpose but it's tremendously inefficient, not only because
 of recursion, but because we invoke the fibonacci function twice, and the right branch of 
 recursion (i.e. fibonacci(n-2)) recalculates all the Fibonacci numbers already calculated by the 
 left branch (i.e. fibonacci(n-1)).

This algorithm is so inefficient that the time to calculate any Fibonacci number over 50 is 
simply too much. You may go for a cup of coffee or go take a nap while you wait for the answer. 
But if you try it here in Code Wars you will most likely get a code timeout before any answers.

For this particular Kata we want to implement the memoization solution. This will be cool 
because it will let us keep using the tree recursion algorithm while still keeping it sufficiently 
optimized to get an answer very rapidly.

The trick of the memoized version is that we will keep a cache data structure (most likely an 
associative array) where we will store the Fibonacci numbers as we calculate them. When a Fibonacci 
number is calculated, we first look it up in the cache, if it's not there, we calculate it and put 
it in the cache, otherwise we returned the cached number.

Refactor the function into a recursive Fibonacci function that using a memoized data structure 
avoids the deficiencies of tree recursion. Can you make it so the memoization cache is private 
to this function?
'''


def fibonacci(n):
    if n in [0,1]:
        return n
    return fibonacci(n-1) + fibonacci(n-2)
# 这个递归算法效率低下,因为递归调用了两次fibonacci函数,
# 而且右分支递归(fibonacci(n-2))重新计算了左分支(fibonacci(n-1))已经计算过的所有斐波那契数

def fibonacci(n):
    memo = {}

    def fib_helper(x):
        if x in memo:
            return memo[x]
        if x in [0, 1]:
            return x
        memo[x] = fib_helper(x - 1) + fib_helper(x - 2)
        return memo[x]

    return fib_helper(n)
# 还是慢

def fibonacci(n):
    if n in [0,1]:
        return n
    a,b = 0,1
    for _ in range(2,n+1):
        a,b = b,a+b
    return b
# 还是太慢了

from functools import lru_cache

@lru_cache(maxsize=None)
def fibonacci(n):
    if n in [0, 1]:
        return n
    return fibonacci(n - 1) + fibonacci(n - 2) 
# 最逆天的算法,使用functools模块的lru_cache装饰器,缓存了递归调用的结果,大大提高了效率
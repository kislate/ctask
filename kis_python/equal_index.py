"""
This module provides a function to find an index in an array where the sum of the integers to the left of the index 
is equal to the sum of the integers to the right of the index.

Function:
    find_equal_index(arr: List[int]) -> int:
        Given an array of integers, returns the lowest index N where the sum of the integers to the left of N 
        is equal to the sum of the integers to the right of N. If no such index exists, returns -1.

Example:
    Given the array [1, 2, 3, 4, 3, 2, 1], the function will return 3 because at the 3rd position of the array, 
    the sum of the left side of the index (1+2+3) and the sum of the right side of the index (3+2+1) both equal 6.
    
    Given the array [1, 100, 50, -51, 1, 1], the function will return 1 because at the 1st position of the array, 
    the sum of the left side of the index (1) and the sum of the right side of the index (50-51+1+1) both equal 1.
    
    Given the array [20, 10, -80, 10, 10, 15, 35], the function will return 0 because at index 0 the left side is empty 
    and the right side is (10-80+10+10+15+35), both equal 0 when added.

Note:
    - The index of an array starts at 0.
    - If there are multiple answers, the function returns the lowest correct index.
    - The input array length is between 0 and 1000, and the numbers in the array can be any integer, positive or negative.

Input:
    arr: List[int] - An integer array of length 0 < len(arr) < 1000.

Output:
    int - The lowest index where the sum of the integers to the left of the index is equal to the sum of the integers 
    to the right of the index. If no such index exists, returns -1.
"""
def find_even_index(arr):
    return next((i for i in range(len(arr)) if sum(arr[:i]) == sum(arr[i]) == sum(arr) - sum(arr) if i + 1 < len(arr)), -1 )
### 错误的解法



# ### Other Solutions
# def find_even_index(arr):
#     for i in range(len(arr)):
#         if sum(arr[:i]) == sum(arr[i+1:]):
#             return i
#     return -1

def find_even_index(arr):
    return next((i for i in range(len(arr)) if sum(arr[:i]) == sum(arr[i+1:])), -1)

### next() 函数返回迭代器的下一个项目。
### 但是，这个迭代器一旦迭代，就不能再次迭代，也就是说，next() 函数只能从左到右迭代一次。
### 想要重新迭代，需要重新创建迭代器对象。

def find_even_indices(arr):
    for i in range(len(arr)):
        if sum(arr[:i]) == sum(arr[i+1:]):
            yield i

# 示例用法
arr = [1, 2, 3, 4, 3, 2, 1]
indices = list(find_even_indices(arr))# list() 函数将生成器转换为列表
print(indices)  # 输出 [3]

### 生成器函数 yield 语句的作用是产生一个值，然后暂停执行，等待下一次调用。
### 生成器函数可以使用 for 循环来迭代，也可以使用 next() 函数来获取下一个值。
### 生成器函数的执行过程是惰性的，只有在需要时才会执行，这样可以节省内存。
### 生成器函数的执行过程是可恢复的，可以在任何时候暂停和恢复执行。
### 生成器函数的执行过程是单向的，只能从头到尾执行一次，不能反复执行。

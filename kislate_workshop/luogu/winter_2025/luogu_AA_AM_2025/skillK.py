'''
技能冷却（skill）
【题目描述】
在一款游戏中，一个英雄有 n 个技能, 冷却时间分别为 ti，技能升级可以减少冷
却时间，现在你有 m 次技能点，使用 ci 个技能点可以给第 i 个技能减少 1 冷却时
间，但是因为使用技能消耗时间，所以技能的冷却时间最少有 k 秒，现在这个英雄想让
max(t1, t2, ..., tn) 最小，请问最小是多少?
【输入格式】
输入共 n + 1 行.
输入的第一行包含三个正整数 n, m, k ，含义见上文
接下来 n 行，每行含有两个正整数 ti, ci，表示技能 i 原本的冷却时间和升级所需要
的技能点。
【输出格式】
输出一个整数，表示最小化的冷却时间的最大值。
【样例 1 输入】
4 9 2
6 1
5 1
6 2
7 1
【样例 1 输出】
5
【样例 2 输入】
4 30 2
6 1
5 1
6 2
7 1
样例 2 输出】
2
【子任务】
对于 100% 的测试数据，0 < n, ti, ci ≤100000，0 < m ≤109。
'''
import heapq

n, m, k = map(int, input().split())
skills = []
for _ in range(n):
    t, c = map(int, input().split())
    heapq.heappush(skills, (-t, c))
while m > 0:
    t, c = heapq.heappop(skills)
    if -t <= k or c > m:
        heapq.heappush(skills, (t, c))
        break
    m -= c
    heapq.heappush(skills, (t + 1, c))
print(-skills[0][0])


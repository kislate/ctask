'''
华中科技大学计算机科学与技术学院 语言基础 任务管理（task）
任务管理（task）
【题目描述】
你现在有 N 个任务，依次编号为 1 ∼N 。部分任务有一些前置任务。现在，由于
你编号为 1 的任务已经接近截止时间，十分紧急。你想要知道，如果要完成 1 号任务，
至少一共要完成多少任务？
【输入格式】
输入共 N + 1 行。
输入的第一行为一个正整数 N 。
接下来 N 行，第 i 行描述了编号为 i 的任务的前置任务：
• 第 i 行共有 Ci + 1 个数。
• 第一个数为 Ci。
• 接下来 Ci 个数，描述了该任务的前置任务的编号。
【输出格式】
输出一行一个整数，表示至少需要完成的任务数量。
【样例 1 输入】
5
1 2
1 3
1 4
0
0
【样例 1 输出】4
【子任务】
对于 100% 的测试数据，1 ≤N ≤5000，0 ≤Ci < N ，保证任务之间不会构成循环
依赖。
'''


n = int(input())
pre = [[] for _ in range(n + 1)]  # pre[0]未使用

for i in range(1, n + 1):
    parts = list(map(int, input().split()))
    ci = parts[0]
    pres = parts[1:] if ci > 0 else []
    pre[i] = pres

required = {1}
while True:
    new_tasks = set()
    for i in required:
        for k in pre[i]:
            if k not in required:
                new_tasks.add(k)
    if not new_tasks:
        break
    required.update(new_tasks)

print(len(required))






n = int(input())
tasks = [list(map(int, input().split())) for _ in range(n)]
ans = 0
task_list = []
for i in range(n):
    task_list+=tasks[i][1:]
    task_set = set(task_list)
    if task_list == task_set:
        break 
    else:
        task_list = task_set
for i in range(1,n+1):
    if i in task_set:
        ans+=1
if 1 not in task_set:
    ans+=1
print(ans)



from collections import deque

n = int(input())
tasks = [[] for _ in range(n + 1)]

for i in range(1, n + 1):
    tasks[i] = list(map(int, input().split()))[1:]

rq = {1}
old_tasks = deque(1)

while old_tasks:
    t = old_tasks.popleft()
    for i in tasks[t]:
        if i not in rq:
            rq.add(i)
            old_tasks.append(i)
print(len(rq))



from collections import deque

n = int(input())
tasks = [[] for _ in range(n + 1)]

for i in range(1, n + 1):
    tasks[i] = list(map(int, input().split()))[1:]

rq = {1}
old_tasks = deque(1)

while old_tasks:
    t = old_tasks.popleft()
    new_tasks = set(tasks[t]) - rq
    rq.update(new_tasks)
    old_tasks.extend(new_tasks)
print(len(rq))



import sys
from collections import deque

def main():
    n = int(sys.stdin.readline())
    pre = [[] for _ in range(n + 1)]

    for i in range(1, n + 1):
        parts = list(map(int, sys.stdin.readline().split()))
        if parts[0] > 0:
            pre[i] = parts[1:]
        else:
            pre[i] = []

    visited = [False] * (n + 1)
    queue = deque([1])
    visited[1] = True
    count = 1 

    while queue:
        current = queue.popleft()
        for p in pre[current]:
            if not visited[p]:
                visited[p] = True
                count += 1
                queue.append(p)

    print(count)

if __name__ == "__main__":
    main()
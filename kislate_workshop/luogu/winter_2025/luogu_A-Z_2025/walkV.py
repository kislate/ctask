'''
走（walk）
【题目描述】
在一个 m ×m 的棋盘上，每个方格可能是红色、黄色或无色。任务是从最左上角
移动到最右下角。在任何时刻，所站的位置必须是有颜色的，只能向上、下、左、右四
个方向移动。当从一个格子移动到另一个格子时，如果两个格子的颜色相同，则无需支
付金币；如果颜色不同，则需要支付 1 个金币。
此外，可以花费 2 个金币使用魔法，将下一个无色格子短暂变为指定颜色。魔法不
能连续使用，且持续时间有限。一旦使用了魔法，当走到这个暂时有颜色的格子上时不
能再次使用魔法；只有在离开这个位置，走到原本有颜色的格子上时才能再次使用魔法。
当离开位置时（通过施展魔法使其变为有颜色的格子），该格子恢复为无色。
现在的问题是，从最左上角移动到最右下角，要求达成的最少金币花费是多少？
【输入格式】
第一行包含两个正整数 $ m, n$，以一个空格分开，分别代表棋盘的大小，棋盘上
有颜色的格子的数量。
接下来的 $ n $ 行，每行三个正整数 $ x, y, c$，分别表示坐标为 (x, y) 的格子有颜
色 $ c$。
其中 $ c=1$ 代表黄色，$ c=0$ 代表红色。棋盘左上角的坐标为 (1, 1)，右下角的坐
标为 (m, m)。
棋盘上其余的格子都是无色。保证棋盘的左上角一定是有颜色的。
【输出格式】
一个整数，表示花费的金币的最小值，如果无法到达，输出 −1。
【样例 1 输入】
5 7
1 1 0
1 2 0
2 2 1
3 3 1
3 4 0
4 4 1
5 5 0
【样例 1 输出】
8
【样例 2 输入】
5 5
1 1 0
1 2 0
2 2 1
3 3 1
5 5 0
【样例 2 输出】
‐1
【子任务】
对于 30% 的数据，1 ≤m ≤5，1 ≤n ≤10。
对于 60% 的数据，1 ≤m ≤20，1 ≤n ≤200。
对于 100% 的数据，1 ≤m ≤100，1 ≤n ≤1000。
【提示】
题目中说，只能朝四个方向走。可否对使用金币变化颜色的规则做一些拓展，让主
角可以往十二个方向走，同时去部分关于颜色的规则呢？
方向太多，若逐个回溯是否代码太长？请查找资料并学习搜索中的 .增 .量 .数 .组。
第 36 页 共 67 页
'''



#洪水填充初尝试
import heapq

m, n = map(int, input().split())

#初始化棋盘，从1-base索引
board = [[-1] * (m + 2) for _ in range(m + 2)]
for i in range(n):
    x, y, c = map(int , input().split())
    board[x][y] = c

#directions
directions = [(0, 1), (1, 0),(0, -1), (-1, 0)]

#初始化距离数组: old_board[nx][ny][old_color][magic]
mem_board= [[[[False] * 2 for _ in range (2)] for __ in range(m + 2)] for ___ in range(m + 2)]
mem_board[1][1][board[1][1]][1] = False
#heappush将元素加入到堆中(new_cost, nx, ny, color, magic)
heap = []
heapq.heappush(heap, (0, 1, 1, board[1][1], 1))

#循环遍历棋盘
found = False

while heap:# heap存着需要遍历的点
    cost, x, y, color, magic = heapq.heappop(heap)
    if x == m and y == m:
        found = True
        print(cost)# 基于heapq特性，此必为最优解
        break
    if mem_board[x][y][color][magic]:
        continue
    else:
        mem_board[x][y][color][magic] = True

    for dx, dy in directions:
        nx, ny = x + dx, y + dy
        if nx < 1 or nx > m or ny < 1 or ny > m:
            continue
        else:
            if board[nx][ny] != -1 and board[nx][ny] != color:
                if not mem_board[nx][ny][board[nx][ny]][1]:
                    heapq.heappush(heap,(cost+1, nx, ny, board[nx][ny], 1))
            elif board [nx][ny] != -1 and board[nx][ny] == color:
                if not mem_board[nx][ny][board[nx][ny]][1]:
                    heapq.heappush(heap,(cost, nx, ny, board[nx][ny], 1))
            else:
                if magic == 0:
                    continue
                else:
                    for i in [0,1]:
                        if board[x][y] == i:
                            cost_ch = 2
                        else:
                            cost_ch = 3
                        if not mem_board[nx][ny][i][0]:
                            heapq.heappush(heap,(cost+cost_ch, nx, ny, i, 0))

if not found:
    print(-1)
                










        







'''
Given a 2D array and a number of generations, compute n timesteps of Conway's Game of Life.

The rules of the game are:

Any live cell with fewer than two live neighbours dies, as if caused by underpopulation.
Any live cell with more than three live neighbours dies, as if by overcrowding.
Any live cell with two or three live neighbours lives on to the next generation.
Any dead cell with exactly three live neighbours becomes a live cell.
Each cell's neighborhood is the 8 cells immediately around it (i.e. Moore Neighborhood). The universe is infinite in both the x and y dimensions and all cells are initially dead - except for those specified in the arguments. The return value should be a 2d array cropped around all of the living cells. (If there are no living cells, then return [[]].)

For illustration purposes, 0 and 1 will be represented as ░░ and ▓▓ blocks respectively (PHP: plain black and white squares). You can take advantage of the htmlize function to get a text representation of the universe, e.g.:

print(htmlize(cells))'''

def get_generation(cells : list[list[int]], generations : int) -> list[list[int]]:
    def count_neighbours(x: int, y: int, grid: list[list[int]]) -> int:
        directions = [(dx, dy) for dx in (-1, 0 , 1) for dy in (-1, 0, 1) if (dx, dy) != (0, 0)] # 什么牛逼方法 、
        #directions = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]
        count = 0
        for dx, dy in directions:
            nx, ny = x + dx, y + dy
            if 0 <= nx < len(grid) and 0 <= ny < len(grid[0]):
                count += grid[nx][ny]
        return count
    
    def expand_grid(grid: list[list[int]]) -> list[list[int]]:
        rows, cols = len(grid), len(grid[0])
        new_grid = [[0] * (cols + 2) for _ in range(rows + 2)]
        for i in range(rows):
            for j in range(cols):
                new_grid[i + 1][j +1] = grid[i][j]
        return new_grid
    
    def crop_grid(grid: list[list[int]]) -> list[list[int]]:
        min_row, max_row = float('inf'), float('-inf')
        min_col, max_col = float('inf'), float('-inf')
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j]:
                    min_row = min(min_row, i)
                    max_row = max(max_row, i)
                    min_col = min(min_col, j)
                    max_col = max(max_col, j)
        if min_row == float('inf'):
            return [[]]
        return [row[min_col:max_col + 1] for row in grid[min_row:max_row + 1]]
    
    for _  in range(generations):
        cells = expand_grid(cells)
        new_cells = [[0] * len(cells[0]) for _ in range(len(cells))]
        for i in range(len(cells)):
            for j in range(len(cells[0])):
                count = count_neighbours(i, j, cells)
                if cells[i][j]:
                    new_cells[i][j] = 1 if 2 <= count <= 3 else 0
                else:
                    new_cells[i][j] = 1 if count == 3 else 0
        cells = new_cells

    return crop_grid(cells)





from typing import Set, Tuple, List
from collections import defaultdict

Cell = Tuple[int, int]

def simulate(initial: Set[Cell], generations: int) -> Set[Cell]:
    current_gen = initial.copy()
    for _ in range(generations):
        neighbor_counts = defaultdict(int)
        for (x, y) in current_gen:
            for dx in (-1, 0, 1):
                for dy in (-1, 0, 1):
                    if (dx, dy) != (0, 0):
                        neighbor_counts[(x+dx, y+dy)] += 1
        
        current_gen = {
            cell for cell, count in neighbor_counts.items()
            if count == 3 or (count == 2 and cell in current_gen)
        }
    return current_gen

def get_generation(cells: List[List[int]], generations: int) -> List[List[int]]:
    # 输入转换
    live_cells = {
        (x, y) 
        for x, row in enumerate(cells) 
        for y, val in enumerate(row) 
        if val
    }
    
    # 模拟演化
    final_cells = simulate(live_cells, generations)
    
    # 输出转换
    if not final_cells:
        return []
    
    xs = {x for (x, y) in final_cells}
    ys = {y for (x, y) in final_cells}
    min_x, max_x = min(xs), max(xs)
    min_y, max_y = min(ys), max(ys)
    
    return [
        [int((x, y) in final_cells) for y in range(min_y, max_y+1)]
        for x in range(min_x, max_x+1)
    ]










import numpy as np
from scipy.ndimage import generic_filter

def get_cell(cells):
    m, n = cells[4], sum(cells[:4]+cells[5:])
    return n==3 or (n==2 and m)

def crop_window(cells):
    r, c = tuple(cells.any(i).nonzero()[0] for i in (1,0))
    return cells[r[0]:r[-1]+1, c[0]:c[-1]+1].tolist() if r.size else [[]]
    
def get_generation(cells, gens):
    for i in range(gens):
        cells = np.pad(cells, 1, 'constant')
        cells = generic_filter(cells, get_cell, size=(3,3), mode='constant')
        cells = crop_window(cells)
    return cells
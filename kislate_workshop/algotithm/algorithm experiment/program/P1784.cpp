#include <bits/stdc++.h>
#define sudoku_size 81
using namespace std;
vector<vector<int>> sudoku(9, vector<int>(9));
bool found = false;
bool is_valid(int pos, int num) {
    int row = pos / 9, col = pos % 9;

    // 最佳检查顺序

    // check column
    for (int i = 0; i < 9; ++i) {
        if (sudoku[i][col] == num) return false;
    }

    // check row;
    for (int i = 0; i < 9; ++i) {
        if (sudoku[row][i] == num) return false;
    }

    // 检查3x3宫格
    int box_row = (row / 3) * 3;
    int box_col = (col / 3) * 3;
    for (int i = box_row; i < box_row + 3; i++) {
        for (int j = box_col; j < box_col + 3; j++) {
            if (sudoku[i][j] == num) return false;
        }
    }

    return true;
}
void solve(int pos) {
    if (pos == -1) {
        // found = true;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                cout << sudoku[i][j] << " ";
            }
            cout << endl;
        }
        exit(0);
    }
    int x = pos / 9, y = pos % 9;

    if (sudoku[x][y] > 0) {
        solve(pos - 1);
        return;
    }

    // try fill
    for (int i = 1; i <= 9; ++i) {
        if (!is_valid(pos, i)) continue;
        else {
            sudoku[x][y] = i;
            solve(pos - 1);
            // if (found) return;
            sudoku[x][y] = 0;
        }
    }
    return;
}

int main(void) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cin >> sudoku[i][j];
        }
    }
    // 问为什么从最后一个开始， 因为枚举尝试发现， 从后向前可以过最后一个。
    solve(80);
}

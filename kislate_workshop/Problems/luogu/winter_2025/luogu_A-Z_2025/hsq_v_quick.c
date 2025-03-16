#include <stdio.h>
#include <limits.h>
void map(int x, int y, int *coin);
int min = INT_MAX;
int magicflag = 1;  // 1为可以使用魔法
int m, n;
int a[120][120];
#define find(x, y) (a[x][y] < 2) && (x > 0) && (y > 0) && (x <= m) && (y <= m)
#define find2(x, y) (a[x][y] == 2) && (x > 0) && (y > 0) && (x <= m) && (y <= m) && (magicflag == 1)

int main() {
    scanf("%d %d", &m, &n);
    getchar();
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            a[i][j] = 2;
        }
    }
    for (int i = 0; i < n; i++) {
        int k, j, l;
        scanf("%d %d %d", &k, &j, &l);
        for (int p = 0; p <= l; p++) {
            a[k][j] = l;
        }
        getchar();
    }
    int coin = 0;
    map(1, 1, &coin);
    if (min == INT_MAX)
        printf("-1");
    else
        printf("%d", min);
}

void map(int x, int y, int *coin) {
    if (*coin >= min) return;  // 剪枝优化
    if ((x == m) && (y == m)) {
        min = ((*coin) < min) ? (*coin) : min;
        return;
    }
    if (find(x + 1, y)) {
        int temp = magicflag;
        magicflag = 1;
        if (a[x + 1][y] == a[x][y]) {
            a[x][y] += 10;
            map(x + 1, y, coin);
            a[x][y] -= 10;
        } else {
            a[x][y] += 10;
            (*coin)++;
            map(x + 1, y, coin);
            a[x][y] -= 10;
            (*coin)--;
        }
        magicflag = temp;
    } else if (find2(x + 1, y)) {
        magicflag = 0;
        int temp = a[x + 1][y];
        a[x + 1][y] = a[x][y];
        a[x][y] += 10;
        (*coin) += 2;
        map(x + 1, y, coin);
        a[x][y] -= 10;
        magicflag = 1;
        (*coin) -= 2;
        a[x + 1][y] = temp;
    }
    if (find(x, y + 1)) {
        int temp = magicflag;
        magicflag = 1;
        if (a[x][y + 1] == a[x][y]) {
            a[x][y] += 10;
            map(x, y + 1, coin);
            a[x][y] -= 10;
        } else {
            a[x][y] += 10;
            (*coin)++;
            map(x, y + 1, coin);
            a[x][y] -= 10;
            (*coin)--;
        }
        magicflag = temp;
    } else if (find2(x, y + 1)) {
        magicflag = 0;
        int temp = a[x][y + 1];
        a[x][y + 1] = a[x][y];
        a[x][y] += 10;
        (*coin) += 2;
        map(x, y + 1, coin);
        a[x][y] -= 10;
        magicflag = 1;
        (*coin) -= 2;
        a[x][y + 1] = temp;
    }
    if (find(x, y - 1)) {
        int temp = magicflag;
        magicflag = 1;
        if (a[x][y - 1] == a[x][y]) {
            a[x][y] += 10;
            map(x, y - 1, coin);
            a[x][y] -= 10;
        } else {
            a[x][y] += 10;
            (*coin)++;
            map(x, y - 1, coin);
            a[x][y] -= 10;
            (*coin)--;
        }
        magicflag = temp;
    } else if (find2(x, y - 1)) {
        magicflag = 0;
        int temp = a[x][y - 1];
        a[x][y - 1] = a[x][y];
        a[x][y] += 10;
        (*coin) += 2;
        map(x, y - 1, coin);
        a[x][y] -= 10;
        magicflag = 1;
        (*coin) -= 2;
        a[x][y - 1] = temp;
    }
    if (find(x - 1, y)) {
        int temp = magicflag;
        magicflag = 1;
        if (a[x - 1][y] == a[x][y]) {
            a[x][y] += 10;
            map(x - 1, y, coin);
            a[x][y] -= 10;
        } else {
            a[x][y] += 10;
            (*coin)++;
            map(x - 1, y, coin);
            a[x][y] -= 10;
            (*coin)--;
        }
        magicflag = temp;
    } else if (find2(x - 1, y)) {
        magicflag = 0;
        int temp = a[x - 1][y];
        a[x - 1][y] = a[x][y];
        a[x][y] += 10;
        (*coin) += 2;
        map(x - 1, y, coin);
        a[x][y] -= 10;
        magicflag = 1;
        (*coin) -= 2;
        a[x - 1][y] = temp;
    }
}
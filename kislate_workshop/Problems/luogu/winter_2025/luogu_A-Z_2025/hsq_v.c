/*
(x-1,y-1) (x-1,y) (x-1,y+1)
(x,y-1)    (x,y)   (x,y+1)
(x+1,y-1) (x+1,y) (x+1,y+1)
*/
#include <stdio.h>
void print(int a[120][120]);
void map(int a[120][120], int x, int y, int *coin);
int min = 10000;
int magicflag = 1;  // 1为可以使用魔法
int m, n;
#define find(x, y) (a[x][y] < 2) && (x > 0) && (y > 0) && (x <= m) && (y <= m)
#define find2(x, y) (a[x][y] == 2) && (x > 0) && (y > 0) && (x <= m) && (y <= m) && (magicflag == 1)

int main() {
    int a[120][120];
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
    // for (int i = 1; i <= m; i++) {
    //     for (int j = 1; j <= m; j++) {
    //         printf("%d ", a[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("\n");
    int coin = 0;
    map(a, 1, 1, &coin);
    if (min == 10000)
        printf("-1");
    else
        printf("%d", min);
}

void map(int a[120][120], int x, int y, int *coin) {
    //print(a);
    //printf("coin=%d\n", *coin);
    if ((x == m) && (y == m)) {
        min = ((*coin) < min) ? (*coin) : min;
        // print(a);
        // printf("final_coin=%d\n", *coin);
        return;
    }
    if (find(x - 1, y)) {
        int temp = magicflag;
        magicflag = 1;
        if (a[x - 1][y] == a[x][y]) {
            a[x][y] += 10;
            *coin += 0;
            map(a, x - 1, y, coin);
            magicflag = temp;
            a[x][y] -= 10;
        } else {
            a[x][y] += 10;
            *coin += 1;
            map(a, x - 1, y, coin);
            magicflag = temp;
            a[x][y] -= 10;
            *coin -= 1;
        }
    } else if (find2(x - 1, y)) {
        magicflag = 0;
        a[x - 1][y] = a[x][y];
        a[x][y] += 10;
        *coin += 2;
        map(a, x - 1, y, coin);
        a[x][y] -= 10;
        magicflag = 1;
        *coin -= 2;
        a[x - 1][y] = 2;
    }
    if (find(x, y - 1)) {
        int temp = magicflag;
        magicflag = 1;
        if (a[x][y - 1] == a[x][y]) {
            a[x][y] += 10;
            *coin += 0;
            map(a, x, y - 1, coin);
            magicflag = temp;
            a[x][y] -= 10;
        } else {
            a[x][y] += 10;
            *coin += 1;
            map(a, x, y - 1, coin);
            magicflag = temp;
            a[x][y] -= 10;
            *coin -= 1;
        }
    } else if (find2(x, y - 1)) {
        magicflag = 0;
        a[x][y - 1] = a[x][y];
        a[x][y] += 10;
        *coin += 2;
        map(a, x, y - 1, coin);
        a[x][y] -= 10;
        magicflag = 1;
        *coin -= 2;
        a[x][y - 1] = 2;
    }
    if (find(x, y + 1)) {
        int temp = magicflag;
        magicflag = 1;
        if (a[x][y + 1] == a[x][y]) {
            a[x][y] += 10;
            *coin += 0;
            map(a, x, y + 1, coin);
            magicflag = temp;
            a[x][y] -= 10;
        } else {
            a[x][y] += 10;
            *coin += 1;
            map(a, x, y + 1, coin);
            magicflag = temp;
            a[x][y] -= 10;
            *coin -= 1;
        }
    } else if (find2(x, y + 1)) {
        magicflag = 0;
        a[x][y + 1] = a[x][y];
        a[x][y] += 10;
        *coin += 2;
        map(a, x, y + 1, coin);
        a[x][y] -= 10;
        magicflag = 1;
        *coin -= 2;
        a[x][y + 1] = 2;
    }
    if (find(x + 1, y)) {
        int temp = magicflag;
        magicflag = 1;
        if (a[x + 1][y] == a[x][y]) {
            a[x][y] += 10;
            *coin += 0;
            map(a, x + 1, y, coin);
            magicflag = temp;
            a[x][y] -= 10;
        } else {
            a[x][y] += 10;
            *coin += 1;
            map(a, x + 1, y, coin);
            magicflag = temp;
            a[x][y] -= 10;
            *coin -= 1;
        }
    } else if (find2(x + 1, y)) {
        magicflag = 0;
        a[x + 1][y] = a[x][y];
        a[x][y] += 10;
        *coin += 2;
        map(a, x + 1, y, coin);
        a[x][y] -= 10;
        magicflag = 1;
        *coin -= 2;
        a[x + 1][y] = 2;
    }
}

// void print(int a[120][120]) {
//     for (int i = 1; i <= m; i++) {
//         for (int j = 1; j <= m; j++) {
//             printf("%d ", a[i][j]);
//         }
//         printf("\n");
//     }
//     printf("\n");
// }
#include <bits/stdc++.h>
using namespace std;
int Z, k;
typedef struct op{
    int ui, di, li, ri, oi, vi, Li, option;
} op;
vector<op> ops;
vector<vector<char>> pic;

// 1
// ui, vi, Li, di, ri;

// 2
// ui, di, li, ri, oi;

// 顺90度
void rotation_1(int x, int y, int size) {
    vector<vector<char>> tmp_pic = pic;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            pic[x + i][y + j] = tmp_pic[x + size - 1 - j][y + i];
        }
    }
}

// 顺180
void rotation_2(int x, int y, int size) {
    vector<vector<char>> tmp_pic = pic;
    for (int i = 0; i < size; i++) {
        for(int j = 0; j < size; j ++) {
            pic[x + i][y + j] = tmp_pic[x + size - 1 - i][y + size - 1 - j];
        }
    }
}

// 顺270
void rotation_3(int x, int y, int size) {
    vector<vector<char>> tmp_pic = pic;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            pic[x + i][y + j] = tmp_pic[x + j][y + size - 1 - i];
        }
    }
}
void deal_1(op operate) {
    int ui = operate.ui, vi = operate.vi, Li = operate.Li, di = operate.di, ri = operate.ri;
    if (ri % 4 == 1) rotation_1(1, 1, Z);
    if (ri % 4 == 2) rotation_2(1, 1, Z);
    if (ri % 4 == 3) rotation_3(1, 1, Z);
    if (di == 90) rotation_3(ui, vi, Li);
    else if (di == 180) rotation_2(ui, vi, Li);
    else if (di == 270) rotation_1(ui, vi, Li);
}

void fanzhuan_shagnxia(int ui, int di, int li, int ri) {
    vector<vector<char>> tmp_pic = pic;
    for (int i = 0; i <= ui - di; i++) {
        for (int j = 0; j <= ri - li; j++) {
            pic[ui + i][li + j] = tmp_pic[di - i][li + j];
        }
    }
}

void fanzhuan_zuoyou(int ui, int di, int li, int ri) {
    vector<vector<char>> tmp_pic = pic;
    for (int i = 0; i <= di - ui; i++) {
        for (int j = 0; j <= ri - li; j++) {
            pic[ui + i][li + j] = tmp_pic[ui + i][ri - j];
        }
    }
}

void deal_2(op operate) {
    int ui = operate.ui, di = operate.di, li = operate.li, ri = operate.ri, oi = operate.oi;
    if (oi == -1) fanzhuan_zuoyou(ui, di, li, ri);
    if (oi == 1) fanzhuan_shagnxia(ui, di, li, ri);
}
int main(void) {
    ios::sync_with_stdio(false);cin.tie(0);
    cin >> Z;
    pic.resize(Z + 1, vector<char>(Z + 1, '?'));
    for (int i = 1; i <= Z; i++) {
        for (int j = 1; j <= Z; j++) {
            cin >> pic[i][j];
        }
    }
    cin >> k;
    k -= 1;
    char jump;
    cin >> jump;
    ops.resize(k / 6);
    for (int i = 0; i < k / 6; i++) {
        cin >> ops[i].option;
        if (ops[i].option == 1) {
            cin >> ops[i].ui >> ops[i].vi >> ops[i].Li >> ops[i].di >> ops[i].ri;
        } else {
            cin >> ops[i].ui >> ops[i].di >> ops[i].li >> ops[i].ri >> ops[i].oi;
        }
    }
    for (int i = ops.size() - 1; i >= 0; i--) {
        if (ops[i].option == 1) deal_1(ops[i]);
        else deal_2(ops[i]);
    }
    int n;
    for (n = 1; n <= Z; n++) {
        if (pic[n][1] == '?') break;
    }
    n -= 1;
    int m;
    for (m = 1; m <= Z; m++) {
        if (pic[1][m] == '?') break;
    }
    m -= 1;
    cout << n << " " << m << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << pic[i][j];
        }
        cout << endl;
    }
}

/*
4
?Nk?
??F?
??C?
C1??
13
2 1 2 2 3 90 1 2 2 3 1 3 -1
*/
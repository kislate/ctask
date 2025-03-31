#include <bits/stdc++.h>
using namespace std;

typedef struct landmine{
   int  num;
   int  sum;
   int  prior;
}landmine;

int main(void){
    int n;
    cin >> n;
    vector<vector<int>> nodeptr(n + 3, vector<int>(n + 100, 0));// 打算把第一位当作储存连接的点的个数
    vector<landmine> node(n + 3, {0, 0, 0});
    for(int i = 1; i <= n; i++) cin >> node[i].num, node[i].prior = 0;
    for(int i = 1; i <= n-1; i++){
        int cnt = 0;
        for(int j = 1; j <= n-i; j++)
        {
            int type;
            cin >> type;
            if(type) nodeptr[i][++cnt] = i + j;
        }
        nodeptr[i][0] = cnt;
        cnt = 0;
    }
    // // 调试:
    // for(int i = 1; i <= n; i++){
    //     cout << node[i].num << " ";
    // }
    // cout << endl;
    // for(int i = 1; i <= n-1; i++)
    // {
    //     for(int j = 1; j <= nodeptr[i][0]; j++)
    //     {
    //         cout << nodeptr[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    pair<int, int> ans_sum_node = {0, 0};

    vector<int> mem(n + 3, 0);
    mem[1] = ans_sum_node.first;
    int node_num = ans_sum_node.first, cnt = 1, cnt_final = 0, start = 0;

    for(int m = 1; m <= n; m++)
    {
        bool change = false;
        //node[1].sum = node[1].num;
        node[m].sum = node[m].num;
        if(node[m].sum > ans_sum_node.second){
            ans_sum_node.first = m;
            ans_sum_node.second = node[m].sum;
            change = true;
            start = m;
        }
        for(int i = m; i <= n-1; i++){
            for(int j = 1; j <= nodeptr[i][0]; j++){
                if(node[nodeptr[i][j]].sum < node[i].sum + node[nodeptr[i][j]].num){
                    node[nodeptr[i][j]].sum = node[i].sum + node[nodeptr[i][j]].num;
                    node[nodeptr[i][j]].prior = i;
                }
                if(node[nodeptr[i][j]].sum > ans_sum_node.second){
                    ans_sum_node.first = nodeptr[i][j];
                    ans_sum_node.second = node[nodeptr[i][j]].sum;
                    change = true;
                }
            }
        }

        if(change){
            node_num = ans_sum_node.first;
            while(node_num != m){
                node_num = mem[++cnt] = node[node_num].prior;
            }
            mem[m] = ans_sum_node.first;
            cnt_final = cnt;
            start = m;
        }
        // 清空:
        for(int i = 1; i <= n; i++){
            node[i].sum = 0;
            node[i].prior = 0;
        }
    }
    // 输出顺序:
    for(int i = cnt_final; i >= start; i--){
        cout << mem[i] << " ";
    }
    cout << endl << ans_sum_node.second << endl;
}
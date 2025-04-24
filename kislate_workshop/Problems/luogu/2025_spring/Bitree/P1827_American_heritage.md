# P1827 [USACO3.4] 美国血统 American Heritage

## 题目描述

农夫约翰非常认真地对待他的奶牛们的血统。然而他不是一个真正优秀的记帐员。他把他的奶牛 们的家谱作成二叉树，并且把二叉树以更线性的“树的中序遍历”和“树的前序遍历”的符号加以记录而 不是用图形的方法。

你的任务是在被给予奶牛家谱的“树中序遍历”和“树前序遍历”的符号后，创建奶牛家谱的“树的 后序遍历”的符号。每一头奶牛的姓名被译为一个唯一的字母。（你可能已经知道你可以在知道树的两 种遍历以后可以经常地重建这棵树。）显然，这里的树不会有多于 $26$ 个的顶点。

这是在样例输入和样例输出中的树的图形表达方式：


```plain
　　　　　　　　 C
　　　　　　   /  \
　　　　　　  /　　\
　　　　　　 B　　  G
　　　　　　/ \　　/
　　　　   A   D  H
　　　　　　  / \
　　　　　　 E   F

```

附注：

- 树的中序遍历是按照左子树，根，右子树的顺序访问节点；
- 树的前序遍历是按照根，左子树，右子树的顺序访问节点；
- 树的后序遍历是按照左子树，右子树，根的顺序访问节点。

## 输入格式

第一行一个字符串，表示该树的中序遍历。

第二行一个字符串，表示该树的前序遍历。

## 输出格式

单独的一行表示该树的后序遍历。

## 输入输出样例 #1

### 输入 #1

```
ABEDFCHG
CBADEFGH
```

### 输出 #1

```
AEFDBHGC
```

## 说明/提示

题目翻译来自NOCOW。

USACO Training Section 3.4
### AC代码:
```cpp
#include <bits/stdc++.h>
using namespace std;
vector<char> A, B;
stack<char> S;
void dfs(char root);
void delet(char ch)
{
    int idx_A = find(A.begin(), A.end(), ch) - A.begin();
    int idx_B = find(B.begin(), B.end(), ch) - B.begin();
    A.erase(A.begin() + idx_A);
    B.erase(B.begin() + idx_B);
}
int main(void)
{
    string str1, str2;
    cin >> str1 >> str2;
    for(const char &c : str1) A.push_back(c);
    for(const char &c : str2) B.push_back(c);
    A.reserve(100);
    B.reserve(100);
    //cout << B[find(A.begin(), A.end(), B[0]) - A.begin() + 1] << endl;
    //cout << B[find(B.begin(), B.end(), B[0]) - B.begin() + 1] << endl;
    dfs(B[0]);
    while(!S.empty())
    {
        cout << S.top();
        S.pop();
    }
    cout << endl;
    return 0;
}
// ABEDFCHG 中序, 左边的一定在右边的左侧
// CBADEFGH 前序,
// AEFDBHGC
// void dfs(int root)
// {
//     int lroot = root + 1;
//     int rroot = find(A.begin(), A.end(), B[root]) - A.begin() + 1;
//     S.push(B[root]);
//     delet(B[root]);
//     if(rroot < A.size()) dfs(rroot);
//     if(lroot < B.size()) dfs(lroot);
// }
void dfs(char root)
{
    if(A.empty() || B.empty()) return;
    S.push(root);

    unsigned long long rx = find(A.begin(), A.end(), root) - A.begin() + 1;
    unsigned long long lx = find(B.begin(), B.end(), root) - B.begin() + 1;
    bool flag_1=false, flag_2=false;
    char lroot, rroot;
    if(rx < A.size()){
        rroot = A[rx];
        flag_1 = true;
    }
    if(lx < A.size()){
        lroot = B[lx];
        flag_1 = true;
    }
    if(rx < B.size()){
        rroot = B[rx];
        flag_2 = true;
    }
    delet(root);
    if(flag_2) dfs(rroot);
    if(flag_1 && rroot != lroot) dfs(lroot);
}   

```

### 调试代码:
```cpp
#include <bits/stdc++.h>
using namespace std;
vector<char> A, B;
stack<char> S;
void dfs(char root);
void delet(char ch)
{
    int idx_A = find(A.begin(), A.end(), ch) - A.begin();
    int idx_B = find(B.begin(), B.end(), ch) - B.begin();
    A.erase(A.begin() + idx_A);
    B.erase(B.begin() + idx_B);
}
int main(void)
{
    string str1, str2;
    cin >> str1 >> str2;
    for(const char &c : str1) A.push_back(c);
    for(const char &c : str2) B.push_back(c);
    A.reserve(100);
    B.reserve(100);
    //cout << B[find(A.begin(), A.end(), B[0]) - A.begin() + 1] << endl;
    //cout << B[find(B.begin(), B.end(), B[0]) - B.begin() + 1] << endl;
    dfs(B[0]);
    while(!S.empty())
    {
        cout << S.top();
        S.pop();
    }
    cout << endl;
    return 0;
}
// ABEDFCHG 中序, 左边的一定在右边的左侧
// CBADEFGH 前序,
// AEFDBHGC
// void dfs(int root)
// {
//     int lroot = root + 1;
//     int rroot = find(A.begin(), A.end(), B[root]) - A.begin() + 1;
//     S.push(B[root]);
//     delet(B[root]);
//     if(rroot < A.size()) dfs(rroot);
//     if(lroot < B.size()) dfs(lroot);
// }
void dfs(char root)
{
    if(A.empty() || B.empty()) return;
    S.push(root);
    for(unsigned long long i = 0; i < A.size(); i++) cout << A[i] << " ";
    cout << "    "<< root;
    cout << endl;
    for(unsigned long long i = 0; i < B.size(); i++) cout << B[i] << " ";
    cout << endl << endl;

    unsigned long long rx = find(A.begin(), A.end(), root) - A.begin() + 1;
    unsigned long long lx = find(B.begin(), B.end(), root) - B.begin() + 1;
    bool flag_1=false, flag_2=false;
    char lroot, rroot;
    cout << rx << " " << lx << endl;
    cout << A.size() << " " << B.size() << endl;
    if(rx < A.size()){
        rroot = A[rx];
        flag_1 = true;
    }
    if(lx < A.size()){
        lroot = B[lx];
        flag_1 = true;
    }
    if(rx < B.size()){
        rroot = B[rx];
        flag_2 = true;
    }
    cout << flag_1 << " " << flag_2 << endl<< endl;
    delet(root);
    if(flag_2) dfs(rroot);
    if(flag_1 && rroot != lroot) dfs(lroot);
    // if(rx >= A.size() || lx >= B.size()) return;
    // char lroot = B[lx], rroot = B[rx];
    // delet(root);
    // dfs(rroot);
    // dfs(lroot);
}   
```
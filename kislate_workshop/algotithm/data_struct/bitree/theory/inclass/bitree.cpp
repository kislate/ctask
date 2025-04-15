#include <iostream>
#include <queue>

using namespace std;

// 二叉树节点结构体
struct BiTNode {
    int data;
    BiTNode *lchild, *rchild;
};

// 非递归创建二叉树
BiTNode* createTree() {
    BiTNode* s[101]; // 假设最多100个节点
    BiTNode* root = nullptr;
    int i, j, x;

    cout << "请输入节点编号和值（0 0 结束）：" << endl;
    cin >> i >> x;

    while (i != 0) {
        BiTNode* q = new BiTNode;
        q->data = x;
        q->lchild = q->rchild = nullptr;
        s[i] = q;

        if (i == 1) {
            root = q;
        } else {
            j = i / 2;
            if (i % 2 == 1) {
                s[j]->rchild = q;
            } else {
                s[j]->lchild = q;
            }
        }

        cin >> i >> x;
    }

    return root;
}

// 层序遍历二叉树（用于验证）
void levelOrder(BiTNode* root) {
    if (root == nullptr) return;

    queue<BiTNode*> q;
    q.push(root);

    cout << "层序遍历结果：";
    while (!q.empty()) {
        BiTNode* node = q.front();
        q.pop();
        cout << node->data << " ";

        if (node->lchild) q.push(node->lchild);
        if (node->rchild) q.push(node->rchild);
    }
    cout << endl;
}

int main() {
    BiTNode* root = createTree();
    levelOrder(root);

    return 0;
}
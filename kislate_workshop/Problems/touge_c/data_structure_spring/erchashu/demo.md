- 第一关:
```cpp
#include <bits/stdc++.h>
status CreateBiTree(BiTree &T,TElemType definition[])
/*根据带空枝的二叉树先根遍历序列definition构造一棵二叉树，将根节点指针赋值给T并返回OK，
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    static std::unordered_set<KeyType> key_set;
    static int idx = 0;
    if(definition[idx].key == -1 || definition[idx].key == 0){
        T = NULL;
        idx++;
        return OK;
    }
    if(key_set.find(definition[idx].key) != key_set.end()){
        return ERROR;
    }
    key_set.insert(definition[idx].key);

    T = (BiTNode *)malloc(sizeof(BiTNode));
    if(!T) return OVERFLOW;
    T->data = definition[idx++];
    status lres = CreateBiTree(T->lchild, definition);
    status rres = CreateBiTree(T->rchild, definition);
    return (lres == OK && rres == OK);
    /********** End **********/
}

// or

status CreateBiTree(BiTree &T,TElemType definition[])
/*根据带空枝的二叉树先根遍历序列definition构造一棵二叉树，将根节点指针赋值给T并返回OK，
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    static KeyType mem[10000] = {0};
    static int idx = 0;
    if(definition[idx].key == -1 || definition[idx].key == 0){
        T = NULL;
        idx++;
        return OK;
    }
    if(mem[definition[idx].key] == 1){
        return ERROR;
    }
    mem[definition[idx].key] = 1;

    T = (BiTNode *)malloc(sizeof(BiTNode));
    if(!T) return OVERFLOW;
    T->data = definition[idx++];
    status lres = CreateBiTree(T->lchild, definition);
    status rres = CreateBiTree(T->rchild, definition);
    return (lres == OK && rres == OK);
    /********** End **********/
}
```

- 第二关:
```cpp
status ClearBiTree(BiTree &T)
//将二叉树设置成空，并删除所有结点，释放结点空间
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T == NULL) return OK;
    ClearBiTree(T->lchild);
    ClearBiTree(T->rchild);
    free(T);
    T = NULL;
    return OK;
    /********** End **********/
}
```

- 第三关:
```cpp
int BiTreeDepth(BiTree T)
//求二叉树T的深度
{
    static int depth;
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T == NULL) return 0;
    return 1 + max(BiTreeDepth(T->lchild), BiTreeDepth(T->rchild));
    /********** End **********/
}
```

- 第四关:
```cpp
BiTNode* LocateNode(BiTree T,KeyType e)
//查找结点
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T == NULL) return NULL;
    if(T->data.key == e) return T;
    BiTNode* lres = LocateNode(T->lchild, e);
    if(lres) return lres;
    BiTNode* rres = LocateNode(T->rchild, e);
    if(rres) return rres;
    return NULL;
    /********** End **********/
}
```

- 第五关:
```cpp
int mem[10000] = {0};

status to_mem(BiTree T)
{
    if(T == NULL) return OK;
    mem[T->data.key] = 1;
    to_mem(T->lchild);
    to_mem(T->rchild);
    return OK;
}

BiTNode* LocateNode(BiTree T,KeyType e)
//查找结点
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T == NULL) return NULL;
    if(T->data.key == e) return T;
    BiTNode* lres = LocateNode(T->lchild, e);
    if(lres) return lres;
    BiTNode* rres = LocateNode(T->rchild, e);
    if(rres) return rres;
    return NULL;
    /********** End **********/
}

status Assign(BiTree &T,KeyType e,TElemType value)
//实现结点赋值。此题允许通过增加其它函数辅助实现本关任务
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T == NULL) return ERROR;
    for(int i = 0; i < 100; i++) mem[i] = 0;
    to_mem(T);
    if(value.key != e  && mem[value.key] == 1) 
    {
        return ERROR;
    }
    // printf("%d, %d", value.key, mem[e]);
    BiTNode* node = LocateNode(T, e);
    mem[e] = 0;
    mem[value.key] = 1;
    if(node == NULL) return ERROR;
    node->data = value;
    return OK;
    /********** End **********/
}
```

- 第七关:
```cpp
status InsertNode(BiTree &T,KeyType e,int LR,TElemType c)
//插入结点。此题允许通过增加其它函数辅助实现本关任务
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T == NULL) return ERROR;
    if(LR != 0 && LR != 1 && LR != -1) return ERROR;
    if(LocateNode(T, c.key) != NULL) return ERROR; // 不能有相同的关键字
    if(LR == -1)
    {
        BiTNode * newNode = (BiTNode *)malloc(sizeof(BiTNode));
        if(!newNode) return OVERFLOW;
        newNode->data = c;
        newNode->rchild = T;
        newNode->lchild = NULL;
        T = newNode;
        return OK;
    }
    BiTNode * node = LocateNode(T, e);
    if(node == NULL) return ERROR;
    if(LR == 0)
    {
        BiTNode * newNode = (BiTNode *)malloc(sizeof(BiTNode));
        if(!newNode) return OVERFLOW;
        newNode->data = c;
        newNode->lchild = NULL;
        newNode->rchild = node->lchild;
        node->lchild = newNode;
        return OK;
    }
    else if(LR == 1)
    {
        BiTNode * newNode = (BiTNode *)malloc(sizeof(BiTNode));
        if(!newNode) return OVERFLOW;
        newNode->data = c;
        newNode->lchild = NULL;
        newNode->rchild = node->rchild;
        node->rchild = newNode;
        return OK;
    }
    else return ERROR;
    return ERROR;
    /********** End **********/
}
```


- 第八关:
```cpp

status DeleteNode(BiTree &T,KeyType e)
//删除结点。此题允许通过增加其它函数辅助实现本关任务
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T == NULL) return ERROR;
    if (T->data.key == e) {
    BiTNode *del = T;
        // 度为0
        if (T->lchild == NULL && T->rchild == NULL) {
            T = NULL;
        }
        // 度为1
        else if (T->lchild == NULL) {
            T = T->rchild;
        }
        // 度为1（只有左孩子）
        else if (T->rchild == NULL) {
            T = T->lchild;
        }
        // 度为2
        else {
            BiTNode *p = T->lchild;
            while (p->rchild != NULL) {
                p = p->rchild;
            }
            p->rchild = T->rchild;
            T = T->lchild;
        }
        free(del);
        return OK;
    }
    // 递归;
    if(T->lchild && DeleteNode(T->lchild, e) == OK) return OK;
    if(T->rchild && DeleteNode(T->rchild, e) == OK) return OK;
    /********** End **********/
}
```

- 中序和后序遍历(递归):
```cpp
status InOrderTraverse(BiTree T,void (*visit)(BiTree))
//中序遍历二叉树T
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T == NULL) return ERROR;
    InOrderTraverse(T->lchild, visit);
    visit(T);
    InOrderTraverse(T->rchild, visit);
    return OK;
    /********** End **********/
}

status PostOrderTraverse(BiTree T,void (*visit)(BiTree))
//后序遍历二叉树T
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T == NULL) return ERROR;
    PostOrderTraverse(T->lchild, visit);
    PostOrderTraverse(T->rchild, visit);
    visit(T);
    return OK;
    /********** End **********/
}
```

- 前序(非递归):
```cpp
// 非递归
status PreOrderTraverse(BiTree T, void (*visit)(BiTree)) {
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    BiTree stack[1000];
    int top = 0;
    if(T != NULL){
        stack[top++] = T;
    }
    while(top > 0){
        T = stack[--top]; // 弹出栈顶元素
        visit(T); // 访问当前节点
        
        // 先压右孩子, 在压左孩子
        if(T->rchild != NULL){
            stack[top++] = T->rchild;
        }
        if(T->lchild != NULL){
            stack[top++] = T->lchild;
        }
    }
    return OK;
    /********** End **********/
}
```

- 层序:
```cpp
status LevelOrderTraverse(BiTree T,void (*visit)(BiTree))
//按层遍历二叉树T
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T == NULL) return ERROR;
    BiTree queue[1000];
    int front = 0, rear = 0;
    queue[rear++] = T;
    while(front < rear)
    {
        T = queue[front++];
        visit(T);
        if(T->lchild!=NULL) queue[rear++] = T->lchild;
        if(T->rchild!=NULL) queue[rear++] = T->rchild;
    }
    return OK;
    /********** End **********/
}
```

- 获得兄弟节点:
```cpp
BiTNode* GetSibling(BiTree T,KeyType e)
//实现获得兄弟结点
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T == NULL) return NULL;
    if(T->lchild && T->lchild->data.key == e) return T->rchild;
    if(T->rchild && T->rchild->data.key == e) return T->lchild;
    BiTNode* lres = GetSibling(T->lchild, e);
    if(lres) return lres;
    BiTNode* rres = GetSibling(T->rchild, e);
    if(rres) return rres;
    return NULL;
    /********** End **********/
}
```

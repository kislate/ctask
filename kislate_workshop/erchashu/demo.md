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
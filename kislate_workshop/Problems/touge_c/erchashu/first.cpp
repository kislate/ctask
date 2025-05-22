
'''
输入样例:
1 a 2 b 0 null  0 null 3 c 4 d  0 null  0 null 5 e  0 null  0 null -1 null
—— 预期输出 ——

1,a 2,b 3,c 4,d 5,e
2,b 1,a 4,d 3,c 5,e
—— 实际输出 ——

 1,a 2,b 3,c 4,d 5,e
 2,b 1,a 4,d 3,c 5,e 
'''
#include "def.h"

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



void PreOrderTraverse(BiTree T)
{
    if (T)
    {
        printf(" %d,%s",T->data.key,T->data.others);
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}

void InOrderTraverse(BiTree T)
{
    if (T)
    {
        InOrderTraverse(T->lchild);
        printf(" %d,%s",T->data.key,T->data.others);
        InOrderTraverse(T->rchild);
    }
}

int main()
{
TElemType definition[100];
BiTree T;
int ans,i=0;
do {
	scanf("%d%s",&definition[i].key,definition[i].others);
} while (definition[i++].key!=-1);
ans=CreateBiTree(T,definition);
if (ans==OK)
{
    PreOrderTraverse(T);
    printf("\n");
    InOrderTraverse(T);
}
else printf("关键字不唯一");
return 1;
}

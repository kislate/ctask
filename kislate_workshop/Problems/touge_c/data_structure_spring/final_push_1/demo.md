- 第一题:
```cpp
status InitList(SqList& L)
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L.elem != NULL || L.listsize != 0) return -1;
    L.elem = (ElemType *)malloc(sizeof(ElemType) * LIST_INIT_SIZE);
    L.listsize = LIST_INIT_SIZE;
    L.length = 0;
    return 1;
    /********** End **********/
}

```

- 第二题:
```cpp
status DestroyList(SqList& L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L.elem == NULL || L.listsize == 0) return -1;
    free(L.elem);
    L.elem = NULL;
    L.length = 0;
    L.listsize = 0;
    return 1;
    /********** End **********/
}
```

- 第三题:
```cpp
status ClearList(SqList& L)
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L.elem == NULL) return -1;
    L.length = 0;
    return 1;
    /********** End **********/
}
```

- 第四题:
```cpp
status ListEmpty(SqList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L.elem == NULL) return INFEASIBLE;
    if(L.length == 0) return TRUE;
    else return FALSE;
    /********** End **********/
}
```

- 第五题:
```cpp
status ListLength(SqList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L.elem == NULL) return -1;
    return L.length;
    /********** End **********/
}
```

- 第六题:
```cpp
status GetElem(SqList L,int i,ElemType &e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L.elem == NULL) return -1;
    if(i < 1 || i > L.length) return 0;
    e = L.elem[i-1];
    return 1;
    /********** End **********/
}
```

- 第七题:
```cpp
int LocateElem(SqList L,ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号并返回该序号；如果e不存在，返回0；当线性表L不存在时，返回INFEASIBLE（即-1）。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L.elem == NULL) return -1;
    for(int i = 0; i < L.length; i++) if(L.elem[i] == e) return i+1;
    return 0;
    /********** End **********/
}
```

- 第八题:
```cpp
status PriorElem(SqList L,ElemType e,ElemType &pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L.elem == NULL) return -1;
    int flag = 0;
    for(int i = 0; i < L.length; i++)
    {
        if(e == L.elem[i])
        {
            if(i == 0) return 0;
            else pre = L.elem[i-1], flag = 1;
        }
    }
    if(flag) return 1;
    else return 0;
    /********** End **********/
}
```

- 第九题:
```cpp
status NextElem(SqList L,ElemType e,ElemType &next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L.elem == NULL) return -1;
    int flag = 0;
    for(int i = 0; i < L.length; i++)
    {
        if(e == L.elem[i])
        {
            if(i == L.length-1) return 0;
            else next = L.elem[i+1], flag = 1;
        }
       
    }
    if(flag) return 1;
    else return 0;
    /********** End **********/
}
```

- 第十题:
```cpp
status ListInsert(SqList &L,int i,ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L.elem == NULL) return -1;
    if(L.length == L.listsize)
    {
        L.elem = (ElemType*) realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
        if(!L.elem) return 0;
        L.listsize += LISTINCREMENT;
    }
    if(i > L.length+1 || i == 0) return 0;
    for(int j = L.length; j >= i; j--) L.elem[j] = L.elem[j-1];
    L.elem[i-1] = e;
    L.length++;
    return 1;
    /********** End **********/
}
```

- 第十一题:
```cpp
status ListDelete(SqList &L,int i,ElemType &e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L.elem == NULL) return -1;
    if(L.length < i || i < 1 ) return 0;
    e = L.elem[i-1];
    L.length--;
    for(int j = i-1; j < L.length; j++)
    {
        L.elem[j] = L.elem[j+1];
    }
    return 1;
    /********** End **********/
}

```

- 第十二题:
```cpp
status ListTraverse(SqList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L.elem == NULL) return -1;
    for(int i = 0; i < L.length; i++)
    {
        printf("%d", L.elem[i]);
        if(i != L.length - 1) putchar(' ');
    }
    return 1;
    /********** End **********/
}
```
##### 1.这是一个`冒泡排序`的优化算法
```cpp
    void bubble_c(int a[], int n)
    {
        int i = n-1;
        bool change;
        do{
            change = false;
            for(int j = 0; j <i; ++j)
            {
                if(a[j]>a[j+1])
                {
                    int temp = a[j];
                    a[j] = a[j+1];
                    a[j+1] = temp;
                    change = true;
                }
            }
        }while(change && --i >= 1);
    }
```
- 下面这个是`python`版本
```python
    def bubble_py(a):
        n = len(a)
        i = n - 1;
        change = True
        while change and i >=1:
            change = False
            for j in range(i):
                if a[j] > a[j+1]:
                    a[j], a[j+1] = a[j+1], a[j]
                    change = True
            i -= 1
```

##### 下面实现一个`二分法`或者`折半查找法`
```cpp
    int getKthElement(int A[], int B[],int k; int m, int n)// 在两个已经排好序的数组中查找第k小的数
    {
        int index_A=0; index_B=0;
        int candidate_A,candidate_B;// 候选目标下标
        while(k!=1)
        {
            if(index_A>m)
                return B[index_B + k -1];
            if(index_B>n)
                return A[index_A + k -1];
            candidate_A = (index_A+k/2-1>m-1)?(m-1):(index_A+k/2-1);
            candidate_B = (index_B+k/2-1>n-1)?(n-1):(index_B+k/2-1);
            if(A[candidate_A] > B[candidate_B])
            {
                k-=(candidate_A+1);
                index_A = candidate_A + 1;
            }
            else
            {
                k-=(candidate_B+1)
                index_B = candidate_B + 1;
            }
        }
        if(index_A>m)
                return B[index_B + k -1];
            if(index_B>n)
                return A[index_A + k -1];
        return A[index_A]<B[index_B]?A[index_A]:B[index_B];
    }
```

在 Python 中，`set.add()` 和 `set.update()` 都是用于向集合中添加元素的方法，但它们有一些重要的区别：

1. **`set.add(element)`**:
   - 用于向集合中添加单个元素。
   - 如果该元素已经存在于集合中，则不会发生任何变化。
   - 例如：
     ```python
     my_set = {1, 2, 3}
     my_set.add(4)
     print(my_set)  # 输出: {1, 2, 3, 4}
     my_set.add(2)
     print(my_set)  # 输出: {1, 2, 3, 4} (没有变化，因为2已经在集合中)
     ```

2. **`set.update(iterable)`**:
   - 用于向集合中添加多个元素。
   - 参数可以是列表、元组、字符串或其他可迭代对象。
   - 例如：
     ```python
     my_set = {1, 2, 3}
     my_set.update([4, 5])
     print(my_set)  # 输出: {1, 2, 3, 4, 5}
     my_set.update([2, 6])
     print(my_set)  # 输出: {1, 2, 3, 4, 5, 6} (2已经在集合中，所以不会重复添加)
     ```

### 示例代码
假设你有以下代码：

```python
def main():
    n = int(input())
    tasks = [list(map(int, input().split())) for _ in range(n)]
    ans = 0
    task_set = set()

    # 将所有任务的前置任务编号添加到 task_set 中
    for i in range(n):
        task_set.update(tasks[i][1:])  # 使用 update 添加多个元素

    # 计算需要完成的任务数量
    for i in range(1, n + 1):
        if i in task_set:
            ans += 1

    # 如果任务1不在前置任务集合中，则需要额外完成任务1
    if 1 not in task_set:
        ans += 1

    print(ans)

if __name__ == "__main__":
    main()
```

在这个示例中，`task_set.update(tasks[i][1:])` 用于将每个任务的前置任务编号添加到集合中。这样可以确保所有前置任务编号都被添加到集合中，并且不会有重复的元素。
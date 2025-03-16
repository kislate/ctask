def main():
    import sys
    input = sys.stdin.read  # 读取所有输入
    data = input().splitlines()  # 按行分割输入

    # 解析输入
    n, m, k = map(int, data[0].split())
    yesterday = data[1:n+1]  # 昨天派遣的节点
    completed = set(data[n+1:n+1+m])  # 已完全发现的节点
    new_nodes = data[n+1+m:n+1+m+k]  # 新发现的节点

    # 筛选未完全发现的节点
    ans = [node for node in yesterday if node not in completed]
    # 加入新发现的节点
    ans.extend(new_nodes)#这里可以用+号
    # 按字典序排序并输出
    ans.sort()
    print("\n".join(ans))

if __name__ == "__main__":
    main()
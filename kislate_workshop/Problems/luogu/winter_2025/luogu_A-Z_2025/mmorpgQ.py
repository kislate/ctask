def main():
    import sys
    input = sys.stdin.read
    data = input().splitlines()

    n,m,k = map(int,data[0].split())
    yesterday = data[1:n+1]
    today = set(data[n+1:n+1+m])
    new = data[n+1+m:n+1+m+k]

    ans = [node for node in yesterday if node not in today]
    ans.extend(new)
    ans.sort()
    print("\n".join(ans))

if __name__ == "__main__":
    main()
    
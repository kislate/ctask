n = int(input().strip())
ministers = []
for _ in range(n + 1):
    a, b = map(int, input().split())
    ministers.append((a, b));

# arr = arr[:1] + sorted(arr[1:])
ministers = ministers[:1] + sorted(ministers[1:], key = lambda x : x[0] * x[1])
ans = 0
sum = 1
for i in range(1, n + 1):
    sum *= ministers[i - 1][0]
    ans = max(sum // ministers[i][1], ans)

print(ans)

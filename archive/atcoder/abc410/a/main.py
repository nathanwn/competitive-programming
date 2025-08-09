import sys

input = sys.stdin.readline

n = int(input())
a = list(map(int, input().split()))
k = int(input())

ans = 0
for upper in a:
    if k <= upper:
        ans += 1
print(ans)

s = input()
n = 0
for c in s:
    if c == '2':
        n += 1
a = ''.join(['2' for _ in range(n)])
print(a)

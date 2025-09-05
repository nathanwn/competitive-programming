from random import randint

n = randint(8, 10)
print(n)

a = [randint(-int(10), int(10)) for _ in range(n)]

for i in range(len(a)):
    print(a[i], end=' ')
print()

q = randint(15, 20)
print(q)

for i in range(q):
    t = randint(1, 2)
    low, high = randint(1, n), randint(1, n)
    if low > high:
        low, high = high, low
    if t == 1:
        d = randint(1e8, 1e9)
        print(f'{t} {low} {high} {d}')
    else:
        print(f'{t} {low} {high}')
        
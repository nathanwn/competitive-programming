import sys

inf, ouf = sys.argv[1], sys.argv[2]
print(inf)
print(ouf)

def cube(x):
    return x * x * x

with open(inf) as f:
    # print(f.read())
    n = int(f.read().strip())

with open(ouf) as f:
    ra, rb = f.read().strip().split()
    a = int(ra)
    b = int(rb)
    print(a, b)

print(f"{a=}")
print(f"{b=}")
print(f"{n=}")

if cube(a) - cube(b) == n:
    print("YES")
else:
    print("NO")
    print(cube(a) - cube(b))

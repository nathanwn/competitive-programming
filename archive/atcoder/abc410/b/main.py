import sys
from functools import partial

input = sys.stdin.readline
dprint = partial(print, file=sys.stderr)


def main():
    n, q = map(int, input().split())
    x = list(map(int, input().split()))
    b = [0 for _ in range(n)]
    a = [0 for _ in range(q)]

    for j, p in enumerate(x):
        if p == 0:
            min_b = min(b)
            p = b.index(min_b) + 1
        b[p - 1] += 1
        a[j] = p

    for p in a:
        print(p, end=' ')
    print()

    return 0


if __name__ == "__main__":
    raise SystemExit(main())

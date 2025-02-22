def main():
    n = int(input())
    s = [input() for _ in range(n)]
    s.sort(key=lambda _: len(_))
    print("".join(s))

if __name__ == "__main__":
    main()

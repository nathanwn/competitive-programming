from random import randint

print(1)

target_oxi, target_nitro = randint(2, 10), randint(2, 10)
print(f"{target_oxi} {target_nitro}")

n = randint(5, 10)
print(f"{n}")

for i in range(n):
    vo, vn, w = randint(2, 10), randint(2, 10), randint(1, 10)
    print(f"{vo} {vn} {w}")

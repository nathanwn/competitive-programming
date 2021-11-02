from random import randint

b = ['[', ']', '(', ')', '<', '>']

n = randint(3, 7)
# print(n)
a = []

for i in range(n):
    j = randint(0, len(b) - 1)
    a.append(b[j])

print(''.join(a))

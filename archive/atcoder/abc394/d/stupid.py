def try_remove(s):
    t = s.replace("()", "")
    t = t.replace("[]", "")
    t = t.replace("<>", "")
    return s == t, t

s = input()

while True:
    finished, s = try_remove(s)
    if finished:
        break

if len(s) == 0:
    print("Yes")
else:
    print("No")

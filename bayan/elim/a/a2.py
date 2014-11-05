def count(s, x):
    c = 0
    for t in s:
        if x == t:
            c += 1
    return c

t = int(raw_input())
for i in range(t):
    raw_input()
    raw_input()
    s = raw_input()
    mx, cnt = 0, 0
    for c in s:
        res = 0
        if c == "R":
            res = count(s, "S")
        elif c == "S":
            res = count(s, "P")
        else:
            res = count(s, "R")
        if res > mx:
            mx, cnt = res, 0
        if res == mx:
            cnt += 1
    print "Case #%d:\n%d" % (i+1, cnt)

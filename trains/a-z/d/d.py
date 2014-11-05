import datetime

f = open("dayofw.in", "r")
fout = open("dayofw.out", "w")
for rl in f.readlines():
    if not rl.strip():
        continue
    d, m, y = rl.split()
    d = int(d)
    y = int(y)
    y %= 4000
    if y < 4000:
        y += 4000
    cnt = 1
    for i in ("Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"):
        if i in m:
            m = cnt
            break
        cnt += 1
    else:
        while True:
            pass
    print >> fout, ["", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"][ datetime.date(y, m, d).isoweekday() ]

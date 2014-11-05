n = int(raw_input())
for i in range(n):
    s = raw_input().strip()
    c = 1
    for i in s:
        if i in "aeiuo":
            c += 1
    print ["PESAR", "DOKHTAR"][c%2]

from math import factorial as fact

def c(n,k):
    return fact(n)/fact(k)/fact(n-k)


s = open("string.in", "r").readline().strip()
n = len(s)
t = {}

def pc(n):
    res = 1
    for i in [chr(ord('a')+i) for i in range(26)]:
        if i in t:
            res *= c(n, t[i])
            n -= t[i]
    return res

for i in s:
    if i not in t:
        t[i] = 0
    t[i] += 1

res = 0
for i in range(n-1):
#     print "i=",i
    for mj in range(ord(s[i]) - ord('a')):
#         print "mj=", mj
        j = chr(mj+ord('a'))
        if j in t and t[j] > 0:
            t[j] -= 1
            res += pc(n-i-1)
            t[j] += 1
    t[s[i]] -= 1
print >> open("string.out", "w"), res + 1

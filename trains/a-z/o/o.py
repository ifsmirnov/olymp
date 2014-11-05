def gcd(a,b):
    while b:
        a, b = b, a%b
    return a
def lcm(a, b):
    return a*b/gcd(a,b)

n = int(open("lcm.in", "r").readline())
res = 1
for i in range(1, n+1):
    res = lcm(res, i)
print >> open("1cm.out", "w"), res


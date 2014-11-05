from math import factorial as fact
def c(n, k):
    return fact(n)/fact(k)/fact(n-k)

n, k, num = [int(i) for i in open("combo.in", "r").readline().split()]
num -= 1


fout = open("combo.out", "w")
for i in range(n):
    if k == 0:
        break
    resid = c(n-i-1, k-1)
    if resid <= num:
        num -= resid
    else:
        print>>fout, i+1,
        k -= 1
print>>fout

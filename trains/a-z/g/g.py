#!/usr/bin/python

from math import factorial as fact

fin = open("gen.in", "r")
fout = open("gen.out", "w")

fs = [fact(i) for i in range(110)]
n, k = [int(i) for i in fin.readline().split()]
k -= 1
cands = list(range(n))
res = []
for i in range(n):
    for j in range(len(cands)):
        if k < fs[n-i-1]:
            res += [cands[j]]
            cands[j:j+1] = []
            break
        else:
            k -= fs[n-i-1]

for i in res:
    print>>fout, i+1,
print>>fout

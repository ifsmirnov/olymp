#!/usr/bin/python

fin = open("fido.in", "r")
fout = open("fido.out", "w")

n = int(fin.readline())

a = [0]*1005
a[0] = 0
a[1] = a[2] = 1
for i in range(3, n+1):
    a[i] = a[i-1] + a[i-3]
print>>fout, a[n]

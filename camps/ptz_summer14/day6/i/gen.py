#!/usr/bin/python

from random import randint

k = 40000
m = 150
n = 20

print k, m, n
for i in range(k):
    for j in range(n+1):
        print randint(1, 1000000),
    print

for i in range(m):
    for j in range(2*n+1):
        print randint(1, 1000000),
    print


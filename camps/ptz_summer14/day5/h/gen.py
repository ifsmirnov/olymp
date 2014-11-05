#!/usr/bin/python
from random import randint, shuffle


n = 100000
q = 100000
k =  1000

a = list(range(n))
shuffle(a)

print n, q
for i in range(n):
    print randint(1, k),
print
for i in range(n-1):
    print a[i+1] + 1, a[randint(max(0, i - 1), i)] + 1
for i in range(q):
    if randint(1, 2) == 1:
        print "!", randint(1, n), randint(1, k)
    else:
        print "?", randint(1, n), randint(1, n)

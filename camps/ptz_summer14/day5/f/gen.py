#!/usr/bin/python
from random import randint, shuffle
from sys import argv

n = int(argv[1])

print n,n
a = list(range(n))
shuffle(a)
for i in range(n-1):
#     print a[i]+1, a[i+1]+1
#     print i+2, randint(1, i+1)
    print a[i+1]+1, a[randint(0, i)]+1
for i in range(n-1):
    print i+2, (i+2)/2
for i in range(1000):
    print randint(1, n), randint(1, n)

#!/usr/bin/python
from random import randint
from sys import argv

if len(argv) < 3:
    exit(0)
n = int(argv[1])
k = int(argv[2])
m = n+n
print n, m, k
for i in range(m):
    a = randint(1, n)
    b = a
    while a == b:
        b = randint(max(1, a - k), min(n, a + k))
    print a,b
print n
for i in range(n):
    print randint(1, n),
print

#!/usr/bin/python

from sys import argv
from random import randint

n, k = map(int, argv[1:])
print n
for i in range(n):
    print randint(1, k),
print

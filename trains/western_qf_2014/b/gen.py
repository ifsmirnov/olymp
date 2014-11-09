#!/usr/bin/python

from random import randint

n = randint(1, 50)
a = randint(1, 50)
b = randint(1, 50)
if a > b:
    a,b = b,a
p = 0
# p = randint(1, 1000) / 1000.

print n, a, b, p

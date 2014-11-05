#!/usr/bin/python

from sys import argv

if len(argv) == 1:
    r = list(range(1, 11))
else:
    r = map(int, argv[1:])

for i in r:
    n, m = map(int, open("../pap%02d.in" % i).readline().split())
    print "%02d: %d (max: %d)" % (i,  int(open("res%02d.out" % i).readline()), (n*m-1+n+m-1)/(n+m))

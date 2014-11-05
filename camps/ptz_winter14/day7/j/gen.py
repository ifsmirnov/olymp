from random import *
N = 32767
print N
for i in xrange(N):
    if i < N / 2:
        print 2 * i + 2, 2 * i + 3,
    else:
        print 0, 0,
    print randrange(2)

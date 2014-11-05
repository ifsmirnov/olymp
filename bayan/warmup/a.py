from random import randint, seed
seed(233)
n=100000
q=300000
print n
print " ".join(map(str, [randint(1, 10**9) for i in range(n)]))
print q
for i in range(q):
    print i+1


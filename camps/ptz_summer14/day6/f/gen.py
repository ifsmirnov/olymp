from random import shuffle

n = 1000000
print n
a = list(range(n))
# shuffle(a)
for i in a:
    print i+1,
print
# shuffle(a)
a = a[::-1]
for i in a:
    print i+1,
print

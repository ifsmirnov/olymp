from random import randint

from os import popen

def run(a, b):
    return int(popen("echo %d %d | ./d" % (a, b)).read().strip())

while True:
    a = randint(1, 1000)
    b = randint(1, 1000)
    if (run(a, b) != run(b, a)):
        print a, b
        break

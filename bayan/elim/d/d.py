def solve(n, m):
    if n > m:
        n, m = m, n
    fn = n**3*8 + n**2*3+n;
    assert(fn%3 == 0)
    fn /= 3
    add = 4*n*n+2*n
    for i in range(m-n):
        fn += add
        add += n*2
    print fn + n*m, pow(2, n*m+n-2, 1000000007)

t = int(raw_input())
for idx in range(t):
    raw_input()
    n, m = [int(i) for i in raw_input().split()]
    print "Case #%d:" % (idx+1,)
    solve(n, m)

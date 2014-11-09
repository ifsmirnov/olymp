#include <functional>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <ctime>
#include <queue>
#include <set>
#include <map>
using namespace std;
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
#define fore(i, b, e) for (int i = (int)(b); i <= (int)(e); ++i)
#define ford(i, n) for (int i = (int)(n) - 1; i >= 0; --i)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef long long i64;
typedef unsigned long long u64;
const int inf = 1e9+100500;

const int sz = 1<<17;
struct val {
    int c, cnt, pos;
};
val merge(val a, val b) {
    if (a.c > b.c) return a;
    if (b.c > a.c) return b;
    return { a.c, a.cnt + b.cnt, max(a.pos, b.pos) };
}

val rmq[sz * 2];
val get(int l, int r) {
    l += sz;
    r += sz;
    val mx { 0, 0, 0 };
    while (l < r) {
        if (l%2 == 1) mx = merge(mx, rmq[l]);
        if (r%2 == 0) mx = merge(mx, rmq[r]);
        l = (l+1)/2;
        r = (r-1)/2;
    }
    if (l == r) mx = merge(mx, rmq[l]);
    return mx;
}
void upd(int i, int c) {
    i += sz;
    rmq[i] = {c, 1, i-sz};
    for (i /= 2; i; i /= 2) {
        rmq[i] = merge(rmq[i*2], rmq[i*2+1]);
    }
}

int n, m;
char s[sz], buf[10];

void scan() {
    scanf("%s%d", s, &m);
    n = strlen(s);
}

void solve() {
    forn(i, n) upd(i, s[i]);
    forn(i, m) {
        int t;
        scanf("%d", &t);
        if (t == 1) {
            int l, r, k;
            scanf("%d%d%d", &l, &r, &k);
            --l;--r;--k;
            bool ok = false;
            while (l <= r) {
                val a = get(l, r);
                if (a.cnt > k) {
                    printf("%c\n", a.c);
                    ok = true;
                    break;
                } else {
                    k -= a.cnt;
                    l = a.pos + 1;
                }
            }
            if (!ok) {
                printf("-\n");
            }
        } else {
            int a;
            scanf("%d%s", &a, buf);
            upd(a-1, buf[0]);
        }
    }
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    scan();
    solve();

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}

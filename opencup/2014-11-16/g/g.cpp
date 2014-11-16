#include <functional>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <cassert>
#include <cstdlib>
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
const int maxn = 500500;

struct V {
    int x, l, r;
};
V max(V a, V b) {
    if (a.x == b.x) {
        return {a.x, min(a.l, b.l), max(a.r, b.r)};
    } else return a.x > b.x ? a : b;
}

const int sz = 1<<19;
V rmq[sz * 2];
void upd(int i, int x) {
    i += sz;
    rmq[i] = {x, i-sz, i-sz};
    for (i /= 2; i; i /= 2) {
        rmq[i] = max(rmq[i*2], rmq[i*2+1]);
    }
}
V get(int l, int r) {
    l += sz;
    r += sz;
    V mx = {-1, -1, -1};
    while (l < r) {
        if (l%2 == 1) mx = max(mx, rmq[l]);
        if (r%2 == 0) mx = max(mx, rmq[r]);
        l = (l+1)/2;
        r = (r-1)/2;
    }
    if (l == r) mx = max(mx, rmq[l]);
    return mx;
}

int n;
int a[maxn];
int nxt[maxn], prv[maxn], lst[maxn];
int gol[maxn], gor[maxn]; // for min
pii st[maxn];
int stp;
int shr[maxn];

void scan() {
    scanf("%d", &n);
    forn(i, n) scanf("%d", &a[i]), shr[i] = a[i];
    sort(shr, shr+n);
    forn(i, n) a[i] = lower_bound(shr, shr+n, a[i]) - shr;
//     forn(i, n) cout << a[i] << " "; cout << endl;
}

void buildnxt() {
    forn(i, n) lst[i] = -1, nxt[i] = n, prv[i] = -1;
    forn(i, n) {
        int x = a[i];
        if (lst[x] != -1) {
            nxt[lst[x]] = i;
            prv[i] = lst[x];
        }
        lst[x] = i;
    }
}

void buildgol() {
    stp = 0;
    forn(i, n) {
        while (stp > 0 && st[stp-1].fi > a[i]) {
            --stp;
        }
        if (stp == 0) {
            gol[i] = 0;
        } else {
            gol[i] = st[stp-1].se + 1;
        }
        st[stp++] = mp(a[i], i);
    }
}

void buildgor() {
    stp = 0;
    ford(i, n) {
        while (stp > 0 && st[stp-1].fi > a[i]) {
            --stp;
        }
        if (stp == 0) {
            gor[i] = n-1;
        } else {
            gor[i] = st[stp-1].se - 1;
        }
        st[stp++] = mp(a[i], i);
    }
}

pii res = mp(1, 0); // len, -start

void relax(int l, int r) {
    res = max(res, mp(r-l+1, -l));
}

void solve() {
    forn(i, n) {
        upd(i, a[i]);
    }
    buildnxt();
    buildgor();
    buildgol();


    forn(i, n) {
        int l = gol[i];
        int r = gor[i];
        if (l == r) {
            continue;
        }
        int vl, pl1=inf, pl2=inf;
        int vr, pr1=inf, pr2=inf;

//         cout << i << ": " << l << " " << r << endl;

        if (i == l) {
            vl = -1;
        } else {
            V v = get(l, i-1);
//             cout << v.x << " " << v.l << " " << v.r << endl;
            vl = v.x;
            pl1 = v.r;
//             cout << "pl1 = " << pl1 << endl;
//             cout << prv[pl1] << endl;
            assert(pl1 >= l && pl1 <= r);
            pl2 = max(l-1, prv[pl1]);
//             cout << "pl2 = " << pl2 << endl;
        }

        if (i == r) {
            vr = -1;
        } else {
            V v = get(i+1, r);
//             cout << "get " << i+1 << " " << r << endl;
//             cout << v.x << " " << v.l << " " << v.r << endl;
            vr = v.x;
            pr1 = v.l;
            assert(pr1 >= l && pr1 <= r);
            pr2 = min(r+1, nxt[pr1]);
        }

//         cout << vl << " " << vr << endl;
//         cout << pl1 << " " << pl2 << endl;

        assert(vr != -1 || vl != -1);
        if (vl > vr) {
            relax(pl2+1, r);
        } else if (vr > vl) {
            relax(l, pr2-1);
        } else {
            assert(pl1 != inf);
            assert(pl2 != inf);
            assert(pr1 != inf);
            assert(pr2 != inf);
            relax(pl1+1, pr2-1);
            relax(pl2+1, pr1-1);
        }
    }

    cout << res.fi << " " << -res.se+1 << endl;
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

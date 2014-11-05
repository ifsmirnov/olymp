#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <functional>
#include <numeric>
#include <set>
#include <map>
#include <cassert>
#include <ctime>
#include <cstdlib>
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
typedef pair<long long, long long> pii;
typedef long long i64;
typedef unsigned long long u64;
const i64 inf = 1e18+100500;
const int maxn = 2040;
typedef double ld;

ostream& operator<<(ostream& out, const pii& p) {
    out << p.fi << " " << p.se;
    return out;
}

int n;
int a[maxn];
i64 s[maxn];
i64 d[maxn][maxn];

int top;
ld x[maxn];
int st[maxn];
pii cur[maxn];

bool cmp(const pii& lhs, const pii& rhs) {
    return lhs.fi > rhs.fi || (lhs.fi == rhs.fi && lhs.se < rhs.se);
}

int makegood(int n) {
    vector<pii> a(cur, cur+n);
    sort(all(a), cmp);
    int r = 0;
    forn(i, a.size()) {
        if (i == 0 || a[i].fi != a[i-1].fi) {
            cur[r++] = a[i];
        }
    }
    return r;
}

inline ld intersect(int i, int j) {
    return (ld)(cur[j].se-cur[i].se) / (cur[i].fi-cur[j].fi);
}

void scan() {
    scanf("%d", &n);
    forn(i, n) {
        scanf("%d", &a[i]);
        if (i) s[i] = s[i-1] + a[i-1]; // really a[i-1]!
    }
    s[n] = s[n-1] + a[n-1];
}

i64 get(int);

void hull(int n) {
    n = makegood(n);
//     cout << "make hull" << endl;
//     forn(i, n) cout << cur[i] << "    "; cout << endl;
    if (n == 1) {
        top = 0;
        st[0] = 0;
        return;
    }

    top = 1;
    st[0] = 0;
    st[1] = 1;
    x[0] = intersect(0, 1);

    for (int i = 2; i < n; ++i) {
        while (top > 0) {
            ld nx = intersect(st[top], i);
            if (nx <= x[top-1]) {
                --top;
            } else {
                break;
            }
        }
        x[top] = intersect(st[top], i);
        st[++top] = i;
    }
//     forn(i, top) cout << x[i] << " "; cout << endl;
//     cout << "get(1) = " << get(1) << endl;
    x[top+1] = 1e19;
}

inline i64 apply(int i, int x) {
    return (i64)cur[i].fi * x + cur[i].se;
}

inline i64 get(int p) {
    i64 res = min(apply(0, p), apply(st[top], p));
    if (top == 0) return res;
    int t = lower_bound(x, x+top, (ld)p) - x;
    for (int dx = -3; dx <= 3; ++dx) {
        if (t+dx >= 0 && t+dx <= top) {
            res = min(res, apply(st[t+dx], p));
        }
    }
    return res;
}

void solve() {
    forn(j, n+1) forn(k, n+1) d[j][k] = -inf;
    fore(k, 1, n) d[0][k] = 0;
    fore(j, 1, n-1) {
        forn(i, j) {
            cur[i] = mp(s[i], -d[i][j]);
        }

        hull(j);


        fore(k, j+1, n) {
            d[j][k] = (s[k] - s[j]) * s[j] - get(s[k] - s[j]);
//             i64 t = (s[k] - s[j]) * s[j] - get(s[k] - s[j]);
//             forn(i, j) {
//                 d[j][k] = max(d[j][k], d[i][j] + (s[k]-s[j]) * (s[j]-s[i]));
//             }
//             assert(t == d[j][k]);
//             cout << j << " " << k << ": " << d[j][k] << endl;
        }
    }
    i64 res = -inf;
    forn(i, n) res = max(res, d[i][n]);

    cout << res << endl;
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

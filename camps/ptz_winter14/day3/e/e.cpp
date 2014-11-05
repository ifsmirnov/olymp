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
typedef pair<int, int> pii;
typedef long long i64;
typedef unsigned long long u64;
const int inf = 1e9+100500;
const int maxn = 100500;
typedef long double ld;

struct pt {
    ld x, y;
    pt() {}
    pt(ld x, ld y) : x(x), y(y) {}
    pt operator+(const pt& p) const { return pt(x+p.x, y+p.y); }
    pt operator*(ld k) const { return pt(x*k, y*k); }
    ld d2(const pt& p) const { ld dx=x-p.x; ld dy=y-p.y; return dx*dx+dy*dy; }
    ld d2() const { return x*x+y*y; }

    ld operator&(const pt& p) const { return x*p.x + y*p.y; }
};

pt S;
ld v;
int n;
pt p[100];
pt u[100];
int order[100];

// ld mtime(pt p, pt u, ld t, pt s) {
// #define DD(x) (s.d2(p+u*(t+(x))))
// #define OK(x) (DD(x) <= v2 * (x) * (x))
// //     cout << "t = " << t << endl;
//     const ld v2 = v*v;
//     ld dt = 1;
//     while (!OK(dt)) dt *= 2;
// //     cout << "cand: " << dt << endl;
//     ld l = 0, r = dt+1, m;
// //     cout << "rea r: " << (s.d2(p+u*(t+r)) > v2 * dt * dt) << endl;
//     forn(i, 100) {
//         m = (l+r)/2;
//         if (OK(m)) {
//             r = m;
//         } else {
//             l = m;
//         }
//     }
//     return t+r;
// }

ld mtime(pt u, pt v, ld t, pt s) {
#define DD(x) (s.d2(u+v*(t+(x))))
#define OK(x) (DD(x) <= v2 * (x) * (x))

    u.x -= s.x;
    u.y -= s.y;

    s = pt(0, 0);

    const ld v2 = ::v*::v;

    if (OK(0)) {
        return t;
    }

    u = u + v*t;

    ld A = v.d2() - v2;
    ld B = 2.0 * (u.x * v.x + u.y * v.y);
    ld C = u.d2();

    ld D = B*B - 4.0 * A * C;
    D = sqrtl(max(D, 0.0l));

    return t + (-B-D) / (2*A);
// 
//     ld t1 = (-B + D) / (2*A);
//     ld t2 = (-B - D) / (2*A);
// 
// //     cout << t1 << " " << t2 << endl;
//     assert(t1 >= 0 || t2 >= 0);
//     if (t1 > t2) swap(t1, t2);
//     return t + (t1 >= 0 ? t1 : t2);
}

void scan() {
    cin >> S.x >> S.y >> v;
    cin >> n;
    forn(i, n) cin >> p[i].x >> p[i].y >> u[i].x >> u[i].y;
}

void solve() {
    forn(i, n) order[i] = i;
    ld res = 1e50;
    do {
        pt s = S;
        ld t = 0;
        forn(I, n) {
            int i = order[I];
            ld nt = mtime(p[i], u[i], t, s);
            t = nt;
            s = p[i] + u[i] * nt;
        }
        res = min(res, t);
    } while (next_permutation(order, order+n));
    cout << res << endl;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    cout.precision(20);
    cout << fixed;

    int t;
    cin >> t;
    forn(i, t) {
        scan();
        solve();
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}

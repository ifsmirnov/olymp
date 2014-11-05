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
const int maxn = 1000;

typedef double ld;
const ld eps = 1e-9;

struct pt {
    ld x, y;
    pt(){}
    pt(ld x, ld y) : x(x), y(y) {}
    ld operator%(const pt& p) const { return x*p.x + y*p.y; }
    ld d2() const { return x*x+y*y; }
    ld len() const { return sqrtl(d2()); }
    pt operator*(ld k) const { return pt(x*k, y*k); }
    pt norm() const { return *this * (1/len()); }
    pt turn() const { return pt(-y, x); }
    pt operator-(const pt& p) const { return pt(x-p.x, y-p.y); }
};

int n;
pair<pt, ld> a[maxn];

#define sqr(x) ((x)*(x))
void scan() {
    scanf("%d", &n);
    vector<pair<pii, int> > a(n);
    forn(i, n) scanf("%d%d%d", &a[i].fi.fi, &a[i].fi.se, &a[i].se);
    int nn = 0;
    forn(i, n) {
        bool ok = true;
        forn(j, n) if (j != i) {
            if (a[i] == a[j] && j > i) {
                ok = false;
                break;
            }
            if (a[i].se > a[j].se && sqr(a[i].se - a[j].se) > sqr(a[i].fi.fi-a[j].fi.fi) + sqr(a[i].fi.se-a[j].fi.se)) {
                ok = false;
                break;
            }
        }
        if (ok) {
            ::a[nn++] = mp(pt(a[i].fi.fi, a[i].fi.se), a[i].se);
        }
    }
    n = nn;
//     cerr << "n = " << n << endl;
}

bool check(const pt& e) {
    ld mn = 1000000, mx = -1000000;
    forn(i, n) {
        ld alpha = e % a[i].fi;
        mn = min(mn, alpha + a[i].se);
        mx = max(mx, alpha - a[i].se);
    }
    if (mn > mx - eps) {
        pt p = e * ((mn + mx) / 2);
        pt dir = e.turn();
        printf("The circles are on (%.10lf, %.10lf) + (%.10lf, %.10lf) * t\n",
                p.x, p.y, dir.x, dir.y);
        return true;
    }
    return false;
}

void solve(int test_num) {
    printf("Test case %d: ", test_num);
    if (n == 1) {
        pt t = a[0].fi.norm();
        if (a[0].fi.len() < 0.01) {
            t = pt(1, 0);
        }

        printf("The circles are on (0.0, 0.0) + (%.10lf, %.10lf) * t\n", t.x, t.y);
        return;
    }
    vector<pt> cands;
    forn(i, n) forn(j, i) {
        pt p1 = a[i].fi, p2 = a[j].fi;
        ld r1 = a[i].se, r2 = a[j].se;
        if (r1 > r2) {
            swap(p1, p2);
            swap(r1, r2);
        }

        pt p = p2 - p1;

        {
        ld r = r2 - r1;
        ld d = sqrtl(max(ld(0), p.d2() - sqr(r)));

        pt dir1 = pt(p.x*d - p.y*r, p.y*d + p.x*r);
        pt dir2 = pt(p.x*d + p.y*r, p.y*d - p.x*r);
        cands.pb(dir1);
        cands.pb(dir2);
        }

        {
        ld r = r2 + r1;
        ld d = sqrtl(max(ld(0), p.d2() - sqr(r)));

        pt dir1 = pt(p.x*d - p.y*r, p.y*d + p.x*r);
        pt dir2 = pt(p.x*d + p.y*r, p.y*d - p.x*r);
        cands.pb(dir1);
        cands.pb(dir2);
        }
    }

    forn(i, cands.size()) {
        if (check(cands[i].turn().norm())) {
            return;
        }
    }
    printf("There are no suitable straight lines.\n");
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    freopen("circles.in", "r", stdin);
    freopen("circles.out", "w", stdout);

    int t;
    scanf("%d", &t);
    forn(i, t) {
        scan();
        solve(i+1);
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}

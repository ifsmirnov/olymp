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
typedef double ld;

typedef vector<ld> Poly;

ld exec(const Poly& p, ld x) {
    ld res = 0;
    ld t = 1;
    forn(i, p.size()) {
        res += p[i] * t;
        t *= x;
    }
    return res;
}

Poly mul(const Poly& a, const Poly& b) {
    Poly c(a.size() + b.size() - 1);
    forn(i, a.size()) forn(j, b.size()) c[i+j] += a[i]*b[j];
    return c;
}
Poly add(const Poly& a, const Poly& b) {
    Poly c(max(a.size(), b.size()));
    forn(i, a.size()) c[i] += a[i];
    forn(i, b.size()) c[i] += b[i];
    return c;
}
Poly neg(const Poly& a) {
    Poly c(a);
    forn(i, c.size()) c[i] *= -1;
    return c;
}
Poly sub(const Poly& a, const Poly& b) {
    return add(a, neg(b));
}

void out(const Poly& p) {
    ford(i, p.size()) cout << p[i] << " "; cout << endl;
}

Poly deriv(const Poly& p) {
    if (p.size() == 1u) return Poly();
    Poly res(p.size() - 1);
    forn(i, p.size() - 1) {
        res[i] = p[i + 1] * (i+1);
    }
    return res;
}

bool isCandidate(const Poly& p, ld l, ld r) {
    ld vl = exec(p, l);
    ld vr = exec(p, r);
    if (vl == 0 || vr == 0) return true;
    return (vl < 0) != (vr < 0);
}

ld zero(const Poly& p, ld l, ld r) {
    ld factor = exec(p, l) < exec(p, r) ? 1 : -1;
    assert(exec(p, l) * factor <= 0);
    assert(exec(p, r) * factor >= 0);
    ld m;
    while (r - l > 1e-9) {
        m = (r+l)/2;
        if (exec(p, m) * factor > 0) r = m;
        else l = m;
    }
    return (r+l)/2;
}

vector<ld> zeros(const Poly& p) {
    if (p.size() == 1u) {
        return vector<ld>(1, 0.0);
    } else {
        vector<ld> derZeros = zeros(deriv(p));
        derZeros.pb(-100);
        derZeros.pb(100);
        sort(all(derZeros));
        vector<ld> res;
        forn(i, derZeros.size() - 1) {
            if (isCandidate(p, derZeros[i], derZeros[i+1])) {
                ld root = zero(p, derZeros[i], derZeros[i+1]);
                if (!res.empty() && root - res.back() < 1e-9) continue;
                res.pb(root);
            }
        }
        return res;
    }
}

ld globalMin(const Poly& p, ld l, ld r) {
    vector<ld> roots = zeros(deriv(p));
    ld mn = exec(p, l);
    mn = min(mn, exec(p, r));
    for (ld val: roots) if (val >= l && val <= r) mn = min(mn, exec(p, val));
    return mn;
}

pair<Poly, Poly>
getPoly(ld t1, ld x1, ld y1, ld v1, ld t2, ld x2, ld y2, ld v2) {
    ld dx = x2 - x1;
    ld dy = y2 - y1;
    {
        ld dd = sqrt(dx*dx+dy*dy);
        dx /= dd;
        dy /= dd;
    }
    Poly rx(3), ry(3);
    rx[2] = dx * (v2-v1)/(t2-t1);
    ry[2] = dy * (v2-v1)/(t2-t1);
    rx[1] = dx * (v1 - rx[2] * t1);
    ry[1] = dx * (v1 - ry[2] * t1);
    rx[0] = x1 - dx * (t1 * rx[1] + t1 * t1 * rx[2]/2);
    ry[0] = y1 - dy * (t1 * ry[1] + t1 * t1 * ry[2]/2);
    return mp(rx, ry);
}

pair<Poly, Poly> p1, p2;
ld T;

bool scan() {
    T = -1;
    forn(i, 2) {
        ld t1, x1, y1, v1;
        cin >> t1 >> x1 >> y1 >> v1;
        if (t1 < -0.5) return false;
        ld t2, x2, y2, v2;
        cin >> t2 >> x2 >> y2 >> v2;
        if (i == 0) p1 = getPoly(t1, x1, y1, v1, t2, x2, y2, v2);
        if (i == 1) p2 = getPoly(t1, x1, y1, v1, t2, x2, y2, v2);
        T = max(T, max(t1, t2));
    }
    out(p1.fi); out(p1.se); cout << endl;
    out(p2.fi); out(p2.se); cout << endl;
    return true;
}

int solve() {
    Poly dx = sub(p1.fi, p2.fi);
    Poly dy = sub(p1.se, p2.se);
    Poly q = add(mul(dx, dx), mul(dy, dy));
    ld gmin = globalMin(q, T, T+30);
    cout << gmin << endl;
    out(q);
    return gmin < 19*19.0;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    while (scan()) {
        cout << solve() << "\n";
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}

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
const int maxn = 200500;

struct pt {
    i64 x, y;
    int id;
    pt(){}
    pt(i64 x, i64 y):x(x), y(y) {}
    pt operator+(const pt& p) const { return pt(x+p.x, y+p.y); }
    pt operator-(const pt& p) const { return pt(x-p.x, y-p.y); }
    bool operator<(const pt& p) const { return x<p.x || (x == p.x && y < p.y); }
    void transform() {
        i64 tx = x+y;
        i64 ty = x-y;
        x = tx;
        y = ty;
    }
};

i64 d2(const pt& p1, const pt& p2) {
    i64 dx = p2.x - p1.x;
    i64 dy = p2.y - p1.y;
    return dx*dx + dy*dy;
}
bool cmpy(const pt& p1, const pt& p2) {
    return p1.y < p2.y || (p1.y == p2.y && p1.x < p2.x);
}

int n;
i64 cbest = (i64)1e19;
int ba = -1, bb = -1;
pt p[maxn];

i64 sq(i64 x) { return x * x; }

void relax(int i, int j) {
    i64 t = d2(p[i], p[j]);
    if (cbest > t) {
        cbest = t;
        ba = p[i].id;
        bb = p[j].id;
    }
}

void go(int l, int r) {
    if (p[l].x == p[r].x) {
        for (int i = l; i < r; ++i) {
            relax(i, i+1);
        }
        return;
    }
    int m = (l+r)/2;
    int xsp = p[m].x;

    go(l, m);
    go(m+1, r);

    vector<int> a, b;

    fore(i, l, m) {
        if (sq(xsp - p[i].x) < cbest) {
            a.pb(i);
        }
    }
    fore(j, m+1, r) {
        if (sq(p[j].x - xsp) < cbest) {
            b.pb(j);
        }
    }

//     forn(i, a.size()) cout << a[i] << " "; cout << "   ";
//     forn(i, b.size()) cout << b[i] << " "; cout << endl;

    if (!a.empty() && !b.empty()) {
        for (size_t i = 0, j = 0; i < a.size(); ++i) {
            while (j < b.size() && p[b[j]].y < p[a[i]].y) {
                ++j;
            }
            for (int t = max((int)0, (int)j-15); t <= (int)min(b.size()-1, j+15); ++t) {
                assert(t < (int)b.size());
                assert(t >= 0);
                relax(a[i], b[t]);
            }
        }
    }

    vector<pt> np(r-l+1);
    np.back() = pt(-1,-1);
    merge(p+l, p+m+1, p+m+1, p+r+1, np.begin(), cmpy);
    assert(np.back().x >= 0);
    forn(i,r-l+1) p[l + i] = np[i]; // !!!!!!!!!!!!!!
}

void scan() {
    scanf("%d", &n);
    forn(i, n) {
        int x, y;
        scanf("%d%d", &x, &y);
        p[i] = pt(x, y);
        p[i].id = i;
    }
}

void solve() {
    sort(p, p+n);
    go(0, n-1);
//      cout << cbest << endl;
//              assert(d2(p[ba], p[bb]) == cbest);
//      forn(i, n) forn(j, i) {
//          assert(d2(p[i], p[j]) >= cbest);
//          if ((p[i].id == ba && p[j].id == bb)) {
//              assert(d2(p[i], p[j]) == cbest);
//          }
//          if ((p[i].id == bb && p[j].id == ba)) {
//              assert(d2(p[i], p[j]) == cbest);
//          }
//      }
    cout << ba + 1 << " " << bb + 1 << endl;
}


int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#else
    freopen("illegal.in", "r", stdin);
    freopen("illegal.out", "w", stdout);
#endif

    scan();
    solve();

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}

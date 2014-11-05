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

int n;
pair<pii, int> a[maxn];
int d[maxn];
int best = inf;

void scan() {
    scanf("%d", &n);
    forn(i, n) {
        scanf("%d%d%d", &a[i].se, &a[i].fi.fi, &a[i].fi.se);
    }
}

bool cmp(const pair<pii, int>& a, const pair<pii, int>& b) {
    return a.fi.fi - a.se < b.fi.fi - b.se;
}

void solve() {
    sort(a, a+n, cmp);
    int mnx = 1000000, mxx = -1000000;
    int mn = 1000000;
    int mx = -1000000;

    forn(i, n) {
        mnx = min(mnx, a[i].fi.se - a[i].se);
        mxx = max(mxx, a[i].fi.se + a[i].se);
        mn = min(mn, a[i].fi.fi - a[i].se);
        mx = max(mx, a[i].fi.fi + a[i].se);
        if (i + 1 == n) {
            best = min(best, max(100, mxx - mnx) * max(100, mx - mn));
            d[i] = inf;
        } else if (mx < a[i + 1].fi.fi - a[i + 1].se) {
            d[i] = max(100, mxx - mnx) * max(100, mx - mn);
        } else {
            d[i] = inf;
        }
    }

    mnx = 1000000, mxx = -1000000;
    mn = 1000000;
    mx = -1000000;

    ford(i, n) {
        mnx = min(mnx, a[i].fi.se - a[i].se);
        mxx = max(mxx, a[i].fi.se + a[i].se);
        mn = min(mn, a[i].fi.fi - a[i].se);
        mx = max(mx, a[i].fi.fi + a[i].se);
        if (i) {
            best = min(best, d[i - 1] + max(100, mxx - mnx) * max(100, mx - mn));
        }
    }

    forn(i, n) {
        swap(a[i].fi.fi, a[i].fi.se);
    }
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    scan();
    solve();
    solve();
    cout << best << endl;

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}

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
const int maxn = 200500;

int n, m;
int w, h;
i64 xg[maxn], yg[maxn], xa[maxn], ya[maxn];
int cg[maxn], ca[maxn];

void scan() {
    scanf("%d%d%d%d", &n, &m, &w, &h);
    forn(i, n) {
        scanf("%lld%lld%d", &xa[i], &ya[i], &ca[i]);
    }
    forn(i, m) {
        scanf("%lld%lld%d", &xg[i], &yg[i], &cg[i]);
    }
}

void transform(i64& x, i64& y) {
    x *= h;
    y *= w;
    i64 tx = x - y;
    i64 ty = x + y;
    x = tx;
    y = ty;
}

void solve() {
    forn(i, n) transform(xa[i], ya[i]);
    forn(i, m) transform(xg[i], yg[i]);

    vector<pair<i64, int>> evs;
    forn(i, n) evs.pb(mp(xa[i], i));
    forn(i, m) evs.pb(mp(xg[i], ~i));
    sort(all(evs));

    i64 res = 0;
    set<pair<i64, int>> g;
    forn(i, evs.size()) {
        int t = evs[i].se;
        if (t >= 0) {
            i64 y = ya[t];
            while (ca[t]) {
                auto it = g.lower_bound(mp(y, -1));
                if (it == g.end()) break;
                else {
                    int id = it->se;
                    if (cg[id] <= ca[t]) {
                        ca[t] -= cg[id];
                        g.erase(it);
                    } else {
                        cg[id] -= ca[t];
                        ca[t] = 0;
                        break;
                    }
                }
            }
            res += ca[t];
        } else {
            g.insert(mp(yg[~t], ~t));
        }
    }
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

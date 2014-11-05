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
#define fore(i, b, a) for (int i = (int)(b); i <= (int)(a); ++i)
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
const int maxn = 125;

int n, m;
int a[maxn][maxn];
i64 degl[maxn], degr[maxn];
int ml[maxn], mr[maxn];
int b[maxn], lbl;
i64 cmx;
int strong;

bool kuhn_l(int v) {
    if (b[v] == lbl) return false;
    b[v] = lbl;
    forn(to, m) if (a[v][to]) {
        if (degl[mr[to]] != cmx) {
            ml[mr[to]] = -1;
            mr[to] = v;
            ml[v] = to;
            return true;
        }
        if (mr[to] == -1 || kuhn_l(mr[to])) {
            mr[to] = v;
            ml[v] = to;
            return true;
        }
    }
    return false;
}

bool kuhn_r(int v) {
    if (b[v] == lbl) return false;
    b[v] = lbl;
    forn(to, n) if (a[to][v]) {
        if (degr[ml[to]] != cmx) {
            mr[ml[to]] = -1;
            ml[to] = v;
            mr[v] = to;
            return true;
        }
        if (ml[to] == -1 || kuhn_r(ml[to])) {
            ml[to] = v;
            mr[v] = to;
            return true;
        }
    }
    return false;
}


vector<int> lans;
vector<vi> ans;

bool increase() {
    cmx = max(*max_element(degl, degl + n), *max_element(degr, degr + m));
    if (cmx == 0) return false;
    forn(v, n) {
        if (ml[v] != -1) {
            if (!a[v][ml[v]]) {
                mr[ml[v]] = -1;
                ml[v] = -1;
            }
        }
    }
    forn(v, n) if (ml[v] == -1 && degl[v] == cmx) {
        ++lbl;
        bool ret = kuhn_l(v);
        assert(strong || ret);
    }
    forn(v, m) if (mr[v] == -1 && degr[v] == cmx) {
        ++lbl;
        bool ret = kuhn_r(v);
        assert(strong || ret);
    }

    i64 second_max = 0;
    int max_iter = inf;
    forn(v, n) {
        if (ml[v] == -1)
            second_max = max(second_max, degl[v]);
        else
            max_iter = min(max_iter, a[v][ml[v]]);
    }
    forn(v, m) {
        if (mr[v] == -1)
            second_max = max(second_max, degr[v]);
        else
            max_iter = min(max_iter, a[mr[v]][v]);
    }
    max_iter = min((i64)max_iter, cmx - second_max);

    forn(v, n) if (ml[v] != -1) {
        degl[v] -= max_iter;
        degr[ml[v]] -= max_iter;
        a[v][ml[v]] -= max_iter;
    }

    lans.pb(max_iter);
    ans.pb(vi(ml, ml + n));

    return true;
}

void solve() {
    forn(v, n) ml[v] = -1;
    forn(v, m) mr[v] = -1;
    while (increase());
    i64 s = accumulate(all(lans), 0ll);
    printf("%lld %d\n", s, (int)ans.size());
    forn(i, ans.size()) {
        printf("%d", lans[i]);
        forn(j, n) printf(" %d", ans[i][j] + 1);
        printf("\n");
    }
}

void scan() {
//     n = 120;
//     m = 120;
    scanf("%d%d", &n, &m);
    forn(i, n) forn(j, m) {
        scanf("%d", &a[i][j]);
        degl[i] += a[i][j];
        degr[j] += a[i][j];
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

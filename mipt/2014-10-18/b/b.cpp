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
const int maxn = 100500;

int n;
int w[maxn];
vi e[maxn], re[maxn], ce[maxn];
int c[maxn], nc;
int ts[maxn], tspos;
int d[maxn], wc[maxn], b[maxn];

void scan() {
    scanf("%d", &n);
    forn(i, n) {
        scanf("%d", &w[i]);
        int k;
        scanf("%d", &k);
        forn(j, k) {
            int x;
            scanf("%d", &x);
            e[x-1].pb(i);
            re[i].pb(x-1);
        }
    }
    e[0].pb(n);
    re[n].pb(0);
    w[n] = inf;
    ++n;
}

void dfs(int v) {
    b[v] = 1;
    if (w[v] == 0) {
        for (auto to : e[v]) {
            if (!b[to]) dfs(to);
        }
    }
    ts[tspos++] = v;
}

void dfsrev(int v, int c) {
    b[v] = 1;
    ::c[v] = c;
    for (auto to : re[v]) {
        if (!b[to] && w[to] == 0) {
            dfsrev(to, c);
        }
    }
}

void comps() {
    forn(i, n) if (b[i] == 0) dfs(i);
    forn(i, n) b[i] = 0;
    ford(I, n) {
        int i = ts[I];
        if (!b[i]) {
            dfsrev(i, nc++);
        }
    }
    forn(v, n) {
        assert(wc[c[v]] == 0);
        if (w[v]) wc[c[v]] = w[v];
    }
    forn(v, n) if (!w[v]) for (auto to : e[v]) {
        if (c[v] != c[to]) {
            ce[c[v]].pb(c[to]);
        }
    }
}

void dp() {
    ford(i, nc) {
        if (wc[i]) {
            d[i] = wc[i];
            assert(ce[i].empty());
        } else {
            int res = 0;
            for (auto to : ce[i]) {
                int t = d[to];
                if (t == -1) {
                    res = -1;
                    break;
                } else if (t == 0) {
                    ;
                } else if (t == res) {
                    ;
                } else if (res == 0) {
                    res = t;
                } else {
                    res = -1;
                    break;
                }
            }
            d[i] = res;
        }
    }
}

void getres(int v) {
    int cc = c[v];
    // before
    int res = 0;
    for (auto to : e[v]) {
        int t = d[c[to]];
        if (t == -1) {
            res = -1;
            break;
        } else if (t == 0) {
            ;
        } else if (t == res) {
            ;
        } else if (res == 0) {
            res = t;
        } else {
            res = -1;
            break;
        }
    }
    if (res == inf) {
        printf("sober ");
    } else if (res == -1) {
        printf("unknown ");
    } else {
        printf("%d ", res);
    }

    // after
    if (d[cc] == inf) {
        printf("sober\n");
    } else if (d[cc] == -1) {
        printf("unknown\n");
    } else {
        printf("%d\n", d[cc]);
    }
}

void solve() {
    comps();
//     cout << "comps: ";
//     forn(i, n) cout << c[i] << " "; cout << endl;
//     forn(i, nc) {
//         cout << i << " -> ";
//         for (auto v: ce[i]) {
//             cout << v << " ";
//         }
//         cout << endl;
//     }
//     cout << endl;
//     forn(i, nc) cout << wc[i] << " "; cout << endl;
    dp();
//     cout << "nc = " << nc << endl;

    forn(i, n-1) {
        getres(i);
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

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
const int maxn = 1000500;


int val[maxn * 2], nxt[maxn * 2], start[maxn];
int szp = 1;

void add_edge(int u, int v) {
    val[szp] = v;
    nxt[szp] = start[u];
    start[u] = szp++;
}

int n, q;
int p[maxn];
int h[maxn];
int lp[maxn], rp[maxn];
int lpos[maxn];
int dtime;
int rmqtime;

inline int mmax(int i, int j) { return h[i] < h[j] ? i : j; }

const int sz = 1<<21;
int rmq[sz * 2];

int get(int l, int r) {
    if (l > r) swap(l, r);
    l += sz;
    r += sz;
    int mx = rmq[l];
    while (l < r) {
        if (l%2 == 1) mx = mmax(mx, rmq[l]);
        if (r%2 == 0) mx = mmax(mx, rmq[r]);
        l = (l+1)/2;
        r = (r-1)/2;
    }
    if (l == r) mx = mmax(mx, rmq[l]);
    return mx;
}
void put(int i, int x) {
    i += sz;
    rmq[i] = x;
    for (i /= 2; i; i /= 2) rmq[i] = mmax(rmq[i*2], rmq[i*2+1]);
}

inline int lca(int u, int v) {
    return get(lpos[u], lpos[v]);
}

void scan() {
    scanf("%d", &n);
    scanf("%d", &q);
    forn(i, n-1) {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(u-1, v-1);
        add_edge(v-1, u-1);
    }
}

void dfs(int v, int anc) {
    lpos[v] = rmqtime;
    put(rmqtime++, v);
    lp[v] = dtime++;
    for (int p = start[v]; p; p = nxt[p]) {
        int to = val[p];
        if (to != anc) {
            ::p[to] = v;
            h[to] = h[v] + 1;
            dfs(to, v);
            put(rmqtime++, v);
        }
    }
    rp[v] = dtime++;
}

inline bool anc(int u, int v) {
    return lp[v] >= lp[u] && rp[v] <= rp[u];
}

inline int sub_on_path(int u, int l, int x) {
    return anc(l, x) && anc(x, u);
}

inline bool on_path(int u, int v, int x) {
    int l = lca(u, v);
    return sub_on_path(u, l, x) || sub_on_path(v, l, x);
}

pii intersect_paths(int u1, int v1, int u2, int v2) {
    int l = lca(u2, v2);
    if (l == 0) {
        return mp(lca(u2, u1) | lca(u2, v1), lca(v2, u1) | lca(v2, v1));
    } else {
        if (on_path(0, u1, l)) {
            return mp(lca(u2, u1), lca(v2, u1));
        } else if (on_path(0, v1, l)) {
            return mp(lca(u2, v1), lca(v2, v1));
        } else {
            return mp(-1, -1);
        }
    }
}


int lbound[maxn], rbound[maxn]; // spans for [1..n]
int fpath[maxn], plen;
int rfpath[maxn];
int cl, cr;

void build_bounds() {
    cl = cr = 0;
    forn(i, n+5) lbound[i] = rbound[i] = -1;
    forn(i, n) {

        if (i) {
            if (on_path(cl, cr, i)) ;
            else if (on_path(cl, i, cr)) cr = i;
            else if (on_path(cr, i, cl)) cl = i;
            else break;
        }

        lbound[i] = cl;
        rbound[i] = cr;
    }

    plen = h[cl] + h[cr] + 1;

    forn(i, n) fpath[i] = rfpath[i] = -1;

    int tcl = cl, tcr = cr;
    int l = lca(cl, cr);
    for (int i = 0;; ++i) {
        fpath[i] = cl;
        if (cl == l) break;
        cl = p[cl];
    }
    for (int i = plen - 1; cr != l; --i) {
        fpath[i] = cr;
        cr = p[cr];
    }
    forn(i, plen) rfpath[fpath[i]] = i;
    forn(i, plen) {
        if (lbound[i] == -1) break;
        lbound[i] = rfpath[lbound[i]];
        rbound[i] = rfpath[rbound[i]];
    }
    cl = tcl;
    cr = tcr;
}

bool contains(int u, int v, int i) {
    return u <= lbound[i] && v >= rbound[i];
}

int mex(int u, int v) {
    if (u > v) swap(u, v);
    if (!contains(u, v, 0)) return 1;
    int l = 0, r = plen + 2, m;
    while (l + 1 < r) {
        m = (l+r)/2;
        if (contains(u, v, m))
            l = m;
        else
            r = m;
    }
    return r + 1;
}

int solve_path(int u, int v) {
//     cout << "intersect " << u << " " << v << endl;
    pii coords = intersect_paths(cl, cr, u, v);
//     cout << "intersected to " << coords.fi << " " << coords.se << endl;
    int old_u = u;
    int old_v = v;
    if (coords.fi == -1) return 1;
    u = coords.fi;
    v = coords.se;
//     assert(on_path(cl, cr, u));
//     assert(on_path(cl, cr, v));
//     assert(on_path(old_u, old_v, u));
//     assert(on_path(old_u, old_v, v));
    if (rfpath[u] == -1 || rfpath[v] == -1) {
        printf("OLOLOLO\n");
        return 1;
//         exit(0);
    }
    assert(rfpath[u] != -1);
    assert(rfpath[v] != -1);
    u = rfpath[u];
    v = rfpath[v];

    return mex(u, v);
}

// int qqq[maxn];
// vi path;
// bool go(int v, int t) {
//     path.pb(v);
//     if (v == t) return true;
//     qqq[v] = 1;
//     forn(i, e[v].size()) {
//         int to = e[v][i];
//         if (!qqq[to] && go(to, t)) return true;
//     }
//     path.pop_back();
//     return false;
// }
// 
// int solve_dumb(int u, int v) {
//     path.clear();
//     forn(i, n) qqq[i] = 0;
//     go(u, v);
//     sort(all(path));
//     path.pb(-1);
// //     for (auto i: path) cout << i << " "; cout << endl;
//     forn(i, n+1) if (path[i] != i) {
// //         cout << "ret = " << i+1 << endl;
//         return i + 1;
//     }
//     assert(false);
// }

void solve() {
    dfs(0, -1);
//     forn(i, n) {
//         forn(j, n) cout << lca(i, j) << " ";
//         cout << endl;
//     }
//     return;
    build_bounds();
//     cout << cl << " " << cr << endl;
    int xx = 0;
    forn(i, q) {
        int u, v;
        scanf("%d%d", &u, &v);
        u ^= xx;
        v ^= xx;
        xx = solve_path(u-1, v-1);
//         cout << "xx = " << xx << endl;
//         assert(xx == solve_dumb(u-1, v-1));
        printf("%d\n", xx);
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

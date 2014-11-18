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

const int maxn = 300500;
const int sz = 1<<20;

int h[maxn];

int rmq[sz*2];
int mmx(int x, int y) { if (x == -1) return y; return h[x] < h[y] ? x : y; }
int get(int l, int r) {
    if (l > r) swap(l, r);
    l += sz;
    r += sz;
    int mx = -1;
    while (l < r) {
        if (l%2 == 1) mx = mmx(mx, rmq[l]);
        if (r%2 == 0) mx = mmx(mx, rmq[r]);
        l = (l+1)/2;
        r = (r-1)/2;
    }
    if (l == r) mx = mmx(mx, rmq[l]);
    assert(mx != -1);
    return mx;
}
void upd(int i, int x) {
    i += sz;
    rmq[i] = x;
    for (i /= 2; i; i /= 2) {
        rmq[i] = mmx(rmq[i*2], rmq[i*2+1]);
    }
}

int n, m;
vi e[maxn];
int tin[maxn], tout[maxn], tt, dtime, r[maxn];
int b[maxn];
int cur;

void scan() {
    scanf("%d%d", &n, &m);
    forn(i, n) e[i].clear();
    forn(i, n-1) {
        int u, v;
        scanf("%d%d", &u, &v);
        e[--u].pb(--v);
        e[v].pb(u);
    }
}

void dfs(int v, int anc) {
    tin[v] = dtime++;
    r[v] = tt;
    upd(tt++, v);
    for (auto to : e[v]) if (to != anc) {
        h[to] = h[v] + 1;
        dfs(to, v);
        upd(tt++, v);
    }
    tout[v] = dtime++;
}

bool anc(int u, int v) {
    return tin[u] <= tin[v] && tout[v] <= tout[u];
}

int lca(int u, int v) {
    return get(r[u], r[v]);
}

int dist(int u, int v) {
    return h[u] + h[v] - 2 * h[lca(u, v)];
}

bool check(int u, int v, int d) {
    return dist(u, cur) + dist(v, cur) <= d;
}

bool make_better(int u, int v, int d) {
    int cd = dist(u, cur) + dist(v, cur);
    while (cd > d) {
        b[cur] = 1;
        for (auto to : e[cur]) if (!b[to]) {
            int nd = dist(u, to) + dist(v, to);
            if (nd < cd) {
                cur = to;
                cd = nd;
                break;
            } else {
                b[to] = 1;
            }
        }
        if (b[cur]) {
            return false;
        }
    }
    return true;
}

int U[maxn], V[maxn], D[maxn];

void solve() {
    tt = 0;
    forn(i, n) b[i] = 0;
    dfs(0, -1);
    cur = 0;
    bool ok = true;
    forn(i, m) {
        int u, v, d;
        scanf("%d%d%d", &u, &v, &d);
        U[i] = u; V[i] = v; D[i] = d;
        if (!ok) continue;
        if (!make_better(u-1, v-1, d)) {
            ok = false;
        }
    }
    if (ok) {
        forn(i, m) if (!check(U[i]-1, V[i]-1, D[i])) {
            ok = false;
            break;
        }
    }
    if (!ok) {
        printf("NIE\n");
    }
    if (ok) {
        printf("TAK %d\n", cur+1);
    }
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    int t;
    scanf("%d", &t);
    forn(i, t) {
        scan();
        solve();
    }


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}

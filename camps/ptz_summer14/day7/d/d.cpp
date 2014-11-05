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
const int maxn = 250500;

int n, m;
vector<pii> e[maxn];
int b[maxn];
int pr[maxn];
int u[maxn], v[maxn];
vector<pair<int, pii>> ne[maxn];
int prv[maxn];
vector<int> res[maxn];

inline int commonv(int i, int j) {
    if (u[i] == v[j]) return u[i];
    if (u[i] == u[j]) return u[i];
    return v[i];
}

void scan() {
    scanf("%d%d", &n, &m);
    forn(i, m) {
        int u, v;
        scanf("%d%d", &u, &v);
        e[--u].pb(mp(--v, i));
        e[v].pb(mp(u, i));
        ::u[i] = u;
        ::v[i] = v;
    }
}

void dfs1(int v, int ep) {
    b[v] = 1;
    int be = -1;
    forn(i, e[v].size()) {
        int to = e[v][i].fi;
        int ne = e[v][i].se;
        if (ne == ep) continue;
        if (!b[to]) dfs1(to, ne);
        if (pr[ne] == -1) {
            if (be == -1) be = ne;
            else pr[ne] = be, pr[be] = ne, be = -1;
        }
    }
    if (be != -1) pr[be] = ep, pr[ep] = be;
}

int dfs(int v) {
    b[v] = 1;
    int lv = -1;
    forn(i, ne[v].size()) {
        int to = ne[v][i].fi;
        if (b[to]) continue;
        int lf = dfs(to);
        if (lf == -1) continue;
        res[lf].pb(ne[v][i].se.se);
        res[lf].pb(ne[v][i].se.fi);
        if (lv == -1) lv = lf;
        else prv[lv] = lf, prv[lf] = lv, lv = -1;
    }
    if (e[v].size() % 2 == 0) return lv;
    else {
        if (lv == -1) return v;
        else prv[v] = lv, prv[lv] = v;
        return -1;
    }
}

void solve() {
    forn(i, m) pr[i] = -1;
    dfs1(0, -1);
    forn(i, n) b[i] = 0;
    forn(i, n) prv[i] = -1;
    forn(i, m) {
        int c = commonv(i, pr[i]);
        int f = u[i]^v[i]^c;
        int s = u[pr[i]]^v[pr[i]]^c;
        ne[f].pb(mp(s, mp(i, pr[i])));
//         cout << "add edge " << f << " -> " << s << "(" << i << " " << pr[i] << ")" << endl;
    }
    forn(i, n) if (!b[i]) dfs(i);
    forn(i, n) {
        assert(e[i].size()%2 == 0 || prv[i] != -1);
        if (i < prv[i]) {
            printf("%d %d %d\n", i+1, prv[i]+1, (int)(res[i].size() + res[prv[i]].size()));
            forn(j, res[i].size()) printf("%d ", res[i][j]+1);
            ford(j, res[prv[i]].size()) printf("%d ", res[prv[i]][j]+1);
            printf("\n");
        }
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

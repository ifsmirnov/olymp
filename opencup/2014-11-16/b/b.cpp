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
const int inf = 2e9+100500;
const int maxn = 200500;

int dsu_p[maxn];
void init() {
    forn(i, maxn) {
        dsu_p[i] = i;
    }
}
int get(int x) { return x == dsu_p[x] ? x : (dsu_p[x] = get(dsu_p[x])); }
bool unite(int x, int y) {
    x = get(x);
    y = get(y);
    if (x == y) return false;
    dsu_p[x] = y;
    return true;
}


int n, m, k;
int st[maxn];
vector<pii> e[maxn];
pii d[maxn];
vector<pii> ne[maxn];
int b[maxn];

pii operator+(const pii& a, int x) {
    return mp(a.fi+x, a.se);
}

void scan() {
    scanf("%d%d%d", &n, &k, &m);
    forn(i, n) st[i] = -1;
    forn(i, k) {
        int x;
        scanf("%d", &x);
        st[x-1] = i;
    }
    forn(i, m) {
        int u, v, d;
        scanf("%d%d%d", &u, &v, &d);
        --u; --v;
        e[v].pb(mp(u, d));
        e[u].pb(mp(v, d));
    }
}

void dijkstra() {
    forn(i, n) d[i] = mp(inf, -1);
    set<pair<pii, int> > q;
    forn(i, n) if (st[i] != -1) {
        d[i] = mp(0, st[i]);
        q.insert(mp(mp(0, st[i]), i));
    }

    while (!q.empty()) {
        int v = q.begin()->se;
        q.erase(q.begin());
        for (auto edge : e[v]) {
            int to = edge.fi;
            int w = edge.se;
            if (d[to] > d[v] + w) {
                if (d[to].fi != inf) {
                    q.erase(mp(d[to], to));
                }
                d[to] = d[v] + w;
                q.insert(mp(d[to], to));
            }
        }
    }
}

void kruskal() {
    vector<pair<i64, pii> > edges;
    forn(v, n) for (auto edge : e[v]) {
        int to = edge.fi;
        int w = edge.se;
        if (d[v].se != d[to].se) {
            i64 t = (i64) w + d[v].fi + d[to].fi;
            edges.pb(mp(t, mp(d[v].se, d[to].se)));
        }
    }
    sort(all(edges));
    init();
    for (auto e : edges) {
        if (unite(e.se.fi, e.se.se)) {
            ne[e.se.fi].pb(mp(e.se.se, e.fi));
            ne[e.se.se].pb(mp(e.se.fi, e.fi));
//             cout << "add edge " << e.se.fi << " " << e.se.se << " with w = " << e.fi << endl;
        }
    }
}

int h[maxn];
int p[maxn][20];
int mx[maxn][20];

void dfs(int v, int anc) {
    if (anc == -1) {
        p[v][0] = v;
        mx[v][0] = inf;
    }
    b[v] = 1;
    for (auto edge : ne[v]) {
        int to = edge.fi;
        int w = edge.se;
        if (to == anc) {
            continue;
        }
        h[to] = h[v] + 1;
        p[to][0] = v;
        mx[to][0] = w;
        dfs(to, v);
    }
}

void initlca() {
    forn(k, 20) if (k) {
        forn(v, ::k) {
            p[v][k] = p[p[v][k-1]][k-1];
            mx[v][k] = max(mx[v][k-1], mx[p[v][k-1]][k-1]);
        }
    }
}

int getmx(int u, int v) {
    int mx = 0;
    if (h[u] < h[v]) {
        swap(u, v);
    }
    forn(i, 20) {
        if ((1<<i)&(h[u] - h[v])) {
            mx = max(mx, ::mx[u][i]);
            u = p[u][i];
        }
    }
    if (u == v) {
        return mx;
    }
    ford(i, 20) {
        if (p[u][i] != p[v][i]) {
            mx = max(mx, max(::mx[v][i], ::mx[u][i]));
            v = p[v][i];
            u = p[u][i];
        }
    }
    mx = max(mx, ::mx[v][0]);
    mx = max(mx, ::mx[u][0]);
    assert(u != v && p[v][0] == p[u][0]);
    return mx;
}


void solve() {
    dijkstra();
    kruskal();
    forn(i, k) if (!b[i]) dfs(i, -1);
    initlca();
//     forn(i, k) {
//         cout << mx[i][0] << " ";
//     }
//     cout << endl;
    int q;
    scanf("%d", &q);
    forn(i, q) {
        int x, y, d;
        scanf("%d%d%d", &x, &y, &d);
        --x; --y;
        x = st[x];
        y = st[y];
//         printf("stations: %d %d\n", x, y);
        if (p[x][19] != p[y][19]) {
            printf("NIE\n");
            continue;
        }

        int t = getmx(x, y);
//         printf("mx = %d\n", t);
//         printf("d = %d\n", d);
        if (t <= d) {
            printf("TAK\n");
        } else {
            printf("NIE\n");
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

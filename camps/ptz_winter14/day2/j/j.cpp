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
const int maxq = 1000001;

struct TPoint {
    i64 x, y;
    
    TPoint(i64 x = 0, i64 y = 0)
        : x(x)
        , y(y)
    {
    }
    
    TPoint operator-(const TPoint &p) const {
        return TPoint(x - p.x, y - p.y);
    }
    
    i64 operator%(const TPoint &p) const {
        return x * p.y - y * p.x;
    }
};

struct TQuery {
    int t, a, b;
    
    TQuery(int t = 0, int a = 0, int b = 0)
        : t(t)
        , a(a)
        , b(b)
    {
    }
};

TPoint p[maxn];
TQuery q[maxq];
vi adj[maxn], en[maxn];
vector<bool> vis[maxn];
map<int, int> indadj[maxn];

bool upper_half(const TPoint &p) {
    return p.y > 0 || (p.y == 0 && p.x > 0);
}

struct TComparator {
    int v;
    
    TComparator(int v)
        : v(v)
    {
    }
    
    bool operator()(int x, int y) const {
        bool upx = upper_half(p[x] - p[v]), upy = upper_half(p[y] - p[v]);
        if (upx != upy) {
            return upx;
        }
        return ((p[x] - p[v]) % (p[y] - p[v])) > 0;
    }
};

int par[2 * maxq];
i64 area[2 * maxq];

int root(int v) {
    if (v == par[v]) {
        return v;
    }
    return par[v] = root(par[v]);
}

void unite(int u, int v) {
    v = root(v);
    u = root(u);
    if ((u + v) & 1) {
        par[v] = u;
        if (v != u) {
            area[u] += area[v];
        }
    } else {
        par[u] = v;
        if (v != u) {
            area[v] += area[u];
        }
    }
}

i64 getarea(int x) {
    i64 ans = -area[root(x)];
    if (ans <= 0) {
        ans = -1;
    }
    return ans;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    //cin.sync_with_stdio(false);

    int N;
    scanf("%d", &N);
    //cin >> N;
    forn(i, N) {
        //cin >> p[i].x >> p[i].y;
        int x, y;
        scanf("%d%d", &x, &y);
        p[i] = TPoint(x, y);
    }
    
    //cerr << "Points\n";
    
    int Q;
    //cin >> Q;
    scanf("%d", &Q);
    forn(i, Q) {
        scanf("%d%d%d", &q[i].t, &q[i].a, &q[i].b);
        if (q[i].t == 1) {
            adj[q[i].a].pb(q[i].b);
            adj[q[i].b].pb(q[i].a);
        }
    }
    
    //cerr << "Read\n";
    
    int tc = 0;
    forn(i, N) {
        //cerr << i << '\n';
        sort(all(adj[i]), TComparator(i));
        forn(j, adj[i].size()) {
            indadj[i][adj[i][j]] = j;
            //cerr << tc << ' ' << i << ' ' << adj[i][j] << '\n';
            
            en[i].pb(tc++);
            vis[i].pb(false);
            area[en[i].back()] = p[adj[i][j]] % p[i];
        }
    }
    //cerr << "Built\n";
    
    forn(i, tc) {
        par[i] = i;
        //area[i] = 
    }
    forn(i, N) {
        forn(j, adj[i].size()) {
            int v = i, k = j;
            while (!vis[v][k]) {
                //cerr << v << ' ';
                vis[v][k] = true;
                int u = adj[v][k], p = (indadj[u][v] + adj[u].size() - 1) % adj[u].size();
                unite(en[v][k], en[u][p]);
                v = u, k = p;
            }
            //cerr << '\n';
        }
    }
    
    vector<i64> ans;
    for (int i = Q - 1; i >= 0; --i) {
        int a = q[i].a, b = q[i].b;        
        if (q[i].t == 0) {
            int p = indadj[a][b];
            ans.pb(getarea(en[a][p]));
        } else {
            int p1 = indadj[a][b], p2 = indadj[b][a];
            unite(en[a][p1], en[b][p2]);
        }
    }
    reverse(all(ans));
    forn(i, ans.size()) {
        cout << ans[i] << '\n';
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}

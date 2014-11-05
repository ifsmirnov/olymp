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
const int maxn = 10001;

namespace {

int n;
int S, T;
int ne;
int to[maxn], c[maxn];
vi e[maxn];
void addEdge(int u, int v, int c0) {
    //cerr << u << ' ' << v << ' ' << c0 << '\n';
    to[ne] = v; c[ne] = c0; e[u].pb(ne++);
    to[ne] = u; c[ne] =  0; e[v].pb(ne++);
}

void clear(int _n, int s, int t) {
    n = _n;
    S = s;
    T = t;
    ne = 0;
    forn(i, n) e[i].clear();
}

int q[maxn], d[maxn], pos[maxn];
bool bfs() {
    int lq = 0, rq = 1;
    forn(i, n) d[i] = maxn;
    q[0] = S;
    d[S] = 0;
    while (lq != rq) {
        int v = q[lq++];
        for (int i: e[v]) if (c[i] > 0) {
            int to = ::to[i];
            if (d[to] == maxn) {
                d[to] = d[v] + 1;
                q[rq++] = to;
            }
        }
    }
    return d[T] != maxn;
}

int dfs(int v, int curf) {
    if (v == T || curf <= 0) return max(curf, 0);
    for (int &i = pos[v]; i < (int)e[v].size(); ++i) {
        int id = e[v][i];
        int to = ::to[id];
        if (c[id] > 0 && d[to] == d[v] + 1) {
            if (int ret = dfs(to, min(curf, c[id]))) {
                c[id] -= ret;
                c[id ^ 1] += ret;
                return ret;
            }
        }
    }
    return 0;
}

int dinic() {
    int f = 0;
    while (bfs()) {
        forn(i, n) pos[i] = 0;
        while (int ff = dfs(S, 1000000500)) f += ff;
    }
    return f;
}

};

struct TPoint {
    int x, y;
    
    TPoint(int x = 0, int y = 0)
        : x(x)
        , y(y)
    {
    }
    
    TPoint operator+(const TPoint &p) const {
        return TPoint(x + p.x, y + p.y);
    }
    
    TPoint operator-(const TPoint &p) const {
        return TPoint(x - p.x, y - p.y);
    }
    
    int operator*(const TPoint &p) const {
        return x * p.x + y * p.y;
    }
    
    int operator%(const TPoint &p) const {
        return x * p.y - y * p.x;
    }
    
    bool operator<(const TPoint &p) const {
        if (x != p.x) return x < p.x;
        return y < p.y;
    }
    
    bool operator!=(const TPoint &p) const {
        return *this < p || p < *this;
    }
    
    bool operator==(const TPoint &p) const {
        return !(*this != p);
    }
    
    bool half() const {
        if (y != 0) return y > 0;
        return x >= 0;
    }
};

bool fullCmp(const TPoint &a, const TPoint &b) {
    if (a.half() != b.half()) return a.half();
    return a % b > 0;
}

struct TSide {
    TPoint from, to;
    char type;
    
    TSide()
        : from()
        , to()
        , type('Z')
    {
    }
    
    TSide(TPoint from, TPoint to, char c = 'W')
        : from(from)
        , to(to)
        , type(c)
    {
    }
    
    TSide reverse() const {
        return TSide(to, from, type);
    }
    
    bool operator<(const TSide &s) const {
        if (from != s.from) return from < s.from;
        return to < s.to;
    }
};

map<TPoint, int> enP;
map<TSide, int> enS;
vector<TPoint> points;
vector<TSide> sides;
vector<int> dsu, sq;
vector<int> adj[maxn];

int root(int x) {
    if (dsu[x] == x) return x;
    return dsu[x] = root(dsu[x]);
}

void unite(int x, int y) {
    x = root(x);
    y = root(y);
    if (x == y) return;
    dsu[x] = y;
    sq[y] += sq[x];
}

int getPointN(const TPoint &p) {
    if (!enP.count(p)) {
        int q = enP.size();
        points.pb(p);
        enP[p] = q;
        //adj[q].resize(q + 1);
    }
    return enP[p];
}

int pushSide(TSide s) {
    enS[s] = sides.size();
    dsu.pb(sides.size());
    sides.pb(s);
    sq.pb(s.to % s.from);
    return sides.size() - 1;
}

void addSide(TPoint p, TPoint q, char type) {
    int x = getPointN(p);
    int y = getPointN(q);
    adj[x].pb(pushSide(TSide(p, q, type)));
    adj[y].pb(pushSide(TSide(q, p, type)));
}

class TSidesComparator {
    TPoint p;

public:
    TSidesComparator(TPoint p)
        : p(p)
    {
    }
    
    bool operator()(int a, int b) const {
        assert(sides[a].from == p);
        assert(sides[b].from == p);
        return fullCmp(sides[a].to - p, sides[b].to - p);
    }
};

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    ios::sync_with_stdio(false);
    cout << fixed;
    cout.precision(1);

    while (true) {
        int N;
        cin >> N;
        if (!N) break;
        
        enP.clear();
        enS.clear();
        points.clear();
        sides.clear();
        dsu.clear();
        sq.clear();
        forn(i, maxn) adj[i].clear();
        forn(i, N) {
            int x1, y1, x2, y2;
            string c;
            cin >> x1 >> y1 >> x2 >> y2 >> c;
            addSide(TPoint(x1, y1), TPoint(x2, y2), c[0]);
        }
        forn(i, points.size()) {
            sort(all(adj[i]), TSidesComparator(points[i]));
            assert(adj[i].size() > 1);
            forn(j, adj[i].size()) {
                int jj = (j + 1) % adj[i].size();
                unite(enS[sides[adj[i][j]].reverse()], enS[sides[adj[i][jj]]]);
            }
        }
        int S = 2 * sides.size(), T = 2 * sides.size() + 1;
        clear(2 * sides.size() + 2, S, T);
        //cerr << S << ' ' << T << '\n';
        forn(i, sides.size()) {
            int j = enS[sides[i].reverse()];
            if (j < i) continue;
            char type = sides[i].type;
            int x = root(i), y = root(j);
            if (sq[x] < 0) swap(x, y);
            if (x == y) continue;
            if (type == 'E') {
                addEdge(S, 2 * x, 1e9);
            }
            if (type == 'X') {
                addEdge(2 * x + 1, T, 1e9);
            }
            if (type == 'D') {
                addEdge(2 * x + 1, 2 * y, 1e9);
                addEdge(2 * y + 1, 2 * x, 1e9);
            }
        }
        forn(i, sides.size()) {
            if (dsu[i] != i) continue;
            if (sq[i] > 0) {
                addEdge(2 * i, 2 * i + 1, sq[i]);
            }
        }
        //cerr << '\n';
        
        int flow = dinic();
        assert(flow >= 0);
        //cout << 0.5 * flow << '\n';
        printf("%d.%d\n", flow / 2, 5 * (flow % 2));
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}

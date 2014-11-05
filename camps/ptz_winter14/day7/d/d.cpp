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
#include <cmath>
#include <cstdlib>
#include <cstring>
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

typedef double lf;

const lf eps = 1e-8;

lf curt;

lf sqr(lf x) { return x * x; }

struct pt
{
    lf x, y;
    
    pt() {}
    pt(lf nx, lf ny): x(nx), y(ny) {}
};

struct circle
{
    pt p;
    lf r;
    int id, cost;
    
    circle() {}
    circle(const pt &np, int nid): p(np), id(nid), r(0) {}
    
    lf lowest(lf x) const
    {
        return p.y - sqrt(max(0.0, sqr(r) - sqr(p.x - x)));
    }
    
    lf highest(lf x) const
    {
        return p.y + sqrt(max(0.0, sqr(r) - sqr(p.x - x)));
    }
    
    bool cont(lf y) const
    {
        return lowest(curt) <= y && y <= highest(curt);
    }
};

struct event
{
    pt p;
    int id, type;
    
    event() {}
    event(pt np, int nid, int nt): p(np), id(nid), type(nt) {}
    
    inline bool operator < (const event &e) const
    {
        if (fabs(p.x - e.p.x) > eps) return p.x < e.p.x;
        return type > e.type;
    }
};

struct guy
{
    pt p;
    int cnt;
};

struct cmpH
{
    inline bool operator() (const circle &a, const circle &b)
    {
        return a.highest(curt) < b.highest(curt);
    }
};

struct cmpL
{
    inline bool operator() (const circle &a, const circle &b)
    {
        return a.lowest(curt) < b.lowest(curt);
    }
};

const int maxn = 36000, maxm = 36000;

int n, m, k, ecnt;
event events[maxn * 3 + maxm];
circle data[maxn];
guy guys[maxm];
vector<int> tree[maxn];
int anc[maxn];
i64 coeff[maxn], sz[maxn], all = 0;
set<circle, cmpL> circsl;
set<circle, cmpH> circsh;

inline void putEdge(int u, int v)
{
    if (data[u].r <= data[v].r) return;
    //printf("%d %d\n", u, v);
    assert(anc[v] == -1);
    anc[v] = u;
    tree[u].push_back(v);
}

int findCont(lf y)
{
    circle c = circle(pt(curt, y), 0);
    auto a = circsl.lower_bound(c);
    auto b = circsh.lower_bound(c);
    {
        auto it = a;
        assert(it != circsl.begin());
        --it;
        if (it->highest(curt) >= y) return it->id;
    }
    {
        auto it = b;
        assert(it != circsh.end());
        if (it->lowest(curt) <= y) return it->id;
    }
    {
        auto it = a;
        assert(it != circsl.end());
        assert(anc[it->id] != -1);
        if (data[anc[it->id]].cont(y))
            return anc[it->id];
    }
    {
        auto it = b;
        assert(it != circsh.begin());
        --it;
        assert(anc[it->id] != -1);
        if (data[anc[it->id]].cont(y))
            return anc[it->id];
    }
}

void geom()
{
    ecnt = 0;
    for (int i = 0; i < n; ++i)
    {
        events[ecnt++] = event(pt(data[i].p.x - data[i].r, data[i].p.y), i, 1);
        events[ecnt++] = event(pt(data[i].p.x + data[i].r, data[i].p.y), i, -1);
    }
    for (int i = 0; i < m; ++i) events[ecnt++] = event(guys[i].p, i, 0);
    sort(events, events + ecnt);
    for (int i = 0; i < ecnt; ++i)
    {
        curt = events[i].p.x;
        if (events[i].type == 1)
        {
            if (events[i].id != 0)
            {
                int p = findCont(data[events[i].id].p.y);
                if (p != -1) putEdge(p, events[i].id);
            }
            circsl.insert(data[events[i].id]);
            circsh.insert(data[events[i].id]);
        }
        else if (events[i].type == -1)
        {
            circsl.erase(data[events[i].id]);
            circsh.erase(data[events[i].id]);
        }
        else
        {
            int p = findCont(events[i].p.y);
            coeff[p] += guys[events[i].id].cnt;
        }
    }
}

void read()
{
    scanf("%d%d%d", &n, &m, &k);
    //cin >> n >> m >> k;
    ++n;
    data[0] = circle(pt(0, 0), 0);
    data[0].r = 1e9;
    for (int i = 1; i < n; ++i)
    {
        scanf("%lf%lf%lf%d", &data[i].p.x, &data[i].p.y, &data[i].r, &data[i].cost);
        data[i].id = i;
    }
    for (int i = 0; i < m; ++i)
    {
        scanf("%lf%lf%d", &guys[i].p.x, &guys[i].p.y, &guys[i].cnt);
        all += guys[i].cnt;
    }
}

int wcnt = 0;
i64 w[maxn];

int dfs(int v)
{
    sz[v] = coeff[v];
    for (size_t i = 0; i < tree[v].size(); ++i)
        sz[v] += dfs(tree[v][i]);
    return sz[v];
}

void processedges(int v)
{
    for (size_t i = 0; i < tree[v].size(); ++i)
    {
        i64 bsz = min(sz[tree[v][i]], all - sz[tree[v][i]]);
        //cout << v << " " << tree[v][i] << " " << bsz << " " << data[tree[v][i]].cost << endl;
        w[wcnt++] = (bsz * data[tree[v][i]].cost);
        processedges(tree[v][i]);
    }
}

int main() 
{
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    memset(anc, -1, sizeof(anc));
    memset(coeff, 0, sizeof(coeff));
    read();
    geom();
    dfs(0);
    //for (int i = 0; i < n; ++i) cout << sz[i] << " ";
    //cout << endl << all << endl;
    processedges(0);
    sort(w, w + wcnt, greater<i64>());
    assert(wcnt == n - 1);
    i64 ans = 0;
    for (int i = k; i < n - 1; ++i)
        ans += w[i];
    cout << ans << endl;
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}

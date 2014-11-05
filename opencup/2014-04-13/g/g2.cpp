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
const int maxn = 50050;
const int maxc = 30030;

int p[maxn];
int get(int x) { return x==p[x]?p[x]:(p[x]=get(p[x])); }
bool unite(int x, int y) {
    x = get(x), y = get(y);
    if (x == y) {
        return false;
    }
    p[x] = y;
    return true;
}

int n;
int x[maxn], y[maxn];
vector<int> gr[100][100];
int d2(int i, int j) {
    return (x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]);
}

void scan() {
    scanf("%d", &n);
    forn(i, n) scanf("%d%d", &x[i], &y[i]);
}

struct Edge {
    int i, j, d;
    bool operator<(const Edge& e) const { return d < e.d; }
    Edge(){}
    Edge(int i, int j): i(i), j(j), d(d2(i, j)) {}
};

vector<Edge> mst(const vi& p);
void getEdges(const vi& p, vector<Edge>& edges);

void getEdges(const vi& p, vector<Edge>& edges) {
//     cout << "getEdges " << p.size() << endl;
    if (p.size() < 70) {
        forn(i, p.size()) forn(j, i) edges.pb(Edge(p[i], p[j]));
        sort(all(edges));
        return;
    }
    int mxx = 0, mxy = 0, mnx = 30000, mny = 30000;
    forn(i, p.size()) {
        mxx = max(mxx, x[p[i]]);
        mnx = min(mnx, x[p[i]]);
        mxy = max(mxy, y[p[i]]);
        mny = min(mny, y[p[i]]);
    }
    if (mxx == mnx) ++mxx;
    if (mxy == mny) ++mxy;
    vi p1, p2, p3, p4;
    forn(i, p.size()) {
        double px = (double)(x[p[i]] - mnx) / (mxx - mnx);
        double py = (double)(y[p[i]] - mny) / (mxy - mny);
        const ld TH = 0.6;
        if (px < TH && py < TH) p1.pb(p[i]);
        if (px > 1-TH && py < TH) p2.pb(p[i]);
        if (px > 1-TH && py > 1-TH) p3.pb(p[i]);
        if (px < TH && py > 1-TH) p4.pb(p[i]);
    }
    vector<Edge>
        e1 = mst(p1),
        e2 = mst(p2),
        e3 = mst(p3),
        e4 = mst(p4);
    vector<Edge> r1(e1.size() + e2.size()), r2(e3.size() + e4.size());
    merge(all(e1), all(e2), r1.begin());
    merge(all(e3), all(e4), r2.begin());
    edges.resize(r1.size() + r2.size());
    merge(all(r1), all(r2), edges.begin());
}

int ppos[maxn];
vector<Edge> mst(const vi& p) {
    vector<Edge> e;
    getEdges(p, e);
    forn(i, p.size()) {
        ppos[p[i]] = i;
    }
    forn(i, p.size()) ::p[i] = i;
    vector<Edge> res;
    forn(i, e.size()) {
        if (unite(ppos[e[i].i], ppos[e[i].j])) {
            res.pb(e[i]);
        }
    }
    assert(res.size() == p.size() - 1);
    return res;
}

void solve() {
    vi id;
    forn(i, n) id.pb(i);
    vector<Edge> res = mst(vi(id));
    double ans = 0;
    forn(i, res.size()) {
        ans += sqrtl(res[i].d);
    }
    printf("%.20f\n", ans);
    forn(i, res.size()) {
        printf("%d %d\n", res[i].i + 1, res[i].j + 1);
    }
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#else
    freopen("randommst.in", "r", stdin);
    freopen("randommst.out", "w", stdout);
#endif

    scan();
    solve();


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}

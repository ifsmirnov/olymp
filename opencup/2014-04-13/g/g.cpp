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
const int maxn = 51000, iters = 10, range = 10;

typedef double lf;

struct pt
{
    lf x, y;

    pt(lf nx = 0, lf ny = 0): x(nx), y(ny) {}

    pt operator - (const pt &p) const
    {
        return pt(x - p.x, y - p.y);
    }

    lf operator * (const pt &p) const
    {
        return x * p.x + y * p.y;
    }
};

struct edge
{
    int a, b;
    lf x;

    edge() {}
    edge(int na, int nb, lf nx): a(na), b(nb), x(nx) {}

    inline bool operator < (const edge &e) const
    {
        return x < e.x;
    }
};

pt dir, pts[maxn];
int n, srtd[maxn], ecnt, dsu[maxn], rnk[maxn];
edge edges[maxn * iters * range * 2];

int get(int v)
{
    return dsu[v] == v ? v : dsu[v] = get(dsu[v]);
}

void unite(int u, int v)
{
    u = get(u), v = get(v);
    if (u == v) return;
    if (rnk[u] == rnk[v]) rnk[u]++;
    if (rnk[u] > rnk[v]) dsu[v] = u;
    else dsu[u] = v;
}

inline lf sqdist(const pt &a, const pt &b)
{
    return (a - b) * (a - b);
}

inline lf cmpProj(int a, int b)
{
    return pts[a] * dir < pts[b] * dir;
}

void gen(int n, int c)
{
    FILE *f = fopen("input.txt", "w");
    fprintf(f, "%d\n", n);
    for (int i = 0; i < n; ++i)
        fprintf(f, "%d %d\n", rand() % (2 * c + 1) - c, rand() % (2 * c + 1) - c);
    fclose(f);
}

int main()
{
#ifdef HOME
    long long x;
    asm("rdtsc":"=A"(x));
    srand(x);
//     gen(50000, 30000)
    freopen("input.txt", "r", stdin);
#else
    srand(58924);
    freopen("randommst.in", "r", stdin);
    freopen("randommst.out", "w", stdout);
#endif
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        scanf("%lf%lf", &pts[i].x, &pts[i].y);
    for (int it = 0; it < iters; ++it)
    {
        dir = pt(rand() % 200000001 - 100000000, rand() % 200000001 - 100000000);
        for (int i = 0; i < n; ++i) srtd[i] = i;
        sort(srtd, srtd + n, cmpProj);
        for (int i = 0; i < n; ++i)
            for (int j = max(0, i - range); j < min(n, i + range); ++j)
                if (i != j)
                    edges[ecnt++] = (edge(srtd[i], srtd[j], sqdist(pts[srtd[i]], pts[srtd[j]])));
    }
    sort(edges, edges + ecnt);
    for (int i = 0; i < n; ++i) dsu[i] = i, rnk[i] = 0;
    lf ans = 0;
    vector<edge> vans;
    for (int i = 0; i < ecnt; ++i)
    {
        if (get(edges[i].a) == get(edges[i].b)) continue;
        unite(edges[i].a, edges[i].b);
        ans += sqrtl(edges[i].x);
        vans.pb(edges[i]);
    }
    cout.precision(20);
    cout << fixed;
    cout << ans << endl;
//     for (size_t i = 0; i < vans.size(); ++i)
//         cout << vans[i].a + 1 << " " << vans[i].b + 1 << '\n';
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}

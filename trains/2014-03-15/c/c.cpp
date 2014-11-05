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
const int maxn = 105;

map<pii, int> edges;
int n, m;
vi e[maxn];
vi re[maxn];

void scan() {
    scanf("%d%d", &n, &m);
    forn(i, m) {
        int u, v;
        scanf("%d%d", &u, &v);
        --u; --v;
        e[u].pb(v);
        re[v].pb(u);
        edges[mp(u, v)] = 1;
    }
}

int cmp(int i, int j) {
    return e[i].size() > e[j].size();
}

int sum;
int order[maxn], pos[maxn];

int f(int v) {
    int res = 0;
    forn(i, e[v].size()) if (pos[e[v][i]] < pos[v]) ++res;
    forn(i, re[v].size()) if (pos[e[v][i]] > pos[v]) ++res;
    return res;
}

void mswap(int u, int v) {
    sum -= f(u);
    sum -= f(v);

    int pu = pos[u], pv = pos[v];
    order[pv] = u;
    order[pu] = v;
    pos[v] = pu;
    pos[u] = pv;

    sum += f(u);
    sum += f(v);
}

void solve() {
    int k = n * (n-1) / 2 - m;
    cerr << "k = " << k << endl;

    forn(i, n) order[i] = i;
    sort(order, order+n, cmp);
    forn(i, n) pos[order[i]] = i;

    forn(i, n) sum += f(i);

    cerr << "initial sum*2 = " << sum << endl;
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

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
int mod1, mod2;

bool prime(int n) {
    for (int i = 2; i*i <= n; ++i)
        if (n%i == 0)
            return false;
    return true;
}

int genprime() {
    int s = 1000000000 - 1000 - rand() % 1000000;
    while (!prime(s)) ++s;
    return s;
}

int rev1[maxn * 3], rev2[maxn * 3];

void genrev() {
    fore(i, 1, 3000000) {
        if (i == 1) rev1[i] = 1;
        else rev1[i] = (mod1 - (i64)(mod1/i)*rev1[mod1%i]%mod1) % mod1;
//         assert((i64)rev1[i] * i % mod1 == 1);
    }

    fore(i, 1, 3000000) {
        if (i == 1) rev2[i] = 1;
        else rev2[i] = (mod2 - (i64)(mod2/i)*rev2[mod2%i]%mod2) % mod2;
//         assert((i64)rev2[i] * i % mod2 == 1);
    }
}

struct edge { int v, r1, r2; };
int n, m;
int b[maxn];
int ans[maxn];
pair<pii, int> res[maxn];
int np;
vector<edge> e[maxn];

void dfs(int v, int r1, int r2) {
    b[v] = 1;
    res[np++] = mp(mp(r1, r2), v);
    forn(i, e[v].size()) {
        int to = e[v][i].v;
        if (b[to]) continue;
        dfs(to, (i64)r1 * e[v][i].r1 % mod1, (i64)r2 * e[v][i].r2 % mod2);
    }
}

void scan() {
    scanf("%d%d", &n, &m);
    forn(i, m) {
        int u, v, x, y;
        scanf("%d%d%d%d", &u, &v, &x, &y);
        --u; --v;
        e[u].pb({
            v,
            int((i64)y * rev1[x] % mod1),
            int((i64)y * rev2[x] % mod2)
        });
        e[v].pb({
            u,
            int((i64)x * rev1[y] % mod1),
            int((i64)x * rev2[y] % mod2)
        });
    }
}

void solve() {
    dfs(0,1,1);
    sort(res, res + n);
    int cc = 0;
    forn(i, n) {
        if (i != 0 && res[i].fi != res[i-1].fi) ++cc;
        ans[res[i].se] = cc;
    }
    forn(i, n) printf("%d\n", ans[i] + 1);
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    mod1 = genprime();
    mod2 = genprime();
    genrev();
    scan();
    solve();


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}

// 10:43
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
const int maxn = 45;
const int mod = 1000000007;
int add(int x, int y) { return (x+y)%mod; }
int mul(int x, int y) { return (i64)x*y%mod; }

int c[maxn][maxn];

void fillc() {
    c[0][0] = 1;
    fore(n, 1, maxn-1) {
        c[n][0] = c[n][n] = 1;
        fore(k, 1, n-1) c[n][k] = add(c[n-1][k], c[n-1][k-1]);
    }
}

int n, m;
vi e[maxn];
int d[1<<21];
int a[maxn][maxn];
int sub[maxn];
int id[maxn], k;
int b[maxn];

void scan() {
    scanf("%d%d", &n, &m);
    forn(i, m) {
        int x, y;
        scanf("%d%d", &x, &y);
        --x;--y;
        a[x][y] = 1;
        e[x].pb(y);
        e[y].pb(x);
    }
}

void dfs(int v) {
    b[v] = 1;
    id[k++] = v;
    forn(i, e[v].size()) {
        int to = e[v][i];
        if (!b[to]) dfs(to);
    }
}

int dp() {
//     forn(i, k) cout << id[i] << " "; cout << endl;
    forn(i, k) sub[i] = 0;
    forn(i, k) forn(j, k) if (a[id[i]][id[j]]) sub[i] |= (1<<j);
    forn(i, 1<<k) d[i] = 0;
    d[0] = 1;
    forn(mask, (1<<k)-1) {
        forn(i, k) if (!(mask&(1<<i)) && (sub[i] & mask) == sub[i]) {
            int nmask = mask^(1<<i);
            d[nmask] = add(d[nmask], d[mask]);
        }
    }
//     cout << "res = " << d[(1<<k)-1] << endl;
    return d[(1<<k)-1];
}

void solve() {
    int res = 1;
    int rn = n;
    forn(i, n) if (!b[i]) {
        k = 0;
        dfs(i);
        res = mul(res, dp());
        res = mul(res, c[rn][k]);
        rn -= k;
    }
    cout << res << endl;
}

int main() {
    fillc();
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

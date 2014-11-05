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
const int maxn = 300500;


int n, m, k;
int b[maxn];
int c[maxn];
int deg[maxn];
vi e[maxn];

int snum[maxn], rsnum[maxn], podd[maxn];

void scan() {
   scanf("%d%d", &n, &m);
   forn(i, m) {
       int u, v;
       scanf("%d%d", &u, &v);
       ++deg[--u];
       ++deg[--v];
       e[v].pb(u);
       e[u].pb(v);
   }
}

void dfs_order(int v) {
//     cout << "order " << v +1 << endl;
    if (deg[v] == 4) {
        snum[k] = v;
        rsnum[v] = k++;
    }
    b[v] = 1;
    forn(i, e[v].size()) if (!b[e[v][i]]) {
        dfs_order(e[v][i]);
    }
}

pii dfs(int st, int v) {
    b[v] = 1;
    forn(i, e[v].size()) {
        int to = e[v][i];
        if (!b[to]) {
            pii ret = dfs(st, to);
            return mp(ret.fi, ret.se ^ 1);
        } else if (rsnum[to] != -1 && to != st) {
            return mp(to, 1);
        }
    }
    assert(1);
}

void mfill(int v, int cc) {
    b[v] = 1;
    c[v] = cc;
    forn(i, e[v].size()) {
        int to = e[v][i];
        if (b[to]) {
            assert(1);
        } else {
            mfill(to, !cc);
        }
    }
}

void solve() {
    forn(i, n) rsnum[i] = -1;
    dfs_order(0);
    snum[k] = snum[0];
    forn(i, n) {
        b[i] = 0;
        if (rsnum[i] == -1) assert(1);
        else assert(1);
    }

    forn(i, k) b[snum[i]] = 1;
    forn(i, k) {
        forn(j, 4) {
            int to = e[snum[i]][j];
            if (!b[to]) {
                pii ret = dfs(snum[i], to);
//                 cout << snum[i]+1 << " - " << ret.fi+1 << ": " << ret.se << endl;
                int to = ret.fi;
                int odd = ret.se;
                if (snum[i+1] == to) {
                    podd[i] ^= odd;
                } else {
                    podd[(i+k-1)%k] ^= odd;
                }
            }
        }
    }

//     forn(i, k) {
//         cout << snum[i] + 1 << " " << podd[i] << endl;
//     }

    forn(i, k*2) {
        snum[i+k] = snum[i];
        podd[i+k] = podd[i];
    }
    int s = 0;
    while (s < k && podd[s])
        ++s;
    forn(i, n) b[i] = 0;
    for (int i = s; i < s+k; ++i) {
        if (podd[i] == 1) {
            b[snum[i+1]] = 1;
            c[snum[i+1]] = -1;
            ++i;
        }
    }

    forn(i, n) if (!b[i]) mfill(i, 0);
    forn(mc, 2) {
        int cnt = count(c, c+n, mc);
        printf("%d", cnt);
        forn(i, n) if (c[i] == mc) printf(" %d", i+1);
        printf("\n");
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

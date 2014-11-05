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
const int maxn = 300500;

int n;
int c[maxn];
vi e[maxn];
int u[maxn];
int res[maxn];

bool scan() {
    scanf("%d", &n);
    if (n == 0) return false;
    forn(i, n) e[i].clear();
    forn(i, n-1) {
        int p;
        scanf("%d", &p);
        e[p-1].pb(i+1);
    }
    int k;
    scanf("%d", &k);
    forn(i, k) {
        int v, cc;
        scanf("%d%d", &v, &cc);
        c[v-1] = cc-1;
    }
    return true;
}

void dfs(int v) {
    if (e[v].empty()) {
        u[v] = (1<<c[v]);
        return;
    }
    int ret = 0;
    forn(i, e[v].size()) {
        dfs(e[v][i]);
    }
    forn(c, 3) {
        forn(i, e[v].size()) {
            if (u[e[v][i]] == (1<<c)) {
                goto ovr;
            }
        }
        ret |= 1<<c;
        ovr:;
    }
    u[v] = ret;
}

void go(int v, int c) {
    forn(i, 3) if (i != c && (u[v]&(1<<i))) {
        forn(j, e[v].size()) go(e[v][j], i);
        res[v] = i;
        return;
    }
    assert(false);
}

void solve() {
    dfs(0);
//     forn(i, n) cout << u[i] << " "; cout << endl;
    if (u[0]) {
        printf("YES\n");
        go(0, -1);
        forn(i, n) printf("%d ", res[i] + 1);
        printf("\n");
    } else {
        printf("NO\n");
    }
}


int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    freopen("coloring.in", "r", stdin);
    freopen("coloring.out", "w", stdout);

    while (scan()) {
        solve();
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}

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
const int maxn = 500500;

int n;
vi e[maxn];
int a[maxn];
int h[maxn];
int deg[maxn];
int p[maxn];
int s[maxn];

bool cmp(const pii& lhs, const pii& rhs) {
    return lhs.fi-lhs.se > rhs.fi-rhs.se;
}

pii dfs(int v, int anc) {
    p[v] = anc;
    s[v] = 1;
    vector<pii> ts;
    forn(i, e[v].size()) {
        int to = e[v][i];
        if (anc == to) {
            swap(e[v][i], e[v].back());
            e[v].pop_back();
            --i;
            continue;
        }
        h[to] = h[v] + 1;
        ts.pb(dfs(to, v));
        s[v] += s[to];
    }
    sort(all(ts), cmp);
    if (!ts.empty()) {
//         forn(i, ts.size()) {
//             cout << ts[i].fi << " " << ts[i].se << "    ";
//         }
//         cout << endl;
    }
    int st = 0;
    int mx = 0;
    forn(i, ts.size()) {
        mx = max(mx, st + ts[i].fi);
        st += ts[i].se;
    }
    mx = max(mx, h[v] + a[v] + s[v] - 1);
    return mp(mx, s[v]);
}


void solve() {
    auto it = dfs(0, -1);
    cout << it.first << endl;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    scanf("%d", &n);
    forn(i, n) {
        scanf("%d", &a[i]);
    }
    forn(i, n-1) {
        int u, v;
        scanf("%d%d", &u, &v);
        e[--u].pb(--v);
        e[v].pb(u);
    }
    solve();

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
